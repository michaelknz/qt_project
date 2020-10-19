#include "Player.h"

Player::Player(const std::string& filename, mat4 view, mat4 proj) {
	texture = new Texture(filename.c_str());

	player_pos = vector3f(0.0f, 0.0f, 0.0f);
	shader = new Shader("playerShade");
	life = 8;
	speed = 0.02f;
	cur_weapon = "small_sword";

	projection = proj;
	this->view = view;
	model = Matrix::Translate(player_pos);

	vert = new float[30];
	vert[0] = -0.17f; vert[1] = -0.17f; vert[2] = 0.01f; vert[3] = 0.0f; vert[4] = 1.0f - (32.0f / (float)texture->Height());
	vert[5] = -0.17f; vert[6] = 0.17f; vert[7] = 0.01f; vert[8] = 0.0f; vert[9] = 1.0f;
	vert[10] = 0.17f; vert[11] = 0.17f; vert[12] = 0.01f; vert[13] = (32.0f / (float)texture->Width()); vert[14] = 1.0f;
	vert[15] = -0.17f; vert[16] = -0.17f; vert[17] = 0.01f; vert[18] = 0.0f; vert[19] = 1.0f - (32.0f / (float)texture->Height());
	vert[20] = 0.17f; vert[21] = -0.17f; vert[22] = 0.01f; vert[23] = (32.0f / (float)texture->Width()); vert[24] = 1.0f - (32.0f / (float)texture->Height());
	vert[25] = 0.17f; vert[26] = 0.17f; vert[27] = 0.01f; vert[28] = (32.0f / (float)texture->Width()); vert[29] = 1.0f;

	mesh = new Mesh(vert, 30);

	animS = 1;
	animP = 0;
}

void Player::Move_Player(vector3f vec) {
	player_pos = Matrix::vector_sum(player_pos, vec);
	model = Matrix::Translate(player_pos);
}

vector3f Player::Get_playerPos() const {
	return player_pos;
}

float Player::Get_playerSpeed() const {
	return speed;
}

void Player::DrawPlayer() {
	shader->bind();
	texture->bind();

	shader->SetUniformMatrix4fv("model", Matrix::Transplon(model));
	shader->SetUniformMatrix4fv("view", Matrix::Transplon(view));
	shader->SetUniformMatrix4fv("projection", Matrix::Transplon(projection));
	shader->SetUniform1i("scale", animS);
	shader->SetUniform1f("plus", (float)((animP / 32) * 32) / (float)texture->Width());
	shader->SetUniform1f("del", 16.0f / (float)(texture->Width()));
	mesh->Draw_Mesh();

	texture->unbind();
	shader->unbind();
}

void Player::Update(std::unordered_map<int, bool> map) {

	if ((map[Qt::Key_D] == true && map[Qt::Key_A] == true) || (map[Qt::Key_W] == true && map[Qt::Key_S] == true)) {
		animP = 0;
	}

	else if (map[Qt::Key_D] == true) {
		animS = 1;
		animP = (animP + 4) % (4 * 32);
	}

	else if (map[Qt::Key_A] == true) {
		animS = -1;
		animP = (animP + 4) % (4 * 32);
	}

	else if (map[Qt::Key_W] == true || map[Qt::Key_S] == true) {
		animP = (animP + 4) % (4 * 32);
	}

	else {
		animP = 0;
	}
	vector3f del_pos(map[Qt::Key_D] * Get_playerSpeed() - map[Qt::Key_A] * Get_playerSpeed(), map[Qt::Key_W] * Get_playerSpeed() - map[Qt::Key_S] * Get_playerSpeed(), 0.0);
	Move_Player(del_pos);
}

void Player::UpdateCamera(mat4 view) {
	this->view = view;
}

int Player::Get_playerLife() const {
	return life;
}

std::string Player::GetCurWeapon() const {
	return cur_weapon;
}

Player::~Player() {
	delete[] vert;
	delete mesh;
	delete shader;
	delete texture;
}