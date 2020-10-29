#ifndef LEVEL_BASE_H
#define LEVEL_BASE_H
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cstdlib>
#include "Room_Base.h"
#include "Player.h"
#include "Camera.h"
#include "Room_1.h"
#include "Room_2.h"
#include "Room_3.h"
#include "Enemy.h"

struct RoomCoord {
	RoomCoord(int x = 0, int y = 0);
	int x;
	int y;
};

class Level_Base {
public:
	Level_Base();
	~Level_Base();
	void Init(mat4 view, mat4 projection);
	void GenLevelMap();
	void AddRoom(std::queue<RoomCoord>& q, int& cur_col);
	bool Check_Room_In_Map(RoomCoord room);
	bool Check_Room_Neighbors(RoomCoord room);
	bool Is_Room_Empty(RoomCoord room);
	void ShutUp();
	void SetRoomCache(mat4 view, mat4 projection);
	void CleanRoomCache();
	void DrawRoom(const Player& player, std::unordered_map<int, bool>& keys);
	void SetDoors();
	void SetStartRoom(mat4 view, mat4 projection);
	void Interact_With_Doors(Player* player, Camera* camera);
	void UpdateCamera(mat4 view);
	void UpdateEnemyInRoom(const Player& player);
	void AttakCurEnemy(Player& player);
	Enemy* GetCurEnemy() const;
protected:
	unsigned int level_height;
	unsigned int level_width;
	unsigned int room_count;
	int* level_map;
	std::unordered_map<int, Room_Base*> room_cache;
	int cur_room_pos;
	Room_Base* cur_room;
};

#endif