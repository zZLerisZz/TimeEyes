#include "FatEnemy.h"
#include "math.h"
#include <fstream>
#include <iostream>

FatEnemy::FatEnemy(SDL_Renderer* ren,const char*name,int x,int y,int room_x,int room_y, bool fl)//конструктор с параметрами
{
    bs = fl;
    ifstream file;
    if(!bs) {
        sprt = new Sprite(ren, name, "Enemy/FatEnemy.png", 125, 91, x, y, 2, "Enemy/FatEnemy_cfg.txt");
        file.open("Enemy/FatEnemy_Enemy_cfg.txt");
    }
    else{
        sprt = new Sprite(ren, name, "Enemy/fatenemyboss.png", 250, 182, x, y, 2, "Enemy/FatEnemyBoss_cfg.txt");
        file.open("Enemy/FatEnemy_EnemyBoss_cfg.txt");
    }
    sprt->flag_collision=0;
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
FatEnemy::~FatEnemy()
{
    if(sprt!=NULL)delete sprt;
}
void FatEnemy::Update()//метод мышления
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
SDL_Rect FatEnemy::Move()//перемещение
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
bool FatEnemy::CheckR()//метод проверки наличия врагов в радиусе атаки
{
    int dis=distance1(player->GetSpr(),sprt);
    if(dis<=rad)return true;
    return false;
}
void FatEnemy::Attack()//метод создания анимации атаки
{
    player->TakeDmg(dmg);
}
void FatEnemy::Death()//метод смерти
{
    is_Death=1;
}
void FatEnemy::TakeDmg(int dmgg)//метод получения урона(циферки)
{
    cout<<hp<<"  -  "<<dmgg<<"cde = "<<cdE<<endl;
    hp-=dmgg;
    cdE=0;
    sprt->setAnimation(sprt->Stages->Main_Stage_Animation+3,1);
}

bool FatEnemy::CheckBoss(){
    if (bs==true) return true;
    else return false;
}