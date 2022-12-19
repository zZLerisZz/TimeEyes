#pragma once
#include "Sprite.h"
#include "Player.h"
#include <map>
#include <math.h>
class TypeEnemy {
protected:
    //хп, скорость передвижения, количество урона, тип атаки, радиус атаки, указатель на спрайт
    int movespeed;//вагон-топ тянка
    int dmg;
    int attype;
    int rad;
    int rad_vision;
    int cd;//время отката базовой атаки
    int stacks;//количество стаков на сущности =/
    int cd_cont;
    bool bs;//флаг того, что это босс
    int room_x;//20
    int room_y;//20

public:
    int hp;
    Player* player;
    Sprite *sprt;
    bool is_Death;
    virtual bool CheckBoss()=0;//проверка на босса
    virtual void Update()=0;//метод мышления
    virtual SDL_Rect Move()=0;//перемещение
    virtual bool CheckR()=0;//метод проверки наличия врагов в радиусе атаки
    virtual void Attack()=0;//метод создания анимации атаки
    virtual void Death()=0;//метод смерти
    virtual void TakeDmg(int dmg)=0;//метод получения урона(циферки)
    int cdE;
    virtual int distance1(Sprite*spr1,Sprite*spr2)
    {
        return sqrt((spr1->get_x()-spr2->get_x())*(spr1->get_x()-spr2->get_x())+(spr1->get_y()-spr2->get_y())*(spr1->get_y()-spr2->get_y()));
    }
};

