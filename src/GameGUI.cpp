#include "GameGUI.h"

TexCoords::TexCoords(int minx, int maxx, int miny, int maxy) {
	min_x = minx;
	max_y = maxy;
	min_y = miny;
	max_x = maxx;
}

GameGUI::GameGUI(const Player& player) {
	tile_size = 0.05f;
	is_pushed = false;
	tile_width = tile_size;
	tile_height = tile_size * 2.0f;
	length_between_tiles = 0.005f;
	texture = new Texture("GUI.png");
	textureb = new Texture("GUIb.png");
	texture_Shader = new Shader("GUItexShade");
	color_Shader = new Shader("color_Shade");
	vert_back_tile = new float[6 * 5];
	cur_weapon_tile_vert = new float[6 * 5];
	vert_chest_back_tile = new float[6 * 5];
	life_bar_vert = new float[4 * 5 * 6];
	vert_color_tile = new float[5 * 6];
	vert_letters = new float[10 * 5 * 6];
	vert_color_tile_end = new float[5 * 6];
	vert_end_ok = new float[2 * 5 * 6];

	it_cache["full_life"] = TexCoords(42, 43, 11, 12);
	it_cache["half_life"] = TexCoords(41, 42, 11, 12);
	it_cache["empty_life"] = TexCoords(40, 41, 11, 12);
	it_cache["small_sword"] = TexCoords(34, 35, 15, 16);
	it_cache["sword"] = TexCoords(32, 33, 14, 15);
	it_cache["sharped_sword"] = TexCoords(34, 35, 13, 14);
	it_cache["old_sword"] = TexCoords(36, 37, 14, 15);

	SetLifeBarVert(player);
	SetLetters();
	SetColorVert(0.1f, 0.2f);
	SetChestBgVert(0.2f, 0.4f);
	SetLetterVert();
	SetBackgroundTile(tile_width / 2.0f + length_between_tiles * 2.0f, tile_height / 2.0f + length_between_tiles * 4.0f, -1.0f + tile_width / 2.0f + length_between_tiles * 2.0f, 1.0f - tile_height - tile_height / 2.0f - length_between_tiles * 4.0f);
	SetCurWeaponTile(tile_width / 2.0f + length_between_tiles * 2.0f, tile_height / 2.0f + length_between_tiles * 4.0f, -1.0f + tile_width / 2.0f + length_between_tiles * 2.0f, 1.0f - tile_height - tile_height / 2.0f - length_between_tiles * 4.0f, it_cache[player.GetCurWeapon()]);
	SetColorEndVert();
	SetOkVert();

	life_bar_mesh = new Mesh(life_bar_vert, 4 * 5 * 6);
	bg_tile_mesh = new Mesh(vert_back_tile, 5 * 6);
	cur_weapon_mesh = new Mesh(cur_weapon_tile_vert, 5 * 6);
	bg_chest_tile_mesh = new Mesh(vert_chest_back_tile, 5 * 6);
	color_tile_mesh = new Mesh(vert_color_tile, 5 * 6);
	letter_end_mesh = new Mesh(vert_letters, 10 * 5 * 6);
	color_tile_end_mesh = new Mesh(vert_color_tile_end, 5 * 6);
	end_ok_mesh = new Mesh(vert_end_ok, 2 * 5 * 6);
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

void GameGUI::SetCurChest(Chest ch) {
	cur_chest.item = ch.item;
	cur_chest.pos = ch.pos;
}

void GameGUI::DrawChest(float mouse_x, float mouse_y, bool is_pushed) {

	float x = (2.0f / 1600.0f) * mouse_x - 1.0f;
	float y = ((2.0f / 800.0f) * mouse_y - 1.0f) * (-1.0f);

	ResetCurWeaponTile(0.1f, 0.2f, 0.0f, 0.0f, it_cache[cur_chest.item]);

	texture_Shader->bind();

	textureb->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(0.7f, 0.7f, 0.7f));
	bg_chest_tile_mesh->Draw_Mesh();
	textureb->unbind();

	texture_Shader->unbind();

	color_Shader->bind();
	if (y <= 0.2f && y >= -0.2f && x <= 0.1f && x >= -0.1f && is_pushed) {
		color_Shader->SetUniform3f("color", vector3f(0.5f, 0.5f, 0.7f));
	}
	else {
		color_Shader->SetUniform3f("color", vector3f(0.4f, 0.4f, 0.445f));
	}
	color_tile_mesh->Draw_Mesh();

	color_Shader->unbind();

	texture_Shader->bind();

	texture->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(1.0f, 1.0f, 1.0f));
	cur_weapon_mesh->Draw_Mesh();
	texture->unbind();

	texture_Shader->unbind();
}

