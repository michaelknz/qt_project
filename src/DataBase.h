#ifndef DATABASE_H
#define DATABASE_H

#include "libxl.h"
#include "Matrix.h"
#include <vector>

class Saver {
public:
	vector3f GetV3(int row);
	std::vector<float> GetMas(int row, int quantity);

	void SetSave_mas(int row, int* mas, int num);
	void SetSave_v3(int row, vector3f v3);

private:
	libxl::Book* database;
	libxl::Sheet* saver;
};

#endif