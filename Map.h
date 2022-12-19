#pragma once
#include <SDL2/SDL.h>
#include "Camera.h"
#include "Sprite.h"
#include "FLOOR.h"
#include <map>
#include <string>
#include "Player.h"
#include "TypeEnemy.h"
#include "Warrior.h"
#include "fly.h"
using namespace std;
class Map {
private:
    int WINDOW_WIDTH=1920;
    int WINDOW_HEIGHT=1080;

    SDL_Renderer* Render;
    Camera *camera;
    Player *pl;
    map<string, FireBall*> FBalls;
    int count_enemy;
    Sprite *t ;
    int strtta;

public:
    bool dead_boss;
    int startg;
    int cg;
    map<int,TypeEnemy*> Enemy;
    map<string,Sprite*> data[4];
    Sprite* sprite_with_camera;

    Map(SDL_Renderer* ren,Camera* cum);
    void Update(bool *buttons);
    void CameraUpdate();

    int GetCEnemy();

    void add_sprite(Sprite*spr);
    void del_sprite(string name,int layr);
    bool find_sprite(string name,int layr,Sprite**tmp);

    void collision(Sprite* spr,SDL_Rect LastHitbox);
    bool is_intersection(Sprite*spr);

    bool IsBossDead();

    void print();
    void calculation();
    int Square(Sprite *s1, Sprite *s2);//метод подсчета площади пересечения двух прямоугольников

    pair<pair<pair<int,int>,Sprite*>,int> CreateFloor(FLoor* FL, SDL_Renderer* ren);//СЧИТКА И РАЗМЕЩЕНИЕ СОЗДАННОГО ЭТАЖА

    void DrawHP(int h);//метод отрисовки полоски хп

    void CreatePl(int r, Sprite *s);//метод создания класса игрока

    void CheckBalls();//метод проверки шаров
    void CreateEnemy(int x,int y,int room_x,int room_y, int type);//type:1-warrior

    void DrawCD();//метод отрисовки кд игрока
    bool PLDeath();
};