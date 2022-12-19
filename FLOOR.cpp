#include "FLOOR.h"
#include <fstream>
#include <ctime>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
using namespace std;


Room::Room(){
    room_size=20;
    cout<<"Конструктор комнаты";
    room_configuration = new int* [room_size];
    for (int i=0; i<room_size;i++)
        room_configuration[i] = new int[room_size];
}

Room::Room(const Room &r1) {
    this->room_size = r1.room_size;
    this->room_type = r1.room_type;
    for(int i = 0; i < 4; i++)
        this->doors[i] = r1.doors[i];
    this->room_configuration = new int*[this->room_size];
    for(int i = 0; i < this->room_size; i++)
        this->room_configuration[i] = new int[this->room_size];
    for(int i = 0; i < this->room_size; i++){
        for(int j = 0; j < this->room_size; j++){
            this->room_configuration[i][j] = r1.room_configuration[i][j];
        }
    }
}

Room::~Room(){
    for (int i =0; i<room_size;i++)
            delete[] room_configuration[i];
    delete room_configuration;
}


Room Room::operator=(const Room &r) {
    for(int i = 0; i < this->room_size; i++)
        delete[] this->room_configuration[i];
    delete[] this->room_configuration;
    this->room_size = r.room_size;
    this->room_type = r.room_type;
    for(int i = 0; i < 4; i++)
        this->doors[i] = r.doors[i];
    this->room_configuration = new int*[this->room_size];
    for(int i = 0; i < this->room_size; i++)
        this->room_configuration[i] = new int[this->room_size];
    for(int i = 0; i < this->room_size; i++){
        for(int j = 0; j < this->room_size; j++){
            this->room_configuration[i][j] = r.room_configuration[i][j];
        }
    }
    return *this;
}



FLoor::FLoor(int size1, int h, int w){
    cout<<"Конструктор этажа";
    size = size1;
    FLoor_Height = h;
    FLoor_Width = w;
    THE_FLOOR = new Room* [FLoor_Height];
    for (int count = 0; count < FLoor_Height; count++)  //Выделяем место под этаж, так как он квадратный, то место выделять придется под весь квадрат
        THE_FLOOR[count] = new Room [FLoor_Width];    //На самом деле это очень неприятно,  но я подумаю, как это можно будет изменить, но пока так
}

int FLoor::GetSize() {return size;}
int FLoor::GetH() {return FLoor_Height;}
int FLoor::GetW() {return FLoor_Width;}
Room** FLoor::GetFloor() {return THE_FLOOR;}

 FLoor::~FLoor(){
    ClearFLoor();
    delete THE_FLOOR;
}


void FLoor::ChangeSize(int newsize)
{
    size=newsize;
}

void FLoor::ClearFLoor() {
    for (int count = 0; count < FLoor_Height; count++)  //Выделяем место под этаж, так как он квадратный, то место выделять придется под весь квадрат
        delete [] THE_FLOOR[count];
}

Room FLoor::ReadRoom(const char *filename,int type) {    //по-хорошему, из файла комнаты должны быть считаны все ее данные
    cout<<"Создание потока...?";
    ifstream F(filename);
    Room* NewRoom;
    NewRoom = new Room;
    if (!F.is_open())
        throw "ROOM_ERROR1 - ошибка файла комнаты. Комната не найдена \n";
    F >> NewRoom->room_size;
    if (!strcmp("start_room.txt", filename)) NewRoom->room_type = 0;
    else NewRoom->room_type = type; // нетнетнетнетнетнетнетнет!!!!!!!!!!!!!!!! пока подразумевается, что есть только комнаты 0-типа и 1-типа, поэтому тут так, но вообще будет определение, придумаю
    F >> NewRoom->doors[0] >> NewRoom->doors[1] >> NewRoom->doors[2] >> NewRoom->doors[3];
    for (int i = 0; i < NewRoom->room_size; i++) {
        for (int j = 0; j < NewRoom->room_size; j++) {
            F >> NewRoom->room_configuration[i][j];
            // cout << NewRoom->room_configuration[i][j] << " ";
        }
        //  cout << '\n';
    }
    F.close();
    return *NewRoom;
}

void FLoor::AddRoom(Room* R, int x, int y) {
    cout<<R->doors[0]<<" "<<R->doors[1]<<" "<<R->doors[2]<<" "<<R->doors[3];
    THE_FLOOR[y][x] = *R;
    cout<<"ВСТАВКА ПРОИЗОШЛА!!!!!!!!!!!!!"<<endl;
    cout<<"Координаты комнаты в массиве: "<< y << " "<< x<<endl;
    cout<<"Параметры комнаты:"<<endl;
    cout<<R->room_type << " - Тип комнаты"<<endl;
    cout<<"Массив дверей: (U,R,D,L) ";
    for (int i=0;i<4;i++) cout<<R->doors[i]<<" ";
    cout<<endl;
}

