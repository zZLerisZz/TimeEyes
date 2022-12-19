#pragma once
#include "TypeEnemy.h"
class fly: public TypeEnemy{
public:
    fly(SDL_Renderer* ren,const char*name,int x,int y,int room_x,int room_y, bool fl);//конструктор с параметрами
    ~fly();
    bool CheckBoss()override;//Проверка на босса
    void Update()override;//метод мышления
    SDL_Rect Move()override;//перемещение
    bool CheckR()override;//метод проверки наличия врагов в радиусе атаки
    void Attack()override;//метод создания анимации атаки
    void Death()override;//метод смерти
    void TakeDmg(int dmg)override;//метод получения урона(циферки)

};

