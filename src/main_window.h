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
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
public slots:
	void StartScreebDeleteEvent();
	void End();

private:
	Start_Screen* st;
	gl_Window* glwnd;
};
#endif
