
//
// Created by Leris
//

#include "Player.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>

#define EXPL 100

Player::Player(int tp, Sprite *sp) {
    typeofhero = tp;
    sprt = sp;
    hp = 2000;
    dmg = 100;
    attype = tp;
    if(tp == 0)
        rad = 150;
    else
        rad = 400;
    cd = 0;
    stacks = 0;
    movespeed = 70;
    makeat = false;
    startt = 0;
    dir = true;
    cb = 9999;
    cdq = 14;
    makeq = false;
    startq = 0;
    makee = false;
    starte = 0;
    cde = 4;
    exp = 0;
    lvl = 0;
}

void Player::Update(bool *buttons) {
    if (buttons[SDL_SCANCODE_D]){
        dir = true;
    }
    if (buttons[SDL_SCANCODE_A]){
        dir = false;
    }
//    if(buttons[SDL_BUTTON_LEFT] && (clock() - startt) / 1000 > cd){
//        startt = clock();
//        std::cout << "Попытка атаки" << std::endl;
//        makeat = true;
//    }
//    else{
//        makeat = false;
//    }
    if(buttons[SDL_BUTTON_LEFT]){
        CreateAt(1);
    }
    else
        makeat = false;
    if(buttons[SDL_SCANCODE_Q]){
        CreateAt(2);
    }
    else
        makeq = false;
    if(buttons[SDL_SCANCODE_E]){
        CreateAt(3);
    }
    else
        makee = false;
    hp -= 1;
    if(hp <= 0) {
        std::cout << "Игрок мертв..." << std::endl;
        hp = 0;
    }
    if(exp / EXPL > lvl){
        lvl += 1;
        dmg += dmg / 10;
        hp += 100;
        if(lvl % 3 == 0 && cdq > 1)
            cdq -= 1;
        if(lvl % 4 == 0 && cde > 1)
            cde -= 1;
    }
    //std::cout << "Текущее хп игрока" << hp << std::endl;
}

bool Player::GetAt() {
    return makeq || makeat || makee;
}

Sprite* Player::GetSpr() {
    return sprt;
}

int Player::GetHP(){
    return hp;
}

bool Player::CheckR(Sprite *en) {
    int x0n = this->sprt->Hitbox.x + (this->sprt->Hitbox.w) / 2;
    int y0n = this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 2;
    int x0en = en->Hitbox.x + (en->Hitbox.w) / 2;
    int y0en = en->Hitbox.y + (en->Hitbox.h) / 2;
    int len = sqrt(abs(x0n - x0en) * abs(x0n - x0en) + abs(y0n - y0en) * abs(y0n - y0en));
    int rd;
    if(makee) {
        rd = 2 * rad;
    }
    else
        rd = rad;
    if(makeq && len <= rad)
        return true;
    if (len <= rd) {
        if (dir) {
            if (x0n <= x0en)
                return true;
            return false;
        } else {
            if (x0n >= x0en)
                return true;
            return false;
        }
    }
    return false;
}

void Player::CreateAt(int m) {
    if(m == 1) {
        //l
        if(sprt->Stages->Main_Stage_Animation<6)
            sprt->setAnimation(3,1);
        else
            sprt->setAnimation(9,1);
        if ((clock() - startt) / 1000 > cd) {
            startt = clock();
            if (typeofhero == 0) Mix_PlayChannel(-1,SwordM1,0);
            std::cout << "Попытка атаки" << std::endl;
            makeat = true;
        } else
            makeat = false;
    }
    else if(m == 2){
        //q
        if(sprt->Stages->Main_Stage_Animation<6)
            sprt->setAnimation(2,1);
        else
            sprt->setAnimation(8,1);
        if ((clock() - startq) / 1000 > cdq) {
            startq = clock();
            if (typeofhero == 0) Mix_PlayChannel(-1,SwordQ,0);
            std::cout << "Попытка атаки" << std::endl;
            makeq = true;
        } else
            makeq = false;
    }
    else if(m == 3){
        //e
        if(sprt->Stages->Main_Stage_Animation<6)
            sprt->setAnimation(3,1);
        else
            sprt->setAnimation(9,1);

        if ((clock() - starte) / 1000 > cde) {
            starte = clock();
            if (typeofhero == 0) Mix_PlayChannel(-1,SwordE,0);
            std::cout << "Попытка атаки" << std::endl;
            makee = true;
        } else
            makee = false;
    }
}

int Player::GetDmg(){
    return dmg;
}

FireBall::FireBall(int x, int y, Sprite *s, int rad, int dm, double kf, double bf, int z, bool c) {
    k = kf;
    b = bf;
    xs = xt = x;
    ys = yt = y;
    fspr = s;
    mr = rad;
    stdmg = dm;
    fspr->set_x(xs);
    fspr->set_y(ys);
    al = true;
    zn = z;
    ycol = c;
}

