#ifndef ROOM_1_H
#define ROOM_1_H
#include "Room_Base.h"

class Room_1 :public Room_Base {
public:
	Room_1();
	~Room_1();
	void SetRoomMap() override;
	void SetTexMap() override;

};

#endif