#pragma once
#include <string>
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct Room{
    unsigned short room_type; //0 - стартовая комната. 1 - обычная комната. 2 - комната босса (на будущее); 404 - ловушка джокера
    //char* room_name; //Нереализованная на данный момент наработка. Пока думаю, что можно обойтись без нее
    int doors[4];      //ПО ЧАСОВОЙ: 0 - ВЕРХ! 1 - ПРАВО! 2 - НИЗ! 3 - ЛЕВО
    int room_size;           //в будущем возможно константа, но пока пусть будет так
    int** room_configuration; //"матрица" комнаты
    Room();
    Room(const Room &r1);
    ~Room();
    Room operator=(const Room &r);
};

class FLoor{
private:
    const int RoomCount= 3;  //Крч, это количество комнат в файле, т.е сколько возможных генераций есть, всегда конст
    int size;
    int FLoor_Height, FLoor_Width;
    Room** THE_FLOOR;
public:
    int FloorNumber=0;
    const char* Names[3] = {"room1.txt" , "room2.txt", "room3.txt"}; //самый большой костыль этой генерации, я не знаю, что с этим делать.....
    FLoor (int size1, int h, int w);
    ~FLoor();
    void MakeNull();

    int GetSize();
    int GetH();
    int GetW();
    Room** GetFloor();

    Room ReadRoom(const char* filename,int type);
    void AddRoom(Room* R, int x, int y);

    void GENERATE();
    void CheckEnd();
    void PrintTheFloor();

    Room* DoRoomArray(int Len);
    Room* DoBossArray(int BossLen);
    void ClearFLoor();
    void CheckRoom(int y, int x, bool** a, set<pair<int,int>>* A, int* C);
    void SetStartRoom(int x, int y);
    void AddBossRoom(bool ** a);
    void DeleteRoom (Room* R);

    void ChangeSize(int newsize);

    void PrintRoom(Room R);
};

