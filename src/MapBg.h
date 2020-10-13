#ifndef MAPBG_H
#define MAPBG_H

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Matrix.h"
#include <unordered_map>
#include <string>

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
	void Init(const std::string& filename, mat4 view, mat4 proj);
	virtual void SetRoomMap();
	void ShutUp();
	virtual void SetTexMap();
	void SetTexMapUnit(char a, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy);
	void DrawMapBg();
	void SetVerts();
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
	float tile_width;
	float tile_height;
};

#endif