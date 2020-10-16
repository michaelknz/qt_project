#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"

class Camera {
public:
	Camera();
	vector3f Get_CameraPos();
	vector3f Get_CameraFront();
	vector3f Get_CameraUp();
	void Move_Camera(vector3f vec);
	void Update();
	bool Is_On_Update();
private:
	vector3f CameraPos;
	vector3f CameraFront;
	vector3f CameraUp;
	bool to_update;
};

#endif