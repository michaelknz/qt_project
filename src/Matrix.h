#ifndef MATRIX_H
#define MATRIX_H


#define _USE_MATH_DEFINES
#include <cmath>


struct vector3f
{
	float mas[3];
	vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
};

struct mat4 
{
	float mas[16];
	mat4();
};

class Matrix {

public:
	static mat4 projection(float fov, float aspect, float zNear, float zFar);
	static vector3f normalize(const vector3f& vec);
	static float dot(const vector3f& vec1, const vector3f& vec2);
	static vector3f vector_sum(const vector3f& vec1, const vector3f& vec2);
	static vector3f mult_vector_on_scalar(const vector3f& vec, float scalar);
	static vector3f cross(const vector3f& vec1, const vector3f& vec2);
	static mat4 lookat(const vector3f& CameraPos, const vector3f& CameraFront, const vector3f& CameraUp);
	static mat4 Rotate(float angle, vector3f vec);
	static mat4 Transplon(const mat4& matrix);
	static mat4 Translate(const vector3f& vec);
	static mat4 Scale(vector3f vec);
};

mat4 operator *(const mat4& mat1, const mat4& mat2);

#endif