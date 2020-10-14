#ifndef MAPBG_H
#define MAPBG_H

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Matrix.h"
#include <unordered_map>
#include <string>
#include <unordered_set>
#include "Player.h"

struct Coord {
	float min_x;
	float min_y;
	float max_x;
	float max_y;
};

class MapBg {
public:
	MapBg();
	~MapBg();
	void Init(const std::string& filename, mat4 view, mat4 proj, vector3f room_pos);
	virtual void SetRoomMap();
	void ShutUp();
	virtual void SetTexMap();
	void SetTexMapUnit(char a, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy);
	void DrawMapBg();
	void SetVerts();
	void IsWall(const Player& player, std::unordered_map<int, bool>& keys);
protected:
	Texture* texture;
	Mesh* mesh;
	Shader* shader;
	unsigned int tile_tex_width;
	unsigned int tile_tex_height;
	float* verts;
	char* Map;
	unsigned int Map_width;
	unsigned int Map_height;
	std::unordered_map<char, Coord> TexCoordMap;
	mat4 projection;
	mat4 view;
	mat4 model;
	float tile_width;
	float tile_height;
	std::unordered_set<char> walls;
	vector3f room_pos;
};

#endif