void FLoor::MakeNull() {
    Room Blank;
    Blank.room_type = 404;
    for (int i = 0; i < 4; i++) Blank.doors[i] = true;
    Blank.room_configuration[0][0] = 1;
    for (int i = 0; i < FLoor_Height; i++){
        for (int j = 0; j < FLoor_Width; j++) {
            THE_FLOOR[i][j] = Blank;
            cout<<THE_FLOOR[i][j].room_type<<" "; }
        cout<<endl; }
}
void FLoor::SetStartRoom(int x, int y) {
    Room* Temp;
    Temp = new Room;
    *Temp = ReadRoom("start_room.txt",0);
    AddRoom(Temp, x, y);
}





/*
bool tempdoors[4] = {0, 0, 0, 0}; //массив треований для комнаты
if (y + 1 < FLoor_Height)
    if (THE_FLOOR[y + 1][x].room_type != 404 && THE_FLOOR[y + 1][x].room_type != 2 &&
        THE_FLOOR[y + 1][x].doors[0] == 1) {
        flag = true;
        tempdoors[2] = 1;
    } else if (THE_FLOOR[y + 1][x].room_type == 404) tempdoors[2] = 1;
if (y - 1 >= 0)
    if (THE_FLOOR[y - 1][x].room_type != 404 && THE_FLOOR[y - 1][x].room_type != 2 &&
        THE_FLOOR[y - 1][x].doors[2] == 1) {
        flag = true;
        tempdoors[0] = 1;
    } else if (THE_FLOOR[y - 1][x].room_type == 404) tempdoors[0] = 1;
if (x + 1 < FLoor_Width)
    if (THE_FLOOR[y][x + 1].room_type != 404 && THE_FLOOR[y][x + 1].room_type != 2 &&
        THE_FLOOR[y][x + 1].doors[3] == 1) {
        flag = true;
        tempdoors[1] = 1;
    } else if (THE_FLOOR[y][x + 1].room_type == 404) tempdoors[1] = 1;
if (x - 1 >= 0)
    if (THE_FLOOR[y][x - 1].room_type != 404 && THE_FLOOR[y][x - 1].room_type != 2 &&
        THE_FLOOR[y][x - 1].doors[1] == 1) {
        flag = true;
        tempdoors[3] = 1;
    } else if (THE_FLOOR[y][x + 1].room_type == 404) tempdoors[3] = 1;
if (flag == true) {
    cout << "ФЛАГ = 1 ";
    int GenNum = rand() % RoomCount + 1;
    const char *tempname = Names[GenNum]; //BIG КОСТЫЛЬ
    Room R = ReadRoom("room1.txt");
    for (int i = 0; i < 4; i++)
        if (R.doors[i] != tempdoors[i]) {
            if (R.doors[i] == 0) flag = false;
            else R.doors[i] = 0;  //Стенки между комнатами
        }
    if (flag == true) {
        AddRoom(R, x, y);
        K--;
    cout<<"К РАВНО ="<<K<<endl;ddw
    */


