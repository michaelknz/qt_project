#include "Camera.h"

Camera::Camera() {
	CameraPos = vector3f(0.0f, 0.0f, 1.5f);
	CameraFront = vector3f(0.0f, 0.0f, -1.0f);
	CameraUp = vector3f(0.0f, 1.0f, 0.0f);
}

vector3f Camera::Get_CameraPos() {
	return CameraPos;
}

vector3f Camera::Get_CameraFront() {
	return CameraFront;
}

vector3f Camera::Get_CameraUp() {
	return CameraUp;
}