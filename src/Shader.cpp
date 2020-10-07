#include "Shader.h"

Shader::Shader(const std::string& file) {
	initializeOpenGLFunctions();
	program = glCreateProgram();
	shaders[0] = Create_Shader(Read_Shader(file + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = Create_Shader(Read_Shader(file + ".fs"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < 2; ++i) {
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);
	GLint loglen;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglen);
	if (loglen > 0) {
		char* log = new char[loglen];
		GLsizei writen;
		glGetProgramInfoLog(program, loglen, &writen, log);
		printf("%s\n", log);
		delete[] log;
	}
}

Shader::~Shader() {
	for (int i = 0; i < 2; ++i) {
		glDetachShader(program, shaders[i]);
	}

	glDeleteProgram(program);
}

std::string Shader::Read_Shader(const std::string& file_name) {
	std::ifstream file;
	file.open(file_name.c_str());
	std::string line;
	std::string output;
	while (file.good()) {
		getline(file, line);
		output.append(line + "\n");
	}
	return output;
}

GLuint Shader::Create_Shader(const std::string& text, GLuint type) {
	GLuint Shader = glCreateShader(type);
	const GLchar* p[1];
	p[0] = text.c_str();
	GLint l[1];
	l[0] = text.length();
	glShaderSource(Shader, 1, p, l);
	glCompileShader(Shader);
	return Shader;
}

GLuint Shader::GetProgram() {
	return program;
}

void Shader::bind() {
	glUseProgram(program);
}

void Shader::unbind() {
	glUseProgram(0);
}