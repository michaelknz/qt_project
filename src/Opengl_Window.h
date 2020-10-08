#include <QOpenGL.h>
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qtimer.h>
#include <array>
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "Matrix.h"
#include "Camera.h"
#include "Player.h"
#include <unordered_map>

class gl_Window :public QOpenGLWidget, protected QOpenGLFunctions {

	Q_OBJECT
public:
	gl_Window(QWidget* parent = 0);
	Player* GetPlayer();
	float Get_delTime();
	std::unordered_map<int, bool> map;
private slots:
	void Loop();
protected:
	void paintGL() override;
	void initializeGL() override;
private:
	QTimer* timer;
	std::array<float, 30> vert;
	Mesh* mesh;
	Shader* shader;
	Camera* camera;
	Player* player;
};