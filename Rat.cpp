#include "Rat.h"
#include "math.h"
#include <fstream>
#include <iostream>

Rat::Rat(SDL_Renderer* ren,const char*name,int x,int y,int room_x,int room_y, bool fl)//конструктор с параметрами
{
    bs = fl;
    ifstream file;
    if(!bs) {
        sprt = new Sprite(ren, name, "Enemy/Rat.png", 41 * 2, 16 * 2, x, y, 2, "Enemy/Rat_cfg.txt");
        file.open("Enemy/Rat_Enemy_cfg.txt");
    }
    else{
        sprt = new Sprite(ren, name, "Enemy/ratBoss.png", 82 * 2, 32 * 2, x, y, 2, "Enemy/RatBoss_cfg.txt");
        file.open("Enemy/Rat_EnemyBoss_cfg.txt");
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
Rat::~Rat()
{
    if(sprt!=NULL)delete sprt;
}
void Rat::Update()//метод мышления
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
SDL_Rect Rat::Move()//перемещение
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
bool Rat::CheckR()//метод проверки наличия врагов в радиусе атаки
{
    int dis=distance1(player->GetSpr(),sprt);
    if(dis<=rad)return true;
    return false;
}
void Rat::Attack()//метод создания анимации атаки
{
    player->TakeDmg(dmg);
}
void Rat::Death()//метод смерти
{
    is_Death=1;
}
void Rat::TakeDmg(int dmgg)//метод получения урона(циферки)
{
    cout<<hp<<"  -  "<<dmgg<<"cde = "<<cdE<<endl;
    hp-=dmgg;
    cdE=0;
    sprt->setAnimation(sprt->Stages->Main_Stage_Animation+3,1);
}

bool Rat::CheckBoss(){
    if (bs==true) return true;
    else return false;
}