void GameGUI::SetChestBgVert(float bx, float by) {
	float min_x = 190.0f / (float)textureb->Width();
	float max_x = 290.0f / (float)textureb->Width();
	float min_y = 412.0f / (float)textureb->Height();
	float max_y = 512.0f / (float)textureb->Height();

	vert_chest_back_tile[0] = -bx; vert_chest_back_tile[1] = -by; vert_chest_back_tile[2] = 0.01f; vert_chest_back_tile[3] = min_x; vert_chest_back_tile[4] = min_y;
	vert_chest_back_tile[5] = -bx; vert_chest_back_tile[6] = by; vert_chest_back_tile[7] = 0.01f; vert_chest_back_tile[8] = min_x; vert_chest_back_tile[9] = max_y;
	vert_chest_back_tile[10] = bx; vert_chest_back_tile[11] = by; vert_chest_back_tile[12] = 0.01f; vert_chest_back_tile[13] = max_x; vert_chest_back_tile[14] = max_y;
	vert_chest_back_tile[15] = -bx; vert_chest_back_tile[16] = -by; vert_chest_back_tile[17] = 0.01f; vert_chest_back_tile[18] = min_x; vert_chest_back_tile[19] = min_y;
	vert_chest_back_tile[20] = bx; vert_chest_back_tile[21] = -by; vert_chest_back_tile[22] = 0.01f; vert_chest_back_tile[23] = max_x; vert_chest_back_tile[24] = min_y;
	vert_chest_back_tile[25] = bx; vert_chest_back_tile[26] = by; vert_chest_back_tile[27] = 0.01f; vert_chest_back_tile[28] = max_x; vert_chest_back_tile[29] = max_y;
}

void GameGUI::SetColorVert(float bx, float by) {
	vert_color_tile[0] = -bx; vert_color_tile[1] = -by; vert_color_tile[2] = 0.005f; vert_color_tile[3] = 0.0f; vert_color_tile[4] = 0.0f;
	vert_color_tile[5] = -bx; vert_color_tile[6] = by; vert_color_tile[7] = 0.005f; vert_color_tile[8] = 0.0f; vert_color_tile[9] = 0.0f;
	vert_color_tile[10] = bx; vert_color_tile[11] = by; vert_color_tile[12] = 0.005f; vert_color_tile[13] = 0.0f; vert_color_tile[14] = 0.0f;
	vert_color_tile[15] = -bx; vert_color_tile[16] = -by; vert_color_tile[17] = 0.005f; vert_color_tile[18] = 0.0f; vert_color_tile[19] = 0.0f;
	vert_color_tile[20] = bx; vert_color_tile[21] = -by; vert_color_tile[22] = 0.005f; vert_color_tile[23] = 0.0f; vert_color_tile[24] = 0.0f;
	vert_color_tile[25] = bx; vert_color_tile[26] = by; vert_color_tile[27] = 0.005f; vert_color_tile[28] = 0.0f; vert_color_tile[29] = 0.0f;
}

Chest GameGUI::GetCurChest() {
	return cur_chest;
}

void GameGUI::SetChestItem(std::string it) {
	cur_chest.item = it;
}

