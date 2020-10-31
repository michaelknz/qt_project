#ifndef CHEST_H
#define CHEST_H
#include <string>
#include "Matrix.h"

struct Chest {
	std::string item;
	vector3f pos;
	Chest(std::string it, vector3f p);
	Chest();
};

#endif