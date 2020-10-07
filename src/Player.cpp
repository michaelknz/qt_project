#include "Player.h"

Player::Player() {
	player_pos = vector3f(0.0f, 0.0f, 0.0f);
	speed = 0.2f;
}

void Player::Move_Player(vector3f vec) {
	player_pos = Matrix::vector_sum(player_pos, vec);
}

vector3f Player::Get_playerPos() {
	return player_pos;
}

float Player::Get_playerSpeed() {
	return speed;
}