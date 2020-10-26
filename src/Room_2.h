#ifndef ROOM_2_H
#define ROOM_2_H
#include "Room_Base.h"

class Room_2 :public Room_Base {
public:
	Room_2();
	~Room_2();
	void SetRoomMap() override;
	void SetTexMap() override;
};

#endif