#include "GameGUI.h"

TexCoords::TexCoords(int minx, int maxx, int miny, int maxy) {
	min_x = minx;
	max_y = maxy;
	min_y = miny;
	max_x = maxx;
}

GameGUI::GameGUI(const Player& player) {
	tile_size = 0.05f;
	tile_width = tile_size;
	tile_height = tile_size * 2.0f;
	length_between_tiles = 0.005f;
	texture = new Texture("GUI.png");
	textureb = new Texture("GUIb.png");
	texture_Shader = new Shader("GUItexShade");
	vert_back_tile = new float[6 * 5];
	cur_weapon_tile_vert = new float[6 * 5];
	life_bar_vert = new float[4 * 5 * 6];

	it_cache["full_life"] = TexCoords(42, 43, 11, 12);
	it_cache["half_life"] = TexCoords(41, 42, 11, 12);
	it_cache["empty_life"] = TexCoords(40, 41, 11, 12);
	it_cache["small_sword"] = TexCoords(34, 35, 15, 16);

	SetLifeBarVert(player);
	SetBackgroundTile(tile_width / 2.0f + length_between_tiles * 2.0f, tile_height / 2.0f + length_between_tiles * 4.0f, -1.0f + tile_width / 2.0f + length_between_tiles * 2.0f, 1.0f - tile_height - tile_height / 2.0f - length_between_tiles * 4.0f);
	SetCurWeaponTile(tile_width / 2.0f + length_between_tiles * 2.0f, tile_height / 2.0f + length_between_tiles * 4.0f, -1.0f + tile_width / 2.0f + length_between_tiles * 2.0f, 1.0f - tile_height - tile_height / 2.0f - length_between_tiles * 4.0f, it_cache[player.GetCurWeapon()]);

	life_bar_mesh = new Mesh(life_bar_vert, 4 * 5 * 6);
	bg_tile_mesh = new Mesh(vert_back_tile, 5 * 6);
	cur_weapon_mesh = new Mesh(cur_weapon_tile_vert, 5 * 6);
}

void GameGUI::SetBackgroundTile(float bx, float by, float del_x, float del_y) {
	float min_x = 190.0f / (float)textureb->Width();
	float max_x = 290.0f / (float)textureb->Width();
	float min_y = 412.0f / (float)textureb->Height();
	float max_y = 512.0f / (float)textureb->Height();

	vert_back_tile[0] = -bx + del_x; vert_back_tile[1] = -by + del_y; vert_back_tile[2] = 0.01f; vert_back_tile[3] = min_x; vert_back_tile[4] = min_y;
	vert_back_tile[5] = -bx + del_x; vert_back_tile[6] = by + del_y; vert_back_tile[7] = 0.01f; vert_back_tile[8] = min_x; vert_back_tile[9] = max_y;
	vert_back_tile[10] = bx + del_x; vert_back_tile[11] = by + del_y; vert_back_tile[12] = 0.01f; vert_back_tile[13] = max_x; vert_back_tile[14] = max_y;
	vert_back_tile[15] = -bx + del_x; vert_back_tile[16] = -by + del_y; vert_back_tile[17] = 0.01f; vert_back_tile[18] = min_x; vert_back_tile[19] = min_y;
	vert_back_tile[20] = bx + del_x; vert_back_tile[21] = -by + del_y; vert_back_tile[22] = 0.01f; vert_back_tile[23] = max_x; vert_back_tile[24] = min_y;
	vert_back_tile[25] = bx + del_x; vert_back_tile[26] = by + del_y; vert_back_tile[27] = 0.01f; vert_back_tile[28] = max_x; vert_back_tile[29] = max_y;
}

void GameGUI::SetLifeBarVert(const Player& player) {
	int life = (int)player.Get_playerLife();
	float minx = -1.0f;
	float maxx = -1.0f + tile_width;
	float miny = 1.0f - tile_height;
	float maxy = 1.0f;
	for (int i = 0; i < 4; ++i) {
		TexCoords cur;
		if (life / 2 > 0) {
			cur = it_cache["full_life"];
		}

		else if (life % 2 > 0) {
			cur = it_cache["half_life"];
		}

		else {
			cur = it_cache["empty_life"];
		}

		int e = i * 5 * 6;
		float mintx = (float)cur.min_x * 16.0f / (float)texture->Width();
		float maxtx = (float)cur.max_x * 16.0f / (float)texture->Width();
		float minty = (float)cur.min_y * 16.0f / (float)texture->Height();
		float maxty = (float)cur.max_y * 16.0f / (float)texture->Height();

		life_bar_vert[e] = minx; life_bar_vert[e + 1] = miny; life_bar_vert[e + 2] = 0.0f; life_bar_vert[e + 3] = mintx; life_bar_vert[e + 4] = minty;
		life_bar_vert[e + 5] = minx; life_bar_vert[e + 6] = maxy; life_bar_vert[e + 7] = 0.0f; life_bar_vert[e + 8] = mintx; life_bar_vert[e + 9] = maxty;
		life_bar_vert[e + 10] = maxx; life_bar_vert[e + 11] = maxy; life_bar_vert[e + 12] = 0.0f; life_bar_vert[e + 13] = maxtx; life_bar_vert[e + 14] = maxty;
		life_bar_vert[e + 15] = minx; life_bar_vert[e + 16] = miny; life_bar_vert[e + 17] = 0.0f; life_bar_vert[e + 18] = mintx; life_bar_vert[e + 19] = minty;
		life_bar_vert[e + 20] = maxx; life_bar_vert[e + 21] = miny; life_bar_vert[e + 22] = 0.0f; life_bar_vert[e + 23] = maxtx; life_bar_vert[e + 24] = minty;
		life_bar_vert[e + 25] = maxx; life_bar_vert[e + 26] = maxy; life_bar_vert[e + 27] = 0.0f; life_bar_vert[e + 28] = maxtx; life_bar_vert[e + 29] = maxty;

		life -= 2;
		minx += tile_width + length_between_tiles;
		maxx += tile_width + length_between_tiles;
	}
}

