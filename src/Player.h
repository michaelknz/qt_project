#include "Matrix.h"

class Player {
public:
	Player();
	void Move_Player(vector3f vec);
	vector3f Get_playerPos();
	float Get_playerSpeed();
private:
	vector3f player_pos;
	float speed;
};