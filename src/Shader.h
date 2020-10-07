#include <fstream>
#include <string>
#include <qopengl.h>
#include <qopenglfunctions.h>

class Shader:protected QOpenGLFunctions {
public:
	Shader(const std::string& file);
	~Shader();
	std::string Read_Shader(const std::string& file_name);
	GLuint Create_Shader(const std::string& text, GLuint type);
	GLuint GetProgram();
	void bind();
	void unbind();
private:
	GLuint shaders[2];
	GLuint program;
};