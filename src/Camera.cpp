#include "Camera.h"

Camera::Camera() {
	CameraPos = vector3f(0.0f, 0.0f, 1.5f);
	CameraFront = vector3f(0.0f, 0.0f, -1.0f);
	CameraUp = vector3f(0.0f, 1.0f, 0.0f);
	to_update = false;
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

void Camera::Move_Camera(vector3f vec) {
	CameraPos = Matrix::vector_sum(CameraPos, vec);
	to_update = true;
}

void Camera::Update() {
	to_update = false;
}

bool Camera::Is_On_Update() {
	return to_update;
}