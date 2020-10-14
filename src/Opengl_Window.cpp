#include "Opengl_Window.h"

gl_Window::gl_Window(QWidget* parent) :
	QOpenGLWidget(parent)
{
	camera = new Camera();
	map[Qt::Key_W] = false;
	map[Qt::Key_S] = false;
	map[Qt::Key_D] = false;
	map[Qt::Key_A] = false;
}

void gl_Window::initializeGL() {
	initializeOpenGLFunctions();
	projection = Matrix::projection(90.0f, 1600.0f / 800.0f, 0.1f, 100.0f);
	view = Matrix::lookat(camera->Get_CameraPos(), camera->Get_CameraFront(), camera->Get_CameraUp());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(Loop()));
	timer->start(0);

	back = new MapBg;
	back->Init("sheet.png", view, projection, vector3f(-0.5f));
	player = new Player("Hero.png", view, projection);
}

void gl_Window::paintGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	back->DrawMapBg();
	back->IsWall(*player, map);

	player->Update(map);
	player->DrawPlayer();

}

void gl_Window::Loop() {
	makeCurrent();
	this->update();
	doneCurrent();
}

gl_Window::~gl_Window() {
	delete player;
	delete camera;
	delete timer;
	back->ShutUp();
	delete back;
}

