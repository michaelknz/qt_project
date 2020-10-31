#include "DataBase.h"

DataBase::DataBase() {
}

void DataBase::Save_mas(int* mas, int num) {
	libxl::Book* database = xlCreateBook();
	if (database->load("DataBase.xls")) {
		libxl::Sheet* sheet = database->getSheet(0);
		sheet->clear();
		for (int i = 0; i < num; ++i) {
			sheet->writeNum(1, i, mas[i]);
		}
		database->save("DataBase.xls");
	}

	else {
		libxl::Sheet* saver = database->addSheet("Save");
		database->save("DataBase.xls");
		database->release();
		Save_mas(mas, num);
	}
}

void DataBase::Get_mas(int* mas, int num) {
	libxl::Book* database = xlCreateBook();
	database->load("DataBase.xls");
	libxl::Sheet* sheet = database->getSheet(0);
	for (int i = 0; i < num; ++i) {
		mas[i] = sheet->readNum(1, i);
	}
}

bool DataBase::Have_DataBase() {
	libxl::Book* database = xlCreateBook();
	return database->load("DataBase.xls");
}

DataBase::~DataBase() {

}