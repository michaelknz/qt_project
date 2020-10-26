#include "Matrix.h"

vector3f::vector3f(float x, float y, float z) {
	mas[0] = x;
	mas[1] = y;
	mas[2] = z;
}

mat4::mat4() {
	mas[0] = 1; mas[1] = 0; mas[2] = 0; mas[3] = 0;
	mas[4] = 0; mas[5] = 1; mas[6] = 0; mas[7] = 0;
	mas[8] = 0; mas[9] = 0; mas[10] = 1; mas[11] = 0;
	mas[12] = 0; mas[13] = 0; mas[14] = 0; mas[15] = 1;
}

vector3f Matrix::normalize(const vector3f& vec) {
	vector3f out;
	if (IsNullVector(vec)) {
		return vec;
	}
	out.mas[0] = vec.mas[0] / sqrt(vec.mas[0] * vec.mas[0] + vec.mas[1] * vec.mas[1] + vec.mas[2] * vec.mas[2]);
	out.mas[1] = vec.mas[1] / sqrt(vec.mas[0] * vec.mas[0] + vec.mas[1] * vec.mas[1] + vec.mas[2] * vec.mas[2]);
	out.mas[2] = vec.mas[2] / sqrt(vec.mas[0] * vec.mas[0] + vec.mas[1] * vec.mas[1] + vec.mas[2] * vec.mas[2]);
	return out;
}

float Matrix::dot(const vector3f& vec1, const vector3f& vec2) {
	return vec1.mas[0] * vec2.mas[0] + vec1.mas[1] * vec2.mas[1] + vec1.mas[2] * vec2.mas[2];
}

vector3f Matrix::vector_sum(const vector3f& vec1, const vector3f& vec2) {
	vector3f out;
	out.mas[0] = vec1.mas[0] + vec2.mas[0];
	out.mas[1] = vec1.mas[1] + vec2.mas[1];
	out.mas[2] = vec1.mas[2] + vec2.mas[2];
	return out;
}

vector3f Matrix::mult_vector_on_scalar(const vector3f& vec, float scalar) {
	vector3f out;
	out.mas[0] = vec.mas[0] * scalar;
	out.mas[1] = vec.mas[1] * scalar;
	out.mas[2] = vec.mas[2] * scalar;
	return out;
}

vector3f Matrix::cross(const vector3f& vec1, const vector3f& vec2) {
	vector3f i(1.0, 0.0, 0.0);
	vector3f j(0.0, 1.0, 0.0);
	vector3f k(0.0, 0.0, 1.0);

	vector3f a = mult_vector_on_scalar(i, (vec1.mas[1] * vec2.mas[2] - vec1.mas[2] * vec2.mas[1]));
	vector3f b = mult_vector_on_scalar(j, (vec1.mas[0] * vec2.mas[2] - vec1.mas[2] * vec2.mas[0]));
	b = mult_vector_on_scalar(b, -1.0);
	vector3f c = mult_vector_on_scalar(k, (vec1.mas[0] * vec2.mas[1] - vec1.mas[1] * vec2.mas[0]));
	return vector_sum(a, vector_sum(b, c));
}

mat4 Matrix::Transplon(const mat4& matrix) {
	mat4 out;

	out.mas[0] = matrix.mas[0];
	out.mas[1] = matrix.mas[4];
	out.mas[2] = matrix.mas[8];
	out.mas[3] = matrix.mas[12];

	out.mas[4] = matrix.mas[1];
	out.mas[5] = matrix.mas[5];
	out.mas[6] = matrix.mas[9];
	out.mas[7] = matrix.mas[13];

	out.mas[8] = matrix.mas[2];
	out.mas[9] = matrix.mas[6];
	out.mas[10] = matrix.mas[10];
	out.mas[11] = matrix.mas[14];

	out.mas[12] = matrix.mas[3];
	out.mas[13] = matrix.mas[7];
	out.mas[14] = matrix.mas[11];
	out.mas[15] = matrix.mas[15];

	return out;
}

