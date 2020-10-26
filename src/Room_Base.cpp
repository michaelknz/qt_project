#include "Room_Base.h"

Room_Base::Room_Base() {
	
}

void Room_Base::Init(const std::string& filename, mat4 view, mat4 proj, vector3f room_pos) {
	projection = proj;
	this->view = view;
	model = Matrix::Translate(room_pos);
	this->room_pos = room_pos;
	enemy = new Enemy(view, projection, room_pos);
	tile_height = 0.15f;
	tile_width = 0.15f;
	doors['u'] = -1;
	doors['d'] = -1;
	doors['l'] = -1;
	doors['r'] = -1;
	texture = new Texture(filename.c_str());
	shader = new Shader("mapShade");
	SetRoomMap();
	verts = new float[Map_height * Map_width * 6 * 5];
	SetTexMap();
	SetVerts();
	mesh = new Mesh(verts, Map_height * Map_width * 6 * 5);
	walls.insert('G');
	walls.insert('K');
	walls.insert('J');
	SetTexMapUnit('G', 4, 5, 7, 8);
	SetTexMapUnit('K', 11, 12, 6, 7);
	SetTexMapUnit('J', 12, 13, 6, 7);
}

void Room_Base::SetRoomMap() {
	Map_width = 32;
	Map_height = 16;
	tile_tex_width = 8;
	tile_tex_height = 8;
	Map = "EUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUC"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFDFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "AUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUB";

	walls.insert('U');
	walls.insert('R');
	walls.insert('L');
}

void Room_Base::SetTexMap() {
	SetTexMapUnit('A', 0, 1, 7, 8);
	SetTexMapUnit('D', 9, 10, 6, 7);
	SetTexMapUnit('U', 1, 2, 9, 10);
	SetTexMapUnit('R', 3, 4, 8, 9);
	SetTexMapUnit('L', 0, 1, 8, 9);
	SetTexMapUnit('F', 1, 2, 8, 9);
	SetTexMapUnit('B', 3, 4, 7, 8);
	SetTexMapUnit('C', 3, 4, 9, 10);
	SetTexMapUnit('E', 0, 1, 9, 10);
}

void Room_Base::SetTexMapUnit(char a, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy) {
	TexCoordMap[a].min_x = (float)(minx * (tile_tex_width)) / (float)texture->Width();
	TexCoordMap[a].max_x = (float)(maxx * (tile_tex_width)) / (float)texture->Width();
	TexCoordMap[a].min_y = (float)(miny * (tile_tex_height)) / (float)texture->Height();
	TexCoordMap[a].max_y = (float)(maxy * (tile_tex_height)) / (float)texture->Height();
}

void Room_Base::SetVerts() {
	float del_x = tile_width;
	float del_y = tile_height;
	float x = -tile_width * (float)Map_width / 2.0f;
	float y = tile_height * (float)Map_height / 2.0f;
	float tmp_x = x;
	float tmp_y = y;
	int j = 0;
	for (int i = 0; i < Map_height; ++i) {
		for (int j = 0; j < Map_width; ++j) {
			int e = (i * Map_width + j) * 30;
			int u = (i * Map_width + j);
			verts[e] = tmp_x; verts[e + 1] = tmp_y; verts[e + 2] = 0.0f; verts[e + 3] = TexCoordMap[Map[u]].min_x; verts[e + 4] = TexCoordMap[Map[u]].max_y;
			verts[e + 5] = tmp_x + del_x; verts[e + 6] = tmp_y; verts[e + 7] = 0.0f; verts[e + 8] = TexCoordMap[Map[u]].max_x; verts[e + 9] = TexCoordMap[Map[u]].max_y;
			verts[e + 10] = tmp_x; verts[e + 11] = tmp_y - del_y; verts[e + 12] = 0.0f; verts[e + 13] = TexCoordMap[Map[u]].min_x; verts[e + 14] = TexCoordMap[Map[u]].min_y;
			verts[e + 15] = tmp_x + del_x; verts[e + 16] = tmp_y; verts[e + 17] = 0.0f; verts[e + 18] = TexCoordMap[Map[u]].max_x; verts[e + 19] = TexCoordMap[Map[u]].max_y;
			verts[e + 20] = tmp_x + del_x; verts[e + 21] = tmp_y - del_y; verts[e + 22] = 0.0f; verts[e + 23] = TexCoordMap[Map[u]].max_x; verts[e + 24] = TexCoordMap[Map[u]].min_y;
			verts[e + 25] = tmp_x; verts[e + 26] = tmp_y - del_y; verts[e + 27] = 0.0f; verts[e + 28] = TexCoordMap[Map[u]].min_x; verts[e + 29] = TexCoordMap[Map[u]].min_y;
			tmp_x += del_x;
		}
		tmp_y -= del_y;
		tmp_x = x;
	}
}

