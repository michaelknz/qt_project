#include "Level_Base.h"

RoomCoord::RoomCoord(int x, int y) {
	this->x = x;
	this->y = y;
}

Level_Base::Level_Base() {

}

Level_Base::~Level_Base() {

}

void Level_Base::Init(mat4 view, mat4 projection) {

	srand(time(0));
	level_height = 4;
	level_width = 4;
	room_count = 5;
	cur_room_pos = 0;

	level_map = new int[level_height * level_width];
	memset(level_map, 0, level_height * level_width*sizeof(int));
	GenLevelMap();
	SetRoomCache(view, projection);
	SetDoors();
}

void Level_Base::GenLevelMap() {
	int cur_col = 1;
	while (cur_col < room_count) {
		cur_col = 1;
		memset(level_map, 0, level_height * level_width * sizeof(int));
		level_map[0] = 1;
		std::queue<RoomCoord> q;
		q.push(RoomCoord());
		while (!q.empty()) {
			AddRoom(q, cur_col);
		}
	}
}

void Level_Base::AddRoom(std::queue<RoomCoord>& q, int& cur_col) {
	RoomCoord cur = q.front();
	q.pop();
	RoomCoord next(cur.x + 1, cur.y);
	if (Check_Room_In_Map(next) && Is_Room_Empty(next) && Check_Room_Neighbors(next) && cur_col < room_count && rand()%2 == 0) {
		cur_col++;
		level_map[next.y * level_width + next.x] = 1;
		q.push(next);
	}
	next = RoomCoord(cur.x - 1, cur.y);
	if (Check_Room_In_Map(next) && Is_Room_Empty(next) && Check_Room_Neighbors(next) && cur_col < room_count && rand() % 2 == 0) {
		cur_col++;
		level_map[next.y * level_width + next.x] = 1;
		q.push(next);
	}
	next = RoomCoord(cur.x, cur.y + 1);
	if (Check_Room_In_Map(next) && Is_Room_Empty(next) && Check_Room_Neighbors(next) && cur_col < room_count && rand() % 2 == 0) {
		cur_col++;
		level_map[next.y * level_width + next.x] = 1;
		q.push(next);
	}
	next = RoomCoord(cur.x, cur.y - 1);
	if (Check_Room_In_Map(next) && Is_Room_Empty(next) && Check_Room_Neighbors(next) && cur_col < room_count && rand() % 2 == 0) {
		cur_col++;
		level_map[next.y * level_width + next.x] = 1;
		q.push(next);
	}
}

bool Level_Base::Check_Room_In_Map(RoomCoord room) {
	if (room.x >= 0 && room.x < level_width && room.y >= 0 && room.y < level_height) {
		return true;
	}
	else {
		return false;
	}
}

bool Level_Base::Check_Room_Neighbors(RoomCoord room) {
	int output = 0;
	RoomCoord next(room.x + 1, room.y);
	if (Check_Room_In_Map(next) && level_map[next.y * level_width + next.x] == 1) {
		output++;
	}
	next = RoomCoord(room.x - 1, room.y);
	if (Check_Room_In_Map(next) && level_map[next.y * level_width + next.x] == 1) {
		output++;
	}
	next = RoomCoord(room.x, room.y + 1);
	if (Check_Room_In_Map(next) && level_map[next.y * level_width + next.x] == 1) {
		output++;
	}
	next = RoomCoord(room.x, room.y - 1);
	if (Check_Room_In_Map(next) && level_map[next.y * level_width + next.x] == 1) {
		output++;
	}

	return (output <= 1); 
}

