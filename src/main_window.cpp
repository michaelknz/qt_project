#include "main_window.h"

Main_Window::Main_Window(QWidget* parent):
	QMainWindow(parent)
{
	this->setGeometry(100, 100, 1600, 800);
	this->setFixedSize(1600, 800);
	st = new Start_Screen();
	glwnd = nullptr;
	this->setCentralWidget(st);
	QObject::connect(st, SIGNAL(destroyed()), this, SLOT(StartScreebDeleteEvent()));
}

Main_Window::~Main_Window() {
	if (glwnd != nullptr) {
		delete glwnd;
	}
}

void Main_Window::StartScreebDeleteEvent() {
	if (st->GetIsQuit()) {
		QCoreApplication::quit();
		return;
	}
	glwnd = new gl_Window(st->GetIsContinue());
	this->setCentralWidget(glwnd);
	QObject::connect(glwnd, SIGNAL(Quit()), this, SLOT(End()));
}

void Main_Window::keyPressEvent(QKeyEvent* event) {
	if (glwnd != nullptr) {
		glwnd->key_cache[event->key()] = true;
	}
	QMainWindow::keyPressEvent(event);
}

void Main_Window::keyReleaseEvent(QKeyEvent* event) {
	if (glwnd != nullptr) {
		glwnd->key_cache[event->key()] = false;
	}
	QMainWindow::keyReleaseEvent(event);
}

void Main_Window::mouseReleaseEvent(QMouseEvent* event) {
	if (glwnd != nullptr) {
		if (event->button() == Qt::LeftButton) {
			glwnd->key_cache[Qt::LeftButton] = true;
		}
		glwnd->SetMousePos(event->pos().x(), event->pos().y(), false);
		glwnd->SetIsChange();
	}
	QMainWindow::mouseReleaseEvent(event);
}

void Main_Window::mousePressEvent(QMouseEvent* event) {
	if (glwnd != nullptr) {
		glwnd->SetMousePos(event->pos().x(), event->pos().y(), true);
	}
	QMainWindow::mouseMoveEvent(event);
}

void Main_Window::End() {
	QCoreApplication::quit();
}