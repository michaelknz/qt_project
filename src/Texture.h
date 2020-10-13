#ifndef TEXTURE_H
#define TEXTURE_H

#include <qopengl.h>
#include <qopenglextrafunctions.h>
#include <string>
#include <qimage.h>
#include <qglwidget>
#include "Shader.h"
#include <qmessagebox.h>

class Texture : protected QOpenGLExtraFunctions {
public:
	Texture(const std::string& filename);
	QImage LoadTextureS(const std::string& filename);
	~Texture();
	void UseTexture(Shader* shade);
	void bind();
	void unbind();
	unsigned int Width();
	unsigned int Height();
private:
	GLuint texture;
	unsigned int height;
	unsigned int width;
};
#endif