#ifndef GAMEGUI_H
#define GAMEGUI_H
#include <string>
#include <unordered_map>
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Chest.h"

struct TexCoords {
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	TexCoords(int minx = 0, int maxx = 0, int miny = 0, int maxy = 0);
};

class GameGUI {
public:
	GameGUI(const Player& player);
	~GameGUI();
	void SetBackgroundTile(float bx, float by, float del_x, float del_y);
	void SetLifeBarVert(const Player& player);
	void SetCurWeaponTile(float bx, float by, float del_x, float del_y, TexCoords cur);
	void ResetLifeBarVert(const Player& player);
	void ResetCurWeaponTile(float bx, float by, float del_x, float del_y, TexCoords cur);
	void DrawLifeBar(const Player& player);
	void DrawCurWeapon(const Player& player);
	void DrawPlayerInteface(const Player& player);
	void SetCurChest(Chest ch);
	void SetChestBgVert(float bx, float by);
	void DrawChest(float mouse_x, float mouse_y, bool is_pushed);
	void SetColorVert(float bx, float by);
	Chest GetCurChest();
	void SetChestItem(std::string it);
	void SetLetters();
	void SetLetterVert();
	void SetColorEndVert();
	void SetOkVert();
	void DrawEndScreen();
	void SetIsPush(bool flag);
private:
	Texture* texture;
	Texture* textureb;
	std::unordered_map<std::string, TexCoords> it_cache;
	std::unordered_map<char, TexCoords> letters;
	bool is_pushed;
	Shader* color_Shader;
	Shader* texture_Shader;
	Mesh* life_bar_mesh;
	Mesh* bg_chest_tile_mesh;
	Mesh* bg_tile_mesh;
	Mesh* cur_weapon_mesh;
	Mesh* color_tile_mesh;
	Mesh* letter_end_mesh;
	Mesh* end_ok_mesh;
	Mesh* color_tile_end_mesh;
	Chest cur_chest;
	float tile_size;
	float tile_width;
	float tile_height;
	float length_between_tiles;
	float* vert_back_tile;
	float* life_bar_vert;
	float* cur_weapon_tile_vert;
	float* vert_chest_back_tile;
	float* vert_color_tile;
	float* vert_letters;
	float* vert_color_tile_end;
	float* vert_end_ok;
};

#endif