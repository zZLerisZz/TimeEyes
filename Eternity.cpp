#include "Eternity.h"
#include <cmath>
#include <iostream>

Eternity::Eternity(int h, int m, int dm, int a, int rd, Sprite *sr, int c, int s){
    hp = h;
    movespeed = m;
    dmg = dm;
    attype = a;
    rad = rd;
    sprt = sr;
    cd = c;
    stacks = s;
}

void Eternity::TakeDmg(int d) {
    if(d>0) {
        if (sprt->Stages->Main_Stage_Animation == 0) sprt->setAnimation(4, 1);
        else if (sprt->Stages->Main_Stage_Animation == 1) sprt->setAnimation(5, 1);
        else if (sprt->Stages->Main_Stage_Animation == 6) sprt->setAnimation(10, 1);
        else if (sprt->Stages->Main_Stage_Animation == 7) sprt->setAnimation(11, 1);
    }
    hp -= d;
}

Eternity::Eternity() {

}

//bool Eternity::CheckR(Sprite *en) {
//    int x0n = (this->sprt->Hitbox.x + this->sprt->Hitbox.w) / 2;
//    int y0n = (this->sprt->Hitbox.y + this->sprt->Hitbox.h) / 2;
//    int x0en = (en->Hitbox.x + en->Hitbox.w) / 2;
//    int y0en = (en->Hitbox.y + en->Hitbox.h) / 2;
//    int len = sqrt(abs(x0n - x0en) * abs(x0n - x0en) + abs(y0n - y0en) * abs(y0n - y0en));
//    if(len <= rad) {
//        std::cout << "Атака пройдет - " << len << std::endl;
//        return true;
//    }
//    //std::cout << "Атака не пройдет" << std::endl;
//    return false;
//}