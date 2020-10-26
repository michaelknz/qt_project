#include "Room_1.h"

Room_1::Room_1() {

}

Room_1::~Room_1() {

}

void Room_1::SetRoomMap() {
	Map_width = 32;
	Map_height = 16;
	tile_tex_width = 8;
	tile_tex_height = 8;
	Map = "EUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUC"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFDFFFFFFFFFFFFFFFFFFFFFFFFDFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFDFFFFFFFFFFFFFFFFFFFFFFFFDFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "LFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFR"
		  "AUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUB";

	walls.insert('U');
	walls.insert('R');
	walls.insert('L');
}

void Room_1::SetTexMap() {
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