#include "Opengl_Window.h"

gl_Window::gl_Window(bool is_continue, QWidget* parent) :
	QOpenGLWidget(parent)
{
	camera = new Camera();
	key_cache[Qt::Key_W] = false;
	key_cache[Qt::Key_S] = false;
	key_cache[Qt::Key_D] = false;
	key_cache[Qt::Key_A] = false;
	key_cache[Qt::Key_E] = false;
	key_cache[Qt::Key_Escape] = false;
	key_cache[Qt::LeftButton] = false;

	chest_is_drawn = false;
	is_pushed = false;
	is_change = true;
	is_quit = false;
	this->is_continue = is_continue;
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
	level->Init(view, projection, is_continue);

	gui = new GameGUI(*player);
}

void gl_Window::paintGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (player->Get_playerLife() <= 0.0f) {
		gui->DrawEndScreen();
		float x = (2.0f / 1600.0f) * mouse_x - 1.0f;
		float y = ((2.0f / 800.0f) * mouse_y - 1.0f) * (-1.0f);
		if (y <= -0.25f && y >= -0.38f && x <= 0.08f && x >= -0.08f && is_pushed) {
			gui->SetIsPush(true);
			is_quit = true;
		}
		if (y <= -0.25f && y >= -0.38f && x <= 0.08f && x >= -0.08f && !is_pushed && is_quit) {
			gui->SetIsPush(false);
			emit Quit();
		}
		return;
	}

	if (key_cache[Qt::Key_E] == true) {
		Chest ch = Interact_With_Objects();
		if (camera->Is_On_Update()) {
			view = Matrix::lookat(camera->Get_CameraPos(), camera->Get_CameraFront(), camera->Get_CameraUp());
			level->UpdateCamera(view);
			player->UpdateCamera(view);
		}
		if (ch.item != "NULL") {
			gui->SetCurChest(ch);
			chest_is_drawn = true;
		}
	}

	if (key_cache[Qt::Key_Escape] == true) {
		chest_is_drawn = false;
	}

	if (key_cache[Qt::LeftButton] == true) {
		level->AttakCurEnemy(*player);
		key_cache[Qt::LeftButton] = false;
	}

	level->UpdateEnemyInRoom(*player);
	level->DrawRoom(*player, key_cache);

	player->Update(key_cache);
	player->DrawPlayer();
	Attak();

	gui->DrawPlayerInteface(*player);

	if (chest_is_drawn) {
		gui->DrawChest(mouse_x, mouse_y, is_pushed);
		float x = (2.0f / 1600.0f) * mouse_x - 1.0f;
		float y = ((2.0f / 800.0f) * mouse_y - 1.0f) * (-1.0f);
		if (y <= 0.2f && y >= -0.2f && x <= 0.1f && x >= -0.1f && is_pushed && is_change) {
			ChangeItems();
			is_change = false;
		}
	}
}

void gl_Window::Loop() {
	makeCurrent();
	this->update();
	doneCurrent();
}

gl_Window::~gl_Window() {
	level->SaveLevelMap();
	delete player;
	delete camera;
	delete timer;
	level->ShutUp();
	delete level;
	delete gui;
}

Chest gl_Window::Interact_With_Objects() {
	level->Interact_With_Doors(player, camera);
	Chest out = level->Interact_With_Chests(player);
	return out;
}

void gl_Window::Attak() {
	level->GetCurEnemy()->Attak(*player);
}

void gl_Window::SetMousePos(int x, int y, bool is_pushed) {
	mouse_x = (float)x;
	mouse_y = (float)y;
	this->is_pushed = is_pushed;
}

void gl_Window::ChangeItems() {
	std::string tmp = player->GetCurWeapon();
	player->SetCurWeapon(gui->GetCurChest().item);
	gui->SetChestItem(tmp);
	level->SetChestItem(gui->GetCurChest());
}

void gl_Window::SetIsChange() {
	is_change = true;
}