FireBall* Player::CreateFb() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    x += sprt->Hitbox.x - 960;
    y += sprt->Hitbox.y - 540;
    double k = ((double)y - (double)(this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4)) / (x - this->sprt->Hitbox.x + this->sprt->Hitbox.w);
    double b = (double)y - k * (double)x;
    Sprite *spat;
    Sprite *spq;
    Sprite *spe;
    FireBall *t;
    if(makeq){
        if (typeofhero != 0)Mix_PlayChannel(-1,WarlockQ,0);
        makeat = makeq = makee = false;
        if(x >= this->sprt->Hitbox.x + this->sprt->Hitbox.w / 2) {
            spq = new Sprite(rend, to_string(cb++), "fballr.png",70, 70, 0, 0, 2, "fballr_cfg.txt");
            t = new FireBall(this->sprt->Hitbox.x + this->sprt->Hitbox.w,
                             this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4, spq, 3 * rad, 10 * dmg, k, b, 1, false);
        }
        else {
            spq = new Sprite(rend, to_string(cb++), "fballl.png",70, 70, 0, 0, 2, "fballl_cfg.txt");
            t = new FireBall(this->sprt->Hitbox.x - 70, this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4, spq, 3 * rad,
                             10 * dmg, k, b, -1, false);
        }
    }
    if(makee){
        if (typeofhero != 0) Mix_PlayChannel(-1,WarlockE,0);
        makeat = makee = false;
        if(x >= this->sprt->Hitbox.x + this->sprt->Hitbox.w / 2) {
            spe = new Sprite(rend, to_string(cb++), "eballr.png",50, 50, 0, 0, 2, "eballr_cfg.txt");
            t = new FireBall(this->sprt->Hitbox.x + this->sprt->Hitbox.w,
                             this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4, spe, 2 * rad, 2 * dmg, k, b, 1, false);
        }
        else {
            spe = new Sprite(rend, to_string(cb++), "eballl.png",50, 50, 0, 0, 2, "eballl_cfg.txt");
            t = new FireBall(this->sprt->Hitbox.x - 50, this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4, spe, 2 * rad,
                             2 * dmg, k, b, -1, false);
        }
    }
    if(makeat){
        if (typeofhero != 0) Mix_PlayChannel(-1,WarlockM1,0);
        makeat = false;
        spat = new Sprite(rend, to_string(cb++), "fireball.png",35, 35, 0, 0, 2, "fireball_cfg.txt");
        if(x >= this->sprt->Hitbox.x + this->sprt->Hitbox.w / 2) {
            t = new FireBall(this->sprt->Hitbox.x + this->sprt->Hitbox.w,
                             this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4, spat, rad, dmg, k, b, 1, true);
        }
        else {
            t = new FireBall(this->sprt->Hitbox.x - 50, this->sprt->Hitbox.y + (this->sprt->Hitbox.h) / 4, spat, rad,
                             dmg, k, b, -1, true);
        }
    }
    std::cout << "Создан файрбол " << k << std::endl;
    std::cout << sprt->Hitbox.x << ' ' << sprt->Hitbox.y << std::endl;
    return t;
}

void Player::SetRen(SDL_Renderer *r) {
    this->rend = r;
}

bool Player::TypeOfHero() {
    return typeofhero;
}

void FireBall::Update(bool fl) {
    if(fl && ycol)
        al = false;
    xt += zn * 20 / sqrt(2 * (k * k + 1));
//    xt += 10 * zn;
    yt = k * xt + b;
    fspr->Hitbox.x = (int)xt;
    fspr->Hitbox.y = (int)yt;
    int len = sqrt((xt - xs) * (xt - xs) + (yt - ys) * (yt - ys));
    if(len >= mr)
        al = false;
}

int Player::GetCb() {
    return cb++;
}

bool Player::GetDir() {
    return dir;
}

bool Player::GetQ(){
    if(makeat && makeq)
        makeat = false;
    if(makeq && makee)
        makee = false;
    return makeq;
}

bool Player::GetE(){
    cout << "Умерло тут" << endl;
    if(makeat && makee)
        makeat = false;
    cout << "Умерло тут2" << endl;
    return makee;
}

bool Player::GetAtc(){
    return makeat;
}

double Player::GetCdA() {
    if((clock() - startt) / 1000 > cd)
        return 0;
    double c = 1 + (double)cd - ((double)clock() - (double)startt) / 1000;
    return c;
}

double Player::GetCdE() {
    if((clock() - starte) / 1000 > cde)
        return 0;
    double c = 1 + cde - ((double)clock() - (double)starte) / 1000;
    return c;
}

double Player::GetCdQ() {
    if((clock() - startq) / 1000 > cdq)
        return 0;
    double c = 1 + (double)cdq - ((double)clock() - (double)startq) / 1000;
    return c;
}

void Player::GetExp(int e) {
    exp += e;
}

int Player::CheckExp() {
    return exp % EXPL;
}

int Player::GetLVL() {
    return lvl;
}