#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QMainWindow>
#include <QKeyEvent>
#include "start_screen.h"
#include "Opengl_Window.h"


class Main_Window : public QMainWindow {
	Q_OBJECT

public:
	explicit Main_Window(QWidget *parent = 0);
	~Main_Window();
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
public slots:
	void StartScreebDeleteEvent();


private:
	Start_Screen* st;
	gl_Window* glwnd;
};
#endif
