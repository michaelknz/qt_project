#ifndef MESH_H
#define MESH_H

#include <qopengl.h>
#include <qopenglfunctions.h>
#include <qopenglextrafunctions.h>

class Mesh : protected QOpenGLExtraFunctions  {
public:
	Mesh(float* VertexBuf, unsigned int size);
	~Mesh();
	void Draw_Mesh();
	void SetVertexBufWithTex(float* VertexBuf, unsigned int size);
private:
	GLuint vao;
	GLuint vbo;
	unsigned int BufSize;
};

#endif