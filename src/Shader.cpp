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

GLint Shader::GetUniformLocation(const std::string& s) {
	if (uniform_locations.find(s) != uniform_locations.end()) {
		return uniform_locations[s];
	}
	uniform_locations[s] = glGetUniformLocation(program, s.c_str());
	return uniform_locations[s];
}

void Shader::SetUniformMatrix4fv(const std::string& s, const mat4& mat) {
	glUniformMatrix4fv(GetUniformLocation(s), 1, GL_FALSE, mat.mas);
}

void Shader::SetUniform3f(const std::string& s, const vector3f& vec) {
	glUniform3f(GetUniformLocation(s), vec.mas[0], vec.mas[1], vec.mas[2]);
}

void Shader::SetUniform1i(const std::string& s, int code) {
	glUniform1i(GetUniformLocation(s), code);
}

void Shader::SetUniform1f(const std::string& s, float code) {
	glUniform1f(GetUniformLocation(s), code);
}
