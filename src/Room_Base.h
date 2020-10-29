#ifndef ROOM_BASE_H
#define ROOM_BASE_H

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Matrix.h"
#include <unordered_map>
#include <string>
#include <unordered_set>
#include "Player.h"
#include "Enemy.h"

struct Coord {
	float min_x;
	float min_y;
	float max_x;
	float max_y;
};

class Room_Base {
public:
	Room_Base();
	~Room_Base();
	void Init(const std::string& filename, mat4 view, mat4 proj, vector3f room_pos);
	virtual void SetRoomMap();
	void ShutUp();
	virtual void SetTexMap();
	void SetTexMapUnit(char a, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy);
	void DrawRoom();
	void SetVerts();
	void IsWall(const Player& player, std::unordered_map<int, bool>& keys);
	float GetRoomWidth() const;
	float GetRoomHeight() const;
	void SetDoor(char dir);
	void ResetVerts();
	vector3f Player_Pos_In_Room(Player* player);
	float Get_Tile_Height() const;
	float Get_Tile_Width() const;
	unsigned int Get_Room_Width_In_Tiles() const;
	unsigned int Get_Room_Height_In_Tiles() const;
	std::unordered_map<char, int> Get_Doors() const;
	void UpdateCamera(mat4 view);
	void UpdateEnemy(const Player& player);
	Enemy* GetEnemy() const;
	void AttakEnemy(Player& player);
protected:
	Texture* texture;
	Mesh* mesh;
	Shader* shader;
	Enemy* enemy;
	unsigned int tile_tex_width;
	unsigned int tile_tex_height;
	float* verts;
	std::string Map;
	unsigned int Map_width;
	unsigned int Map_height;
	std::unordered_map<char, Coord> TexCoordMap;
	std::unordered_map<char, int> doors;
	mat4 projection;
	mat4 view;
	mat4 model;
	float tile_width;
	float tile_height;
	std::unordered_set<char> walls;
	vector3f room_pos;
};

#endif