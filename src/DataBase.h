#ifndef DATABASE_H
#define DATABASE_H

#include "libxl.h"
#include "Matrix.h"
#include <vector>

class DataBase {
public:
	DataBase();
	static void Save_mas(int* mas, int num);
	static void Get_mas(int* mas, int num);
	static bool Have_DataBase();
	~DataBase();
};

#endif