void FLoor::GENERATE() {  //ОСНОВНАЯ ВОЗНЯ ТУТ!!! ДАЛЬШЕ БОГА НЕТ!!!!
    MakeNull();
    int x, y, k, i, j, p;
    int L = size;
    bool flag;
    cout << "Этаж обнулен";
    bool **PreList;
    PreList = new bool *[FLoor_Height];
    for (k = 0; k < FLoor_Height; k++)
        PreList[k] = new bool[FLoor_Width];
    for (k = 0; k < FLoor_Height; k++)
        for (p = 0; p < FLoor_Width; p++)
            PreList[k][p] = 0;
    x = rand() % FLoor_Width/2+FLoor_Width/4;
    y = rand() % FLoor_Height/2+FLoor_Height/4;
    PreList[y][x] = 1;
    SetStartRoom(x, y);
    int x1 = x;
    int y1 = y;
    set<pair<int, int>> AvailableForGen;
    cout<<"SetPair done!";
    int AvCount = 0;
    int CheckNum;
    set<pair<int, int>>::iterator it(AvailableForGen.begin());
    cout<<"IT done!";
    while (L) {
        cout<<"-------"<<endl;
        cout<<"y x:"<<y<<" "<<x<<endl;
        CheckRoom(y, x, PreList, &AvailableForGen, &AvCount);
        cout<<"Всего в сете: "<<AvCount<<" ";

        cout<<"сам сет=";
        for(auto&item:AvailableForGen){
            cout<<"-("<<item.first<<','<<item.second<<')';
        }cout<<endl;

        cout<<AvailableForGen.size()<<endl;
        CheckNum = rand() % AvCount;
        cout<<"Random = "<<CheckNum<<endl;
        it = AvailableForGen.begin();
        advance(it, CheckNum);
        cout<<"Advance done!"<<endl;
        cout<<"NEW XY"<<it->first << " "<< it->second<<endl;
        cout<<PreList[it->first][it->second]<<endl;
        if (PreList[it->first][it->second] != 1) {
            PreList[it->first][it->second] = 1;
            L--;
            cout<<"Размер - "<<L<<endl;
            cout<<it->first << " "<< it->second<<endl;
            y=it->first;
            x=it->second;
            AvailableForGen.erase(it);
            AvCount--;
            cout<<"сам сет2=";
            for(auto&item:AvailableForGen){
                cout<<"-("<<item.first<<','<<item.second<<')';
            }cout<<endl;
        }

        it=AvailableForGen.begin();
    }
    AddBossRoom(PreList);
    cout<<"PreList распределен"<<endl;
    for (i=0;i<FLoor_Height;i++)
    {
        for (j=0;j<FLoor_Width;j++)
            cout<<"\t"<<PreList[i][j];
        cout<<endl;
    }
    //PreList[y1][x1] = 0;
    int K = size;
    cout << "Этаж обнулен. Стартовая комната поставлена";
    int N = 7;
    cout<<"ЫЫЫЫЫЫЫЫЫЫы"<<endl;
    Room* RTemp = DoRoomArray(N);
    cout<<"ЫЫЫЫЫЫЫЫЫЫы"<<endl;
    while (K>0) { //Пока можно впихнуть комнату
        for (y = 0; y < FLoor_Height && K>0; y++)
            for (x = 0; x < FLoor_Width && K>0; x++){
                if (PreList[y][x]==1 && THE_FLOOR[y][x].room_type!=0  && THE_FLOOR[y][x].room_type!=99) {
                    Room* RoomArray = new Room[N];
                    for (i=0;i<N;i++)
                        RoomArray[i]=RTemp[i];
                    bool DoorKrits[4] = {1,1,1,1};// 0 -UP  1 - RIGHT  2 - DOWN  3 - LEFT
                    if (y-1>=0) {                                     //СОЗДАЕМ ОБЯЗАТЕЛЬНЫЕ ПАРАМЕТРЫ
                        if (THE_FLOOR[y - 1][x].doors[2] == 0) {      // 1 - OPEN    0 - CLOSE
                            DoorKrits[0] = 0;
                        }
                    }
                    else DoorKrits[0]=0;
                    if (y+1<FLoor_Height) {
                        if (THE_FLOOR[y + 1][x].doors[0] == 0) {
                            DoorKrits[2] = 0;
                        }
                    }
                    else DoorKrits[2] = 0;
                    if (x+1<FLoor_Width) {
                        if (THE_FLOOR[y][x+1].doors[3]==0){
                            DoorKrits[1] = 0;
                        }
                    }
                    else  DoorKrits[1] = 0;
                    if (x-1>=0) {
                        if (THE_FLOOR[y][x-1].doors[1]==0){
                            DoorKrits[3] = 0;
                        }
                    }
                    else DoorKrits[3] = 0;
                    /* Подбор комнаты из массива комнат */
                    cout<<"КРИТЕРИИ РАССТАВЛЕНЫ";
                    int Coun = 0;
                    for (i =0; i<N; i++) {
                        flag = 1;
                        for (j = 0; j < 4; j++) {
                            if (RoomArray[i].doors[j] < DoorKrits[j]) flag = 0;
                        }
                        if (flag) Coun++;
                    }
                    int Randoma = rand() % Coun + 1;
                    Coun = 0;
                    for (i =0; i<N; i++) {
                        flag = 1;
                        for (j = 0; j < 4; j++)
                            if (RoomArray[i].doors[j] < DoorKrits[j]) flag = 0;
                        if (flag) Coun++;
                        if (Coun == Randoma) {
                            for (k=0; k<4;k++)
                                RoomArray[i].doors[k]=DoorKrits[k];
                            AddRoom(RoomArray + i, x, y);
                            K--;
                            break;
                        }
                    }
                }
            }
    }
    CheckEnd();
}

