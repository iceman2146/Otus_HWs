#pragma once
#include <string>
struct person
{
    std::string user_name = "none";
    int attempt = 0;
};
int CreateandWriteinFile(person p);
int ReadFile();
void qSortMas(person *, int);
void removeNulEllemFromMas(person *, int &);
void removeDuplicatedEllemFromMas(person *, int &);