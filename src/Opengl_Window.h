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


class gl_Window :public QOpenGLWidget, protected QOpenGLFunctions {

	Q_OBJECT
public:
	gl_Window(QWidget* parent = 0);
	~gl_Window();
	void Interact_With_Objects();
	void Attak();
	std::unordered_map<int, bool> key_cache;
private slots:
	void Loop();
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
};
#endif