void GameGUI::SetLetters() {
	letters['A'] = TexCoords(35, 36, 3, 4); letters['B'] = TexCoords(36, 37, 3, 4); letters['C'] = TexCoords(37, 38, 3, 4); letters['D'] = TexCoords(38, 39, 3, 4);
	letters['E'] = TexCoords(39, 40, 3, 4); letters['F'] = TexCoords(40, 41, 3, 4); letters['G'] = TexCoords(41, 42, 3, 4); letters['H'] = TexCoords(42, 43, 3, 4);
	letters['I'] = TexCoords(43, 44, 3, 4); letters['J'] = TexCoords(44, 45, 3, 4); letters['K'] = TexCoords(45, 46, 3, 4); letters['L'] = TexCoords(46, 47, 3, 4);
	letters['M'] = TexCoords(47, 48, 3, 4); letters['N'] = TexCoords(35, 36, 2, 3); letters['O'] = TexCoords(36, 37, 2, 3); letters['P'] = TexCoords(37, 38, 2, 3);
	letters['Q'] = TexCoords(38, 39, 2, 3); letters['R'] = TexCoords(39, 40, 2, 3); letters['S'] = TexCoords(40, 41, 2, 3); letters['T'] = TexCoords(41, 42, 2, 3);
	letters['U'] = TexCoords(42, 43, 2, 3); letters['V'] = TexCoords(43, 44, 2, 3); letters['W'] = TexCoords(44, 45, 2, 3); letters['X'] = TexCoords(45, 46, 2, 3);
	letters['Y'] = TexCoords(46, 47, 2, 3); letters['Z'] = TexCoords(47, 48, 2, 3);
}

void GameGUI::SetLetterVert() {
	std::string s = "YOU ARE DEAD";

	float x = -0.21f;
	float y = 0.4f;
	float del_x = 0.035f;
	float del_y = 0.07f;
	int e = 0;

	for (int i = 0; i < s.length(); ++i) {
		if (s[i] == ' ') {
			x += del_x;
			continue;
		}
		float min_x = (float)letters[s[i]].min_x * 16.0f / (float)texture->Width();
		float max_x = (float)letters[s[i]].max_x * 16.0f / (float)texture->Width();
		float min_y = (float)letters[s[i]].min_y * 16.0f / (float)texture->Height();
		float max_y = (float)letters[s[i]].max_y * 16.0f / (float)texture->Height();

		vert_letters[e] = x; vert_letters[e + 1] = y - del_y; vert_letters[e + 2] = 0.0f; vert_letters[e + 3] = min_x; vert_letters[e + 4] = min_y;
		vert_letters[e + 5] = x; vert_letters[e + 6] = y; vert_letters[e + 7] = 0.0f; vert_letters[e + 8] = min_x; vert_letters[e + 9] = max_y;
		vert_letters[e + 10] = x + del_x; vert_letters[e + 11] = y; vert_letters[e + 12] = 0.0f; vert_letters[e + 13] = max_x; vert_letters[e + 14] = max_y;
		vert_letters[e + 15] = x; vert_letters[e + 16] = y - del_y; vert_letters[e + 17] = 0.0f; vert_letters[e + 18] = min_x; vert_letters[e + 19] = min_y;
		vert_letters[e + 20] = x + del_x; vert_letters[e + 21] = y - del_y; vert_letters[e + 22] = 0.0f; vert_letters[e + 23] = max_x; vert_letters[e + 24] = min_y;
		vert_letters[e + 25] = x + del_x; vert_letters[e + 26] = y; vert_letters[e + 27] = 0.0f; vert_letters[e + 28] = max_x; vert_letters[e + 29] = max_y;
		x += del_x;
		e += 30;
	}
}

void GameGUI::SetColorEndVert() {
	vert_color_tile_end[0] = -0.08f; vert_color_tile_end[1] = -0.38f; vert_color_tile_end[2] = 0.0f; vert_color_tile_end[3] = 0.0f; vert_color_tile_end[4] = 0.0f;
	vert_color_tile_end[5] = -0.08f; vert_color_tile_end[6] = -0.25f; vert_color_tile_end[7] = 0.0f; vert_color_tile_end[8] = 0.0f; vert_color_tile_end[9] = 0.0f;
	vert_color_tile_end[10] = 0.08f; vert_color_tile_end[11] = -0.25f; vert_color_tile_end[12] = 0.0f; vert_color_tile_end[13] = 0.0f; vert_color_tile_end[14] = 0.0f;
	vert_color_tile_end[15] = -0.08f; vert_color_tile_end[16] = -0.38f; vert_color_tile_end[17] = 0.0f; vert_color_tile_end[18] = 0.0f; vert_color_tile_end[19] = 0.0f;
	vert_color_tile_end[20] = 0.08f; vert_color_tile_end[21] = -0.38f; vert_color_tile_end[22] = 0.0f; vert_color_tile_end[23] = 0.0f; vert_color_tile_end[24] = 0.0f;
	vert_color_tile_end[25] = 0.08f; vert_color_tile_end[26] = -0.25f; vert_color_tile_end[27] = 0.0f; vert_color_tile_end[28] = 0.0f; vert_color_tile_end[29] = 0.0f;
}

