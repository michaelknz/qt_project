#ifndef ENEMY_H
#define ENEMY_H
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Matrix.h"
#include "Player.h"
#include "Decal.h"

class Enemy {
public:
	Enemy(mat4 view, mat4 projection, vector3f pos);
	~Enemy();
	void DrawEnemy();
	void SetPosition(vector3f vec);
	void UpdateCamera(mat4 view);
	void MoveEnemy(const Player& player);
	void Attak(Player& player);
	void Is_Attaked(Player& player);
private:
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Decal* decal;
	float* vert;
	vector3f position;
	mat4 view;
	mat4 projection;
	float speed;
	int animS;
	int animP;
	float AttakRad;
	float damage;
	float life;
	float alpha;
	float del_Alpha;
};

#endif
