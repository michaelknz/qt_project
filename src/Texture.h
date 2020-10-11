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
private:
	GLuint texture;
};