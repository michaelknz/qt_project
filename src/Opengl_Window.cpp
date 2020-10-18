#include "Opengl_Window.h"

gl_Window::gl_Window(QWidget* parent) :
	QOpenGLWidget(parent)
{
	camera = new Camera();
	key_cache[Qt::Key_W] = false;
	key_cache[Qt::Key_S] = false;
	key_cache[Qt::Key_D] = false;
	key_cache[Qt::Key_A] = false;
	key_cache[Qt::Key_E] = false;
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

	player = new Player("Hero.png", view, projection);
	level = new Level_Base;
	level->Init(view, projection);

	gui = new GameGUI(player);
}

void gl_Window::paintGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (key_cache[Qt::Key_E] == true) {
		Interact_With_Objects();
		if (camera->Is_On_Update()) {
			view = Matrix::lookat(camera->Get_CameraPos(), camera->Get_CameraFront(), camera->Get_CameraUp());
			level->UpdateCamera(view);
			player->UpdateCamera(view);
		}
	}

	level->DrawRoom(*player, key_cache);

	player->Update(key_cache);
	player->DrawPlayer();

	gui->DrawPlayerInteface(player);
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
	level->ShutUp();
	delete level;
}

void gl_Window::Interact_With_Objects() {
	level->Interact_With_Doors(player, camera);
}

