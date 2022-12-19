
//
// Created by Leris
//

#pragma once
#include "Sprite.h"

class Eternity{
protected:
    int hp;//хп, скорость передвижения, количество урона, тип атаки, радиус атаки, указатель на спрайт
    int movespeed;//вагон-топ тянка
    int dmg;
    int attype;
    int rad;
    Sprite *sprt;
    int cd;//время отката базовой атаки
    int stacks;//количество стаков на сущности =/
    int startt;
public:
    Eternity();
    Eternity(int h, int m, int dm, int a, int rd, Sprite *sr, int c, int s);//конструктор с параметрами
    virtual bool CheckR(Sprite *en) = 0;//метод проверки наличия врагов в радиусе атаки
    void TakeDmg(int d);//метод получения урона(циферки)
};