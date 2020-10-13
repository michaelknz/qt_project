#include "Texture.h"

Texture::Texture(const std::string& filename) {
	initializeOpenGLFunctions();
	glGenTextures(1, &texture);
	QImage tex = LoadTextureS(filename);
	height = tex.height();
	width = tex.width();
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {

}

QImage Texture::LoadTextureS(const std::string& filename) {
	QImage t;
	QImage b;

	if (!b.load(filename.c_str()))
	{

		QMessageBox::information(NULL, "Error", "Could not load file");

		QImage b(16, 16, QImage::Format_RGB32);
		b.fill(Qt::green);
	}

	t = QGLWidget::convertToGLFormat(b);

	if (t.isNull())
	{
		QMessageBox::information(NULL, "Error", "IMAGE IS NULL");
	}

	return t;

}

void Texture::UseTexture(Shader* shade) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	shade->SetUniform1i("Texture", 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::Width() {
	return width;
}

unsigned int Texture::Height() {
	return height;
}