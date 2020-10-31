#include "Enemy.h"

Enemy::Enemy(mat4 view, mat4 projection, vector3f pos) {
	this->projection = projection;
	this->view = view;
	position = pos;
	speed = 0.015f;
	texture = new Texture("Enemy.png");
	shader = new Shader("enemyShade");
	decal = new Decal(view, projection);

	vert = new float[30];
	vert[0] = -0.12f; vert[1] = -0.12f; vert[2] = 0.01f; vert[3] = 0.0f; vert[4] = 1.0f - (20.0f * 29.0f / (float)texture->Height());
	vert[5] = -0.12f; vert[6] = 0.12f; vert[7] = 0.01f; vert[8] = 0.0f; vert[9] = 1.0f - (20.0f * 28.0f / (float)texture->Height());
	vert[10] = 0.12f; vert[11] = 0.12f; vert[12] = 0.01f; vert[13] = (18.0f / (float)texture->Width()); vert[14] = 1.0f - (20.0f * 28.0f / (float)texture->Height());
	vert[15] = -0.12f; vert[16] = -0.12f; vert[17] = 0.01f; vert[18] = 0.0f; vert[19] = 1.0f - (20.0f * 29.0f / (float)texture->Height());
	vert[20] = 0.12f; vert[21] = -0.12f; vert[22] = 0.01f; vert[23] = (18.0f / (float)texture->Width()); vert[24] = 1.0f - (20.0f * 29.0f / (float)texture->Height());
	vert[25] = 0.12f; vert[26] = 0.12f; vert[27] = 0.01f; vert[28] = (18.0f / (float)texture->Width()); vert[29] = 1.0f - (20.0f * 28.0f / (float)texture->Height());

	mesh = new Mesh(vert, 30);
	animS = 1;
	animP = 0;
	AttakRad = 0.26f;
	damage = 0.05f;
	life = 5.0f;
	alpha = 1.0f;
	del_Alpha = 0.01f;
}

void Enemy::DrawEnemy() {
	if (life > 0.0f) {
		shader->bind();
		texture->bind();
		shader->SetUniformMatrix4fv("model", Matrix::Transplon(Matrix::Translate(position)));
		shader->SetUniformMatrix4fv("view", Matrix::Transplon(view));
		shader->SetUniformMatrix4fv("projection", Matrix::Transplon(projection));
		shader->SetUniform3f("color", vector3f(1.0f, 0.6f, 0.6f));
		shader->SetUniform1i("scale", animS);
		shader->SetUniform1f("plus", (float)((animP / 18) * 18) / (float)texture->Width());
		shader->SetUniform1f("del", 9.0f / (float)(texture->Width()));
		shader->SetUniform1f("alpha", 1.0f);
		mesh->Draw_Mesh();
		texture->unbind();
		shader->unbind();

	}

	else {
		shader->bind();
		texture->bind();
		shader->SetUniformMatrix4fv("model", Matrix::Transplon(Matrix::Translate(position)));
		shader->SetUniformMatrix4fv("view", Matrix::Transplon(view));
		shader->SetUniformMatrix4fv("projection", Matrix::Transplon(projection));
		shader->SetUniform3f("color", vector3f(1.0f, 0.6f, 0.6f));
		shader->SetUniform1i("scale", animS);
		shader->SetUniform1f("plus", (float)((animP / 18) * 18) / (float)texture->Width());
		shader->SetUniform1f("del", 9.0f / (float)(texture->Width()));
		shader->SetUniform1f("alpha", alpha);
		mesh->Draw_Mesh();
		texture->unbind();
		shader->unbind();
		alpha -= del_Alpha;
	}
	decal->Update(position);
}

void Enemy::SetPosition(vector3f vec) {
	position = vec;
}

Enemy::~Enemy() {
	delete vert;
	delete texture;
	delete shader;
	delete mesh;
}

void Enemy::UpdateCamera(mat4 view) {
	this->view = view;
	decal->UpdateCamera(view);
}

void Enemy::MoveEnemy(const Player& player) {
	if (life > 0.0f) {
		vector3f ppos = player.Get_playerPos();
		ppos.mas[2] = 0.0f;
		vector3f dir = Matrix::vector_sum(ppos, Matrix::mult_vector_on_scalar(position, -1.0f));
		dir = Matrix::normalize(dir);
		dir = Matrix::mult_vector_on_scalar(dir, speed);
		position = Matrix::vector_sum(position, dir);
		if (dir.mas[0] < 0.0f) {
			animS = -1;
		}
		else if (dir.mas[0] > 0.0f) {
			animS = 1;
		}
		animP += 2;
		if (animP > 3 * 18) {
			animP = animP % (3 * 18);
		}
	}
}

void Enemy::Attak(Player& player) {
	if (life > 0.0f) {
		vector3f del = Matrix::vector_sum(player.Get_playerPos(), Matrix::mult_vector_on_scalar(position, -1.0f));
		del.mas[2] = 0.0f;
		float dell = Matrix::VectorModule(del);
		if (dell <= AttakRad) {
			player.Is_Attaked(damage);
		}
	}
}

void Enemy::Is_Attaked(Player& player) {
	if (life > 0.0f) {
		vector3f del = Matrix::vector_sum(position, Matrix::mult_vector_on_scalar(player.Get_playerPos(), -1.0f));
		del.mas[2] = 0.0f;
		float dell = Matrix::VectorModule(del);
		if (dell <= player.GetAttakRad()) {
			life -= player.Get_playerDamage();
			decal->SetAlpha();
		}
	}
}