#ifndef PLAYER_H
#define PLAYER_H

#include "Matrix.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include <string>
#include <unordered_map>
#include <iostream>

class Player {
public:
	Player(const std::string& filename, mat4 view, mat4 proj);
	void Move_Player(vector3f vec);
	vector3f Get_playerPos() const;
	float Get_playerSpeed() const;
	void DrawPlayer();
	void Update(std::unordered_map<int, bool> map);
private:
	vector3f player_pos;
	float speed;
	Shader* shader;
	Mesh* mesh;
	Texture* texture;
	mat4 model;
	mat4 view;
	mat4 projection;
	float* vert;
	int animS;
	int animP;
};
#endif