void FLoor::CheckEnd() { //Уборка оставшихся дверей в никуда
    for (int i = 0; i<FLoor_Height; i++)
        for (int j=0; j<FLoor_Width; j++)
            if (THE_FLOOR[i][j].room_type!=404){
                if (i+1<FLoor_Height && THE_FLOOR[i+1][j].room_type == 404) THE_FLOOR[i][j].doors[2]=0;
                if (i-1>=0 && THE_FLOOR[i-1][j].room_type == 404) THE_FLOOR[i][j].doors[0]=0;
                if (j+1<FLoor_Width && THE_FLOOR[i][j+1].room_type == 404) THE_FLOOR[i][j].doors[1]=0;
                if (j-1>=0 && THE_FLOOR[i][j-1].room_type == 404) THE_FLOOR[i][j].doors[3]=0;
            }
}
Room* FLoor::DoBossArray(int BossLen){
    Room* BossArr = new Room[BossLen];
    for (int i=0; i<BossLen; i++)
    {
        int Y=i+1;
        char b[2];
        sprintf(b, "%d", Y);
        const char* RoomName = "boss_room.txt";
        RoomName = strcat(b,RoomName);
        BossArr[i] = ReadRoom(RoomName,99);
        cout<<BossArr[i].room_type<<"ТИП"<<endl;
        cout<<BossArr[i].doors[0]<<"UP DOOR"<<endl;
    }
    return BossArr;
}


Room* FLoor::DoRoomArray(int Len){
    Room* RoomArr = new Room[Len];
    for (int i=0; i<Len; i++)
    {
        int Y=i+1;
        char a[2];
        cout<<"РидРУм";
        sprintf(a, "%d", Y);
        cout<<"РидРУм";
        const char* RoomName = "room.txt";
        RoomName = strcat(a,RoomName);
        RoomArr[i] = ReadRoom(RoomName,Y);
        cout<<RoomArr[i].room_type<<"ТИП"<<endl;
        cout<<RoomArr[i].doors[0]<<"UP DOOR"<<endl;
    }
    return RoomArr;
};


void FLoor::PrintTheFloor() {
    for (int i = 0; i < FLoor_Height; i++){
        for (int j = 0; j < FLoor_Width; j++) {
            cout<<"\t"<<THE_FLOOR[i][j].room_type; }
        cout<<endl; }
}

void FLoor::CheckRoom(int y, int x, bool** a, set<pair<int,int>>* A, int* C)
{
    if (y+1<FLoor_Height && a[y+1][x]!=1){
        pair<int,int> Temp = make_pair(y+1,x);
        if (A->find(Temp) == A->end()) {
            cout<<"Проверка1"<<endl;
            A->insert(Temp);
            *C += 1;
        }
    }
    if (x+1<FLoor_Width && a[y][x+1]!=1){
        pair<int,int> Temp = make_pair(y,x+1);
        if (A->find(Temp) == A->end()) {
            cout<<"Проверка2"<<endl;
            A->insert(Temp);
            *C += 1;
        }
    }
    if (x-1>=0 && a[y][x-1]!=1){
        pair<int,int> Temp = make_pair(y,x-1);
        if (A->find(Temp) == A->end()) {
            cout<<"Проверка3"<<endl;
            A->insert(Temp);
            *C += 1;
        }
    }
    if (y-1>=0 && a[y-1][x]!=1){
        pair<int,int> Temp = make_pair(y-1,x);
        if (A->find(Temp) == A->end()) {
            cout<<"Проверка4"<<endl;
            A->insert(Temp);
            *C += 1;
        }
    }
}

void FLoor::AddBossRoom(bool ** a)
{
    int Nboss=4;
    Room* RBoss = DoBossArray(Nboss);
    int RandBoss;
    RandBoss = rand()% Nboss;
    int i,j;
    for (i=0;i<FLoor_Height;i++)
        for (j=0;j<FLoor_Width;j++){
            if (RandBoss==0){
                if (i+1 < FLoor_Height && a[i][j] == 0 && a[i+1][j] == 1) {
                    AddRoom(&RBoss[RandBoss], j, i);
                    return;
                }

            }
            if (RandBoss==1){
                if (i-1 >=0 && a[i][j] == 0 && a[i][j-1] == 1) {
                    AddRoom(&RBoss[RandBoss], j, i);
                    return;
                }
            }
            if (RandBoss==2){
                if (j+1 < FLoor_Width && a[i][j] == 0 && a[i][j+1] == 1) {
                    AddRoom(&RBoss[RandBoss], j, i);
                    return;
                }
            }
            if (RandBoss==3){
                if (i-1>=0 && a[i][j] == 0 && a[i-1][j] == 1) {
                    AddRoom(&RBoss[RandBoss], j, i);
                    return;
                }
            }
        }
}