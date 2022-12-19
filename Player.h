//
// Created by Leris
//

#pragma once
#include "Eternity.h"
#include <SDL_mixer.h>


class FireBall{
public:
    bool al;//живет ли еще снаряд
    Sprite *fspr;//спрайт заряда
    int xs, ys;//стартовые координаты
    double xt, yt;//текущие координаты
    double k, b;
    int mr;//максимальная дистанция пролета
    int stdmg;//стартовый урон
    int zn;//переменаая отвечающая за направление
    bool ycol;//флаг наличия колизии
    FireBall(int x, int y, Sprite *s, int rad, int dm, double kf, double bf, int z, bool c);//конструктор принимающий стартовые координаты, радиус, урон и спрайт
    void Update(bool fl);//метод обновления
};

class Player : public Eternity{
private:
    int typeofhero;
    bool makeat;
    int startt;
    bool dir;
    SDL_Renderer *rend;
    int cb;
    int cdq;
    bool makeq;
    int startq;//таймер для q
    int cde;
    bool makee;
    int starte;//таймер для e
    int exp;
    int lvl;
    Mix_Chunk* SwordM1 = Mix_LoadWAV("WarriorATK.wav");
    Mix_Chunk* SwordE = Mix_LoadWAV("WarriorE.wav");
    Mix_Chunk* SwordQ = Mix_LoadWAV("WarriorQ.wav");
    Mix_Chunk* WarlockM1 = Mix_LoadWAV("Wizard4.wav");
    Mix_Chunk* WarlockE = Mix_LoadWAV("Wizard3.wav");
    Mix_Chunk* WarlockQ = Mix_LoadWAV("Wizard5.wav");
public:
    Player(int tp, Sprite *sp);//коструктор принимающий класс нашего героя(0 - ближник, 1 - дальник)
    void Update(bool *buttons);//метод обработки всех нажатий и тд
    bool GetAt();//метод для получения понятия о создании атаки
    Sprite* GetSpr();//метод получения адреса спрайта игрока
    int GetHP();//метод для получения хп игрока
    bool CheckR(Sprite *en) override;//метод проверки на
    void CreateAt(int m);//метод создания атаки и его отрисовки
    FireBall* CreateFb();//метод создания FireBall
    void SetRen(SDL_Renderer *r);//установка указателя на рендерер
    bool TypeOfHero();//узнать тип героя
    int GetCb();//метод для получения cb
    bool GetDir();//метод получения dir
    bool GetQ();//метод получения makeq
    bool GetE();//метод получения makee
    bool GetAtc();//метод получения makeat
    int GetDmg();//метод для получения урона
    double GetCdA();//возвращает cd атаки
    double GetCdE();//возвращает cd E
    double GetCdQ();//возвращает cd q
    void GetExp(int e);//метод получения опыта
    int CheckExp();//метод получения процента прогресса уровня
    int GetLVL();//метод получения уровня игрока
};