bool Level_Base::Is_Room_Empty(RoomCoord room) {
	if (Check_Room_In_Map(room) && level_map[room.y * level_width + room.x] == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Level_Base::DrawRoom(const Player& player, std::unordered_map<int, bool>& keys) {
	cur_room->IsWall(player, keys);
	cur_room->DrawRoom();
}

void Level_Base::ShutUp() {
	delete[] level_map;
	CleanRoomCache();

}

void Level_Base::SetRoomCache(mat4 view, mat4 projection) {
	cur_room = new Room_Base;
	cur_room->Init("sheet.png", view, projection, vector3f(0.0f, 0.0f, 0.0f));
	room_cache[0] = cur_room;
	for (int i = 1; i < level_height * level_width; ++i) {
		if (level_map[i] == 1) {
			room_cache[i] = new Room_Base;
			room_cache[i]->Init("sheet.png", view, projection, vector3f((float)(i % level_width) * cur_room->GetRoomWidth(), (float)(i / level_width) * (-cur_room->GetRoomHeight()), 0.0f));
		}
	}
}

void Level_Base::CleanRoomCache() {
	for (auto i = room_cache.begin(); i != room_cache.end(); ++i) {
		(*i).second->ShutUp();
		delete (*i).second;
	}
}

void Level_Base::SetDoors() {
	for (int i = 0; i < level_height * level_width; ++i) {
		if (level_map[i] == 1) {
			if (Check_Room_In_Map(RoomCoord(i % level_width + 1, i / level_width)) && level_map[i + 1] == 1) {
				room_cache[i]->SetDoor('r');
			}
			if (Check_Room_In_Map(RoomCoord(i % level_width - 1, i / level_width)) && level_map[i - 1] == 1) {
				room_cache[i]->SetDoor('l');
			}
			if (Check_Room_In_Map(RoomCoord(i % level_width, i / level_width - 1)) && level_map[i - level_width] == 1) {
				room_cache[i]->SetDoor('u');
			}
			if (Check_Room_In_Map(RoomCoord(i % level_width, i / level_width + 1)) && level_map[i + level_width] == 1) {
				room_cache[i]->SetDoor('d');
			}
		}
	}
}

void Level_Base::Interact_With_Doors(Player* player, Camera* camera) {
	vector3f player_pos_in_room = cur_room->Player_Pos_In_Room(player);
	int r_pos = cur_room->Get_Doors()['r'];
	int u_pos = cur_room->Get_Doors()['u'];
	int d_pos = cur_room->Get_Doors()['d'];
	int l_pos = cur_room->Get_Doors()['l'];

	vector3f r = vector3f(r_pos % cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Width(), r_pos / cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Height(), 0.0f);
	vector3f u = vector3f(u_pos % cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Width(), u_pos / cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Height(), 0.0f);
	vector3f d = vector3f(d_pos % cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Width(), d_pos / cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Height(), 0.0f);
	vector3f l = vector3f(l_pos % cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Width(), l_pos / cur_room->Get_Room_Width_In_Tiles() * cur_room->Get_Tile_Height(), 0.0f);

	if (r_pos != -1 && Matrix::Length2D(player_pos_in_room, r) <= 1.5f * cur_room->Get_Tile_Width()) {
		player->Move_Player(vector3f(4.0f * cur_room->Get_Tile_Width(), 0.0f, 0.0f));
		camera->Move_Camera(vector3f(cur_room->GetRoomWidth(), 0.0f, 0.0f));
		cur_room = NULL;
		cur_room = room_cache[cur_room_pos + 1];
		cur_room_pos++;
	}
	else if (l_pos != -1 && Matrix::Length2D(player_pos_in_room, l) <= 1.5f * cur_room->Get_Tile_Width()) {
		player->Move_Player(vector3f(-4.0f * cur_room->Get_Tile_Width(), 0.0f, 0.0f));
		camera->Move_Camera(vector3f(-cur_room->GetRoomWidth(), 0.0f, 0.0f));
		cur_room = NULL;
		cur_room = room_cache[cur_room_pos - 1];
		cur_room_pos--;
	}
	else if (d_pos != -1 && Matrix::Length2D(player_pos_in_room, d) <= 1.5f * cur_room->Get_Tile_Width()) {
		player->Move_Player(vector3f(0.0f, -4.0f * cur_room->Get_Tile_Height(), 0.0f));
		camera->Move_Camera(vector3f(0.0f, -cur_room->GetRoomHeight(), 0.0f));
		cur_room = NULL;
		cur_room = room_cache[cur_room_pos + level_width];
		cur_room_pos += level_width;
	}
	else if (u_pos != -1 && Matrix::Length2D(player_pos_in_room, u) <= 1.5f * cur_room->Get_Tile_Width()) {
		player->Move_Player(vector3f(0.0f, 4.0f * cur_room->Get_Tile_Height(), 0.0f));
		camera->Move_Camera(vector3f(0.0f, cur_room->GetRoomHeight(), 0.0f));
		cur_room = NULL;
		cur_room = room_cache[cur_room_pos - level_width];
		cur_room_pos -= level_width;
	}
}

void Level_Base::UpdateCamera(mat4 view) {
	for (auto i = room_cache.begin(); i != room_cache.end(); ++i) {
		(*i).second->UpdateCamera(view);
	}
}
