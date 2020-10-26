#ifndef ROOM_3_H
#define ROOM_3_H
#include "Room_Base.h"

class Room_3 :public Room_Base {
public:
	Room_3();
	~Room_3();
	void SetRoomMap() override;
	void SetTexMap() override;
};

#endif