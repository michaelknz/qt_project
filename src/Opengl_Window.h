#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <QOpenGL.h>
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qtimer.h>
#include <array>
#include <iostream>
#include "Matrix.h"
#include "Camera.h"
#include "Player.h"
#include "Room_Base.h"
#include "Level_Base.h"
#include "GameGUI.h"
#include <unordered_map>
#include "DataBase.h"


class gl_Window :public QOpenGLWidget, protected QOpenGLFunctions {

	Q_OBJECT
public:
	gl_Window(bool is_continue, QWidget* parent = 0);
	~gl_Window();
	Chest Interact_With_Objects();
	void Attak();
	std::unordered_map<int, bool> key_cache;
	void SetMousePos(int x, int y, bool is_pushed);
	void ChangeItems();
	void SetIsChange();
private slots:
	void Loop();
signals:
	void Quit();
protected:
	void paintGL() override;
	void initializeGL() override;
private:
	QTimer* timer;
	Camera* camera;
	Player* player;
	GameGUI* gui;
	mat4 projection;
	mat4 view;
	Level_Base* level;
	bool chest_is_drawn;
	float mouse_x;
	float mouse_y;
	bool is_pushed;
	bool is_change;
	bool is_continue;
	bool is_quit;
};
#endif