mat4 Matrix::projection(float fov, float aspect, float zNear, float zFar) {
	mat4 out;
	float f = 1.0 / tan(fov * M_PI / 360.0);
	out.mas[0] = f / aspect; out.mas[1] = 0.0f; out.mas[2] = 0.0f; out.mas[3] = 0.0f;
	out.mas[4] = 0.0f; out.mas[5] = f; out.mas[6] = 0.0f; out.mas[7] = 0.0f;
	out.mas[8] = 0.0f; out.mas[9] = 0.0f; out.mas[10] = (zFar + zNear) / (zNear - zFar); out.mas[11] = (2 * zFar * zNear) / (zNear - zFar);
	out.mas[12] = 0.0f; out.mas[13] = 0.0f; out.mas[14] = -1.0f; out.mas[15] = 0.0f;

	return out;
}

mat4 Matrix::lookat(const vector3f& CameraPos, const vector3f& CameraFront, const vector3f& CameraUp) {
	vector3f xaxis;
	vector3f yaxis;
	vector3f zaxis;

	zaxis = normalize(CameraFront);
	xaxis = normalize(cross(zaxis, CameraUp));
	yaxis = cross(xaxis, zaxis);

	mat4 out;

	out.mas[0] = xaxis.mas[0]; out.mas[1] = yaxis.mas[0]; out.mas[2] = -zaxis.mas[0]; out.mas[3] = 0.0f;
	out.mas[4] = xaxis.mas[1]; out.mas[5] = yaxis.mas[1]; out.mas[6] = -zaxis.mas[1]; out.mas[7] = 0.0f;
	out.mas[8] = xaxis.mas[2]; out.mas[9] = yaxis.mas[2]; out.mas[10] = -zaxis.mas[2]; out.mas[11] = 0.0f;
	out.mas[12] = -dot(xaxis, CameraPos); out.mas[13] = -dot(yaxis, CameraPos); out.mas[14] = dot(zaxis, CameraPos); out.mas[15] = 1.0;

	return Transplon(out);
}

mat4 Matrix::Translate(const vector3f& vec) {
	mat4 out;
	out.mas[0] = 1; out.mas[1] = 0; out.mas[2] = 0; out.mas[3] = vec.mas[0];
	out.mas[4] = 0; out.mas[5] = 1; out.mas[6] = 0; out.mas[7] = vec.mas[1];
	out.mas[8] = 0; out.mas[9] = 0; out.mas[10] = 1; out.mas[11] = vec.mas[2];
	out.mas[12] = 0; out.mas[13] = 0; out.mas[14] = 0; out.mas[15] = 1;
	return out;
}

mat4 Matrix::Rotate(float angle, vector3f vec) {
	mat4 out;

	return out;
}

mat4 Matrix::Scale(vector3f vec) {
	mat4 out;
	out.mas[0] = vec.mas[0]; out.mas[1] = 0.0f; out.mas[2] = 0.0f; out.mas[3] = 0.0f;
	out.mas[4] = 0.0f; out.mas[5] = vec.mas[1]; out.mas[6] = 0.0f; out.mas[7] = 0.0f;
	out.mas[8] = 0.0f; out.mas[9] = 0.0f; out.mas[10] = vec.mas[2]; out.mas[11] = 0.0f;
	out.mas[12] = 0.0f; out.mas[13] = 0.0f; out.mas[14] = 0.0f; out.mas[15] = 1.0f;

	return out;
}

mat4 operator *(const mat4& mat1, const mat4& mat2) {
	mat4 out;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			out.mas[i * 4 + j] = mat1.mas[i * 4 + 0] * mat2.mas[0 * 4 + j] + mat1.mas[i * 4 + 1] * mat2.mas[1 * 4 + j] + mat1.mas[i * 4 + 2] * mat2.mas[2 * 4 + j] + mat1.mas[i * 4 + 3] * mat2.mas[3 * 4 + j];
		}
	}

	return out;
}

float Matrix::Length2D(vector3f vec1, vector3f vec2) {
	return sqrt((vec1.mas[0] - vec2.mas[0]) * (vec1.mas[0] - vec2.mas[0]) + (vec1.mas[1] - vec2.mas[1]) * (vec1.mas[1] - vec2.mas[1]));
}

bool Matrix::IsNullVector(vector3f vec) {
	if (vec.mas[0] == 0.0f && vec.mas[1] == 0.0f && vec.mas[2] == 0.0f) {
		return true;
	}
	else {
		return false;
	}
}

float Matrix::VectorModule(vector3f vec) {
	return sqrt(vec.mas[0] * vec.mas[0] + vec.mas[1] * vec.mas[1] + vec.mas[2] * vec.mas[2]);
}