#include "Decal.h"

Decal::Decal(mat4 view, mat4 projection) {
	texture = new Texture("GUI.png");
	shader = new Shader("decalShade");
	this->view = view;
	this->projection = projection;

	vert = new float[30];

	vert[0] = -0.1f; vert[1] = -0.1f; vert[2] = 0.03f; vert[3] = (26.0f*16.0f/(float)texture->Width()); vert[4] = (10.0f * 16.0f / (float)texture->Height());
	vert[5] = -0.1f; vert[6] = 0.1f; vert[7] = 0.03f; vert[8] = (26.0f * 16.0f / (float)texture->Width()); vert[9] = (11.0f * 16.0f / (float)texture->Height());
	vert[10] = 0.1f; vert[11] = 0.1f; vert[12] = 0.03f; vert[13] = (27.0f * 16.0f / (float)texture->Width()); vert[14] = (11.0f * 16.0f / (float)texture->Height());
	vert[15] = -0.1f; vert[16] = -0.1f; vert[17] = 0.03f; vert[18] = (26.0f * 16.0f / (float)texture->Width()); vert[19] = (10.0f * 16.0f / (float)texture->Height());
	vert[20] = 0.1f; vert[21] = -0.1f; vert[22] = 0.03f; vert[23] = (27.0f * 16.0f / (float)texture->Width()); vert[24] = (10.0f * 16.0f / (float)texture->Height());
	vert[25] = 0.1f; vert[26] = 0.1f; vert[27] = 0.03f; vert[28] = (27.0f * 16.0f / (float)texture->Width()); vert[29] = (11.0f * 16.0f / (float)texture->Height());

	mesh = new Mesh(vert, 30);
	alpha = 0.0f;
	del = 0.01f;
}

void Decal::DrawDecal(vector3f position) {
	shader->bind();
	texture->bind();
	shader->SetUniformMatrix4fv("model", Matrix::Transplon(Matrix::Translate(position)));
	shader->SetUniformMatrix4fv("view", Matrix::Transplon(view));
	shader->SetUniformMatrix4fv("projection", Matrix::Transplon(projection));
	shader->SetUniform1f("alpha", alpha);
	mesh->Draw_Mesh();
	texture->unbind();
	shader->unbind();
}

void Decal::SetAlpha() {
	alpha = 1.0f;
}

void Decal::Update(vector3f position) {
	if (alpha > 0.0f) {
		DrawDecal(position);
		alpha -= del;
	}
}

void Decal::UpdateCamera(mat4 view) {
	this->view = view;
}

Decal::~Decal() {
	delete[] vert;
	delete texture;
	delete shader;
	delete mesh;
}