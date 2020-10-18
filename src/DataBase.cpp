#include "DataBase.h"

vector3f Saver::GetV3(int row)
{
    vector3f v3;

    libxl::Book* database = xlCreateBook();
    database->load("DataBase.xls");
    libxl::Sheet* saver = database->getSheet(0);

    for (int i = 1; i <= 3; i++)
    {
        float s = saver->readNum(row, i);
        v3.mas[i - 1] = s;
    }
    return v3;
}


std::vector<float> Saver::GetMas(int row, int quantity)
{
    std::vector<float> v;

    libxl::Book* database = xlCreateBook();
    database->load("DataBase.xls");
    libxl::Sheet* saver = database->getSheet(0);

    for (int i = 1; i <= quantity; i++)
    {
        float s = saver->readNum(row, i);
        v.push_back(s);
    }
    return v;
}

void Saver::SetSave_mas(int row, int* mas, int num)
{
    libxl::Book* database = xlCreateBook();
    if (database) {
        if (database->load("DataBase.xls")) {
            libxl::Sheet* saver = database->getSheet(0);
            if (saver) {
                for (int i = 1; i <= num; i++) {
                    saver->writeNum(row, i, mas[i]);
                }
            }
        }
        else {
            libxl::Sheet* saver = database->addSheet("Save");
            database->save("DataBase.xls");
            database->release();
            SetSave_mas(row, mas, num);
        }
    }
    database->save("DataBase.xls");
}


void Saver::SetSave_v3(int row, vector3f v3)
{
    libxl::Book* database = xlCreateBook();
    if (database) {
        if (database->load("DataBase.xls")) {
            libxl::Sheet* saver = database->getSheet(0);
            if (saver) {
                for (int i = 1; i <= 3; i++) {
                    saver->writeNum(row, i, v3.mas[i]);
                }
            }
        }
        else {
            libxl::Sheet* saver = database->addSheet("Save");
            database->save("DataBase.xls");
            database->release();
            SetSave_v3(row, v3);
        }
    }
    database->save("DataBase.xls");
}
