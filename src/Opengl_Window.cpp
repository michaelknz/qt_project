#include "Opengl_Window.h"

gl_Window::gl_Window(QWidget* parent) :
	QOpenGLWidget(parent)
{
	vert = { -0.5, -0.5, 0.0, 0.0, 0.0,
		0.5, 0.5, 0.0, 1.0, 1.0,
		0.5, -0.5, 0.0, 1.0, 0.0,
		-0.5, -0.5, 0.0, 0.0, 0.0,
		-0.5, 0.5, 0.0, 0.0, 1.0,
		0.5, 0.5, 0.0, 1.0, 1.0 };

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.3f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));
	timer->start(0);
	shader = new Shader("basic");
	mesh = new Mesh(&vert[0], vert.size());
	texture = new Texture("sheet.png");
}

void gl_Window::paintGL() {
	glClearColor(0.3f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();
	texture->UseTexture(shader);
	shader->SetUniformMatrix4fv("model", Matrix::Transplon(Matrix::Translate(vector3f(0.0f, 0.0f, -0.01)) * Matrix::Scale(vector3f(18.0f, 9.0f, 1.0f))));
	shader->SetUniformMatrix4fv("projection", Matrix::projection(90.0f, 1600.0f / 800.0f, 0.1f, 100.0f));
	shader->SetUniformMatrix4fv("view", Matrix::lookat(camera->Get_CameraPos(), camera->Get_CameraFront(), camera->Get_CameraUp()));
	texture->bind();
	mesh->Draw_Mesh();
	shader->unbind();
	texture->unbind();

	vector3f del_pos(map[Qt::Key_D] * player->Get_playerSpeed() - map[Qt::Key_A] * player->Get_playerSpeed(), map[Qt::Key_W] * player->Get_playerSpeed() - map[Qt::Key_S] * player->Get_playerSpeed(), 0.0);
	player->Move_Player(del_pos);

	shader->bind();
	shader->SetUniformMatrix4fv("model", Matrix::Transplon(Matrix::Translate(player->Get_playerPos()) * Matrix::Scale(vector3f(0.25f, 0.5f, 1.0f))));
	mesh->Draw_Mesh();
	shader->unbind();
}

void gl_Window::Loop() {
	makeCurrent();
	this->update();
	doneCurrent();
}

Player* gl_Window::GetPlayer() {
	return player;
}