void GameGUI::ResetLifeBarVert(const Player& player) {
	SetLifeBarVert(player);
	life_bar_mesh->SetVertexBufWithTex(life_bar_vert, 4 * 5 * 6);
}

void GameGUI::DrawLifeBar(const Player& player) {
	ResetLifeBarVert(player);
	texture_Shader->bind();
	texture->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(1.0f, 1.0f, 1.0f));
	life_bar_mesh->Draw_Mesh();
	texture->unbind();
	texture_Shader->unbind();
}

void GameGUI::DrawCurWeapon(const Player& player) {

	ResetCurWeaponTile(tile_width / 2.0f + length_between_tiles * 2.0f, tile_height / 2.0f + length_between_tiles * 4.0f, -1.0f + tile_width / 2.0f + length_between_tiles * 2.0f, 1.0f - tile_height - tile_height / 2.0f - length_between_tiles * 4.0f, it_cache[player.GetCurWeapon()]);

	texture_Shader->bind();

	textureb->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(0.5f, 0.5f, 0.5f));
	bg_tile_mesh->Draw_Mesh();
	textureb->unbind();

	texture->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(1.0f, 1.0f, 1.0f));
	cur_weapon_mesh->Draw_Mesh();
	texture->unbind();

	texture_Shader->unbind();
}

void GameGUI::DrawPlayerInteface(const Player& player) {
	DrawLifeBar(player);
	DrawCurWeapon(player);
}

void GameGUI::SetCurWeaponTile(float bx, float by, float del_x, float del_y, TexCoords cur) {
	float min_x = (float)cur.min_x * 16.0f / (float)texture->Width();
	float max_x = (float)cur.max_x * 16.0f / (float)texture->Width();
	float min_y = (float)cur.min_y * 16.0f / (float)texture->Height();
	float max_y = (float)cur.max_y * 16.0f / (float)texture->Height();

	cur_weapon_tile_vert[0] = -bx + del_x; cur_weapon_tile_vert[1] = -by + del_y; cur_weapon_tile_vert[2] = 0.0f; cur_weapon_tile_vert[3] = min_x; cur_weapon_tile_vert[4] = min_y;
	cur_weapon_tile_vert[5] = -bx + del_x; cur_weapon_tile_vert[6] = by + del_y; cur_weapon_tile_vert[7] = 0.0f; cur_weapon_tile_vert[8] = min_x; cur_weapon_tile_vert[9] = max_y;
	cur_weapon_tile_vert[10] = bx + del_x; cur_weapon_tile_vert[11] = by + del_y; cur_weapon_tile_vert[12] = 0.0f; cur_weapon_tile_vert[13] = max_x; cur_weapon_tile_vert[14] = max_y;
	cur_weapon_tile_vert[15] = -bx + del_x; cur_weapon_tile_vert[16] = -by + del_y; cur_weapon_tile_vert[17] = 0.0f; cur_weapon_tile_vert[18] = min_x; cur_weapon_tile_vert[19] = min_y;
	cur_weapon_tile_vert[20] = bx + del_x; cur_weapon_tile_vert[21] = -by + del_y; cur_weapon_tile_vert[22] = 0.0f; cur_weapon_tile_vert[23] = max_x; cur_weapon_tile_vert[24] = min_y;
	cur_weapon_tile_vert[25] = bx + del_x; cur_weapon_tile_vert[26] = by + del_y; cur_weapon_tile_vert[27] = 0.0f; cur_weapon_tile_vert[28] = max_x; cur_weapon_tile_vert[29] = max_y;
}

void GameGUI::ResetCurWeaponTile(float bx, float by, float del_x, float del_y, TexCoords cur) {
	SetCurWeaponTile(bx, by, del_x, del_y, cur);
	cur_weapon_mesh->SetVertexBufWithTex(cur_weapon_tile_vert, 5 * 6);
}

GameGUI::~GameGUI() {
	delete texture;
	delete textureb;
	delete life_bar_mesh;
	delete bg_tile_mesh;
	delete texture_Shader;
	delete[] vert_back_tile;
	delete[] life_bar_vert;
	delete cur_weapon_mesh;
	delete[] cur_weapon_tile_vert;
}