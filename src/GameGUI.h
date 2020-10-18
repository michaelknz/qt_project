#ifndef GAMEGUI_H
#define GAMEGUI_H
#include <string>
#include <unordered_map>
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"

struct TexCoords {
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	TexCoords(int minx = 0, int maxx = 0, int miny = 0, int maxy = 0);
};

class GameGUI {
public:
	GameGUI(Player* player);
	~GameGUI();
	void SetBackgroundTile(float bx, float by, float del_x, float del_y);
	void SetLifeBarVert(Player* player);
	void SetCurWeaponTile(float bx, float by, float del_x, float del_y, TexCoords cur);
	void ResetLifeBarVert(Player* player);
	void ResetCurWeaponTile(float bx, float by, float del_x, float del_y, TexCoords cur);
	void DrawLifeBar(Player* player);
	void DrawCurWeapon(Player* player);
	void DrawPlayerInteface(Player* player);
private:
	Texture* texture;
	Texture* textureb;
	std::unordered_map<std::string, TexCoords> it_cache;
	Shader* color_Shader;
	Shader* texture_Shader;
	Mesh* life_bar_mesh;
	Mesh* bg_tile_mesh;
	Mesh* cur_weapon_mesh;
	float tile_size;
	float tile_width;
	float tile_height;
	float length_between_tiles;
	float* vert_back_tile;
	float* life_bar_vert;
	float* cur_weapon_tile_vert;
};

#endif