#include "main_window.h"

Main_Window::Main_Window(QWidget* parent):
	QMainWindow(parent)
{
	this->setGeometry(100, 100, 1600, 1200);
	this->setFixedSize(1600, 900);
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
	glwnd->map[event->key()] = true;
	QMainWindow::keyPressEvent(event);
}

void Main_Window::keyReleaseEvent(QKeyEvent* event) {
	glwnd->map[event->key()] = false;
	QMainWindow::keyReleaseEvent(event);
}