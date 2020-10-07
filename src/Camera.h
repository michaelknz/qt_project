#include "Matrix.h"

class Camera {
public:
	Camera();
	vector3f Get_CameraPos();
	vector3f Get_CameraFront();
	vector3f Get_CameraUp();
private:
	vector3f CameraPos;
	vector3f CameraFront;
	vector3f CameraUp;
};