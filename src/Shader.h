#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <string>
#include <qopengl.h>
#include <qopenglfunctions.h>
#include <unordered_map>
#include "Matrix.h"

class Shader:protected QOpenGLFunctions {
public:
	Shader(const std::string& file);
	~Shader();
	std::string Read_Shader(const std::string& file_name);
	GLuint Create_Shader(const std::string& text, GLuint type);
	GLuint GetProgram();
	GLint GetUniformLocation(const std::string& s);
	void SetUniformMatrix4fv(const std::string& s, const mat4& mat);
	void SetUniform3f(const std::string& s, const vector3f& vec);
	void SetUniform1i(const std::string& s, int code);
	void SetUniform1f(const std::string& s, float code);
	void bind();
	void unbind();
private:
	GLuint shaders[2];
	GLuint program;
	std::unordered_map<std::string,GLint> uniform_locations;
};

#endif