void GameGUI::DrawEndScreen() {
	SetBackgroundTile(0.25f, 0.5f, 0.0f, 0.0f);
	bg_tile_mesh->SetVertexBufWithTex(vert_back_tile, 5 * 6);
	texture_Shader->bind();

	textureb->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(0.5f, 0.3f, 0.3f));
	bg_tile_mesh->Draw_Mesh();
	textureb->unbind();

	texture->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(1.0f, 1.0f, 1.0f));
	letter_end_mesh->Draw_Mesh();
	texture->unbind();

	texture_Shader->unbind();

	color_Shader->bind();
	if (is_pushed) {
		color_Shader->SetUniform3f("color", vector3f(0.4f, 0.2f, 0.2f));
	}
	else {
		color_Shader->SetUniform3f("color", vector3f(0.5f, 0.3f, 0.3f));
	}
	color_tile_end_mesh->Draw_Mesh();
	color_Shader->unbind();

	texture_Shader->bind();
	texture->bind();
	texture_Shader->SetUniform3f("color_mul", vector3f(1.0f, 1.0f, 1.0f));
	end_ok_mesh->Draw_Mesh();
	texture->unbind();
	texture_Shader->unbind();
}

void GameGUI::SetOkVert() {
	std::string s = "OK";
	float x = -0.035f;
	float y = -0.28f;
	float del_x = 0.035f;
	float del_y = 0.07f;
	int e = 0;

	for (int i = 0; i < s.length(); ++i) {
		float min_x = (float)letters[s[i]].min_x * 16.0f / (float)texture->Width();
		float max_x = (float)letters[s[i]].max_x * 16.0f / (float)texture->Width();
		float min_y = (float)letters[s[i]].min_y * 16.0f / (float)texture->Height();
		float max_y = (float)letters[s[i]].max_y * 16.0f / (float)texture->Height();

		vert_end_ok[e] = x; vert_end_ok[e + 1] = y - del_y; vert_end_ok[e + 2] = -0.01f; vert_end_ok[e + 3] = min_x; vert_end_ok[e + 4] = min_y;
		vert_end_ok[e + 5] = x; vert_end_ok[e + 6] = y; vert_end_ok[e + 7] = -0.01f; vert_end_ok[e + 8] = min_x; vert_end_ok[e + 9] = max_y;
		vert_end_ok[e + 10] = x + del_x; vert_end_ok[e + 11] = y; vert_end_ok[e + 12] = -0.01f; vert_end_ok[e + 13] = max_x; vert_end_ok[e + 14] = max_y;
		vert_end_ok[e + 15] = x; vert_end_ok[e + 16] = y - del_y; vert_end_ok[e + 17] = -0.01f; vert_end_ok[e + 18] = min_x; vert_end_ok[e + 19] = min_y;
		vert_end_ok[e + 20] = x + del_x; vert_end_ok[e + 21] = y - del_y; vert_end_ok[e + 22] = -0.01f; vert_end_ok[e + 23] = max_x; vert_end_ok[e + 24] = min_y;
		vert_end_ok[e + 25] = x + del_x; vert_end_ok[e + 26] = y; vert_end_ok[e + 27] = -0.01f; vert_end_ok[e + 28] = max_x; vert_end_ok[e + 29] = max_y;
		x += del_x;
		e += 30;
	}
}

void GameGUI::SetIsPush(bool flag) {
	is_pushed = flag;
}

GameGUI::~GameGUI() {
	delete texture;
	delete textureb;
	delete life_bar_mesh;
	delete bg_tile_mesh;
	delete texture_Shader;
	delete color_Shader;
	delete[] vert_back_tile;
	delete[] life_bar_vert;
	delete cur_weapon_mesh;
	delete[] cur_weapon_tile_vert;
	delete[] vert_chest_back_tile;
	delete bg_chest_tile_mesh;
	delete[] vert_letters;
	delete letter_end_mesh;
	delete end_ok_mesh;
	delete[] vert_color_tile_end;
	delete[] vert_end_ok;
}