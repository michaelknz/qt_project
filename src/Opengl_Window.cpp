#include "Opengl_Window.h"

gl_Window::gl_Window(QWidget* parent) :
	QOpenGLWidget(parent)
{
	vert = { -0.5, -0.5, 0.0, 0.0, 0.0,
		0.5, 0.5, 0.0, 0.0, 0.0,
		0.5, -0.5, 0.0, 0.0, 0.0,
		-0.5, -0.5, 0.0, 0.0, 0.0,
		-0.5, 0.5, 0.0, 0.0, 0.0,
		0.5, 0.5, 0.0, 0.0, 0.0 };

	camera = new Camera();
	player = new Player();
	map[Qt::Key_W] = false;
	map[Qt::Key_S] = false;
	map[Qt::Key_D] = false;
	map[Qt::Key_A] = false;
}

void gl_Window::initializeGL() {
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));
	timer->start(0);
	shader = new Shader("basic");
	mesh = new Mesh(&vert[0], vert.size());
}

void gl_Window::paintGL() {
	shader->bind();
	mesh->Draw_Mesh();
	shader->unbind();
}

void gl_Window::Loop() {
	makeCurrent();
	glClearColor(0.3f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vector3f del_pos(map[Qt::Key_D] * player->Get_playerSpeed() - map[Qt::Key_A] * player->Get_playerSpeed(), map[Qt::Key_W] * player->Get_playerSpeed() - map[Qt::Key_S] * player->Get_playerSpeed(), 0.0);
	player->Move_Player(del_pos);
	shader->bind();
	glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "model"), 1, GL_FALSE, Matrix::Transplon(Matrix::Translate(player->Get_playerPos())*Matrix::Scale(vector3f(0.5f,1.0f,1.0f))).mas);
	glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "projection"), 1, GL_FALSE, Matrix::projection(90.0f, 800.0f / 600.0f, 0.1f, 100.0f).mas);
	glUniformMatrix4fv(glGetUniformLocation(shader->GetProgram(), "view"), 1, GL_FALSE, Matrix::lookat(camera->Get_CameraPos(), camera->Get_CameraFront(), camera->Get_CameraUp()).mas);
	glUniform3f(glGetUniformLocation(shader->GetProgram(), "color"), 1.0f, 1.0f, 0.0f);
	shader->unbind();
	this->update();
	doneCurrent();
}

Player* gl_Window::GetPlayer() {
	return player;
}