void Room_Base::DrawRoom() {
	shader->bind();
	texture->bind();
	shader->SetUniformMatrix4fv("projection", Matrix::Transplon(projection));
	shader->SetUniformMatrix4fv("view", Matrix::Transplon(view));
	shader->SetUniformMatrix4fv("model", Matrix::Transplon(model));
	mesh->Draw_Mesh();
	texture->unbind();
	shader->unbind();
	enemy->DrawEnemy();
}

void Room_Base::ShutUp() {
	delete texture;
	delete enemy;
	delete mesh;
	delete shader;
	delete[] verts;
}

Room_Base::~Room_Base() {

}

void Room_Base::IsWall(const Player& player, std::unordered_map<int, bool>& keys) {
	vector3f player_pos_in_room = vector3f(player.Get_playerPos().mas[0] - (room_pos.mas[0] - tile_width * (float)Map_width / 2.0f), (room_pos.mas[1] + tile_height * (float)Map_height / 2.0f) - player.Get_playerPos().mas[1], player.Get_playerPos().mas[2]);
	if (keys[Qt::Key_W] && walls.find(Map[(int)((player_pos_in_room.mas[1] - player.Get_playerSpeed()) / tile_height)*Map_width+(int)(player_pos_in_room.mas[0]/tile_width)]) != walls.end()) {
		keys[Qt::Key_W] = false;
	}
	if (keys[Qt::Key_S] && walls.find(Map[(int)((player_pos_in_room.mas[1] + player.Get_playerSpeed()) / tile_height+0.7f)*Map_width+ (int)(player_pos_in_room.mas[0] / tile_width)]) != walls.end()) {
		keys[Qt::Key_S] = false;
	}
	if (keys[Qt::Key_A] && walls.find(Map[(int)((player_pos_in_room.mas[0] - player.Get_playerSpeed()) / tile_width)+(int)(player_pos_in_room.mas[1]/tile_height)*Map_width]) != walls.end()) {
		keys[Qt::Key_A] = false;
	}
	if (keys[Qt::Key_D] && walls.find(Map[(int)((player_pos_in_room.mas[0] + player.Get_playerSpeed()) / tile_width) + (int)(player_pos_in_room.mas[1] / tile_height) * Map_width]) != walls.end()) {
		keys[Qt::Key_D] = false;
	}
}

float Room_Base::GetRoomHeight() const{
	return tile_height * Map_height;
}

float Room_Base::GetRoomWidth() const {
	return tile_width * Map_width;
}

void Room_Base::ResetVerts() {
	SetVerts();
}

void Room_Base::SetDoor(char dir) {
	if (dir == 'u') {
		doors['u'] = Map_width / 2;
		Map[Map_width / 2] = 'G';
	}

	else if (dir == 'd') {
		doors['d'] = (Map_height - 1) * Map_width + Map_width / 2;
		Map[(Map_height - 1) * Map_width + Map_width / 2] = 'G';
	}

	else if (dir == 'l') {
		doors['l'] = (Map_height / 2) * Map_width;
		Map[(Map_height / 2) * Map_width] = 'K';
	}

	else if (dir == 'r') {
		doors['r'] = (Map_height / 2) * Map_width + Map_width - 1;
		Map[(Map_height / 2) * Map_width + Map_width - 1] = 'J';
	}

	ResetVerts();
	mesh->SetVertexBufWithTex(verts, Map_height * Map_width * 6 * 5);
}

vector3f Room_Base::Player_Pos_In_Room(Player* player) {
	vector3f player_pos_in_room = vector3f(player->Get_playerPos().mas[0] - (room_pos.mas[0] - tile_width * (float)Map_width / 2.0f), (room_pos.mas[1] + tile_height * (float)Map_height / 2.0f) - player->Get_playerPos().mas[1], player->Get_playerPos().mas[2]);
	return player_pos_in_room;
}

std::unordered_map<char,int> Room_Base::Get_Doors() const {
	return doors;
}

float Room_Base::Get_Tile_Width() const {
	return tile_width;
}

float Room_Base::Get_Tile_Height() const {
	return tile_height;
}

unsigned int Room_Base::Get_Room_Width_In_Tiles() const {
	return Map_width;
}

unsigned int Room_Base::Get_Room_Height_In_Tiles() const {
	return Map_height;
}

void Room_Base::UpdateCamera(mat4 view) {
	this->view = view;
	enemy->UpdateCamera(view);
}

void Room_Base::UpdateEnemy(const Player& player) {
	enemy->MoveEnemy(player);
}

Enemy* Room_Base::GetEnemy() const {
	return enemy;
}