#include "main_window.h"

Main_Window::Main_Window(QWidget* parent):
	QMainWindow(parent)
{
	this->setGeometry(300, 300, 800, 600);
	this->setFixedSize(800, 600);
	st = new Start_Screen();
	this->setCentralWidget(st);
	QObject::connect(st, SIGNAL(destroyed()), this, SLOT(StartScreebDeleteEvent()));
}

Main_Window::~Main_Window() {
	
}

void Main_Window::StartScreebDeleteEvent() {
	glwnd = new gl_Window();
	this->setCentralWidget(glwnd);
}

void Main_Window::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_W) {
		glwnd->GetPlayer()->Move_Player(vector3f(0.0f, glwnd->GetPlayer()->Get_playerSpeed(), 0.0f));
	}

	if (event->key() == Qt::Key_S) {
		glwnd->GetPlayer()->Move_Player(vector3f(0.0f, -glwnd->GetPlayer()->Get_playerSpeed(), 0.0f));
	}

	if (event->key() == Qt::Key_A) {
		glwnd->GetPlayer()->Move_Player(vector3f(-glwnd->GetPlayer()->Get_playerSpeed(), 0.0f, 0.0f));
	}

	if (event->key() == Qt::Key_D) {
		glwnd->GetPlayer()->Move_Player(vector3f(glwnd->GetPlayer()->Get_playerSpeed(), 0.0f, 0.0f));
	}

}