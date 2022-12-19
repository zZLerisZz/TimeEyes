#include "Warrior.h"
#include "math.h"
#include <fstream>
#include <iostream>

Warrior::Warrior(SDL_Renderer* ren,const char*name,int x,int y,int room_x,int room_y, bool fl)//конструктор с параметрами
{
    bs = fl;
    ifstream file;
    if(!bs) {
        sprt = new Sprite(ren, name, "Enemy/Warrior.png", 30 * 2, 46 * 2, x, y, 2, "Enemy/Warrior_cfg.txt");
        file.open("Enemy/Warrior_Enemy_cfg.txt");
    }
    else{
        sprt = new Sprite(ren, name, "Enemy/warriorBoss.png", 60 * 2, 92 * 2, x, y, 2, "Enemy/WarriorBoss_cfg.txt");
        file.open("Enemy/Warrior_EnemyBoss_cfg.txt");
    }
    file>>this->hp;
    file>>this->movespeed;
    file>>this->dmg;
    file>>this->rad;
    file>>this->rad_vision;
    file>>this->cd;
    file.close();
    this->room_x=room_x;
    this->room_y=room_y;
    stacks=0;
    cd_cont=0;
    is_Death=0;
    cdE=0;
}
Warrior::~Warrior()
{
    if(sprt!=NULL)delete sprt;
}
void Warrior::Update()//метод мышления
{
    if(CheckR()&&cd_cont==cd&& distance1(player->GetSpr(),sprt)<rad){
        Attack();
        cd_cont=0;
    }
    if(hp<=0){
        Death();
    }
    if(cdE!=50)cdE++;
    if(cd_cont!=cd)cd_cont++;

}
SDL_Rect Warrior::Move()//перемещение
{
    SDL_Rect tmp = sprt->Hitbox;
    // if(distance1(player->GetSpr(),sprt)<rad_vision)
    if(player->GetSpr()->get_x()>room_x&&player->GetSpr()->get_x()<room_x+20*70 && player->GetSpr()->get_y()>room_y&&player->GetSpr()->get_y()<room_y+20*70||distance1(player->GetSpr(),sprt)<rad_vision) {
        if (player->GetSpr()->Hitbox.x - sprt->Hitbox.x > 3) {
            sprt->Hitbox.x += movespeed;
            sprt->setMainAnimation(2);
        } else if (sprt->Hitbox.x - player->GetSpr()->Hitbox.x > 3) {
            sprt->Hitbox.x -= movespeed;
            sprt->setMainAnimation(0);
        }
        if (player->GetSpr()->Hitbox.y - sprt->Hitbox.y > 3) {
            sprt->Hitbox.y += movespeed;
            //sprt->setMainAnimation(2);
        } else if (sprt->Hitbox.y - player->GetSpr()->Hitbox.y > 3) {
            sprt->Hitbox.y -= movespeed;
            // sprt->setMainAnimation(0);
        }
    }
    else{
        sprt->setMainAnimation(1);
    }
    return tmp;
}
bool Warrior::CheckR()//метод проверки наличия врагов в радиусе атаки
{
    int dis=distance1(player->GetSpr(),sprt);
    if(dis<=rad)return true;
    return false;
}
void Warrior::Attack()//метод создания анимации атаки
{
    player->TakeDmg(dmg);
}
void Warrior::Death()//метод смерти
{
    is_Death=1;
}
void Warrior::TakeDmg(int dmgg)//метод получения урона(циферки)
{
    cout<<hp<<"  -  "<<dmgg<<"cde = "<<cdE<<endl;
    hp-=dmgg;
    cdE=0;
    sprt->setAnimation(sprt->Stages->Main_Stage_Animation+3,1);
}

bool Warrior::CheckBoss(){
    if (bs==true) return true;
    else return false;
}