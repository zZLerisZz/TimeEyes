#include "Map.h"
#include "cmath"
#include <algorithm>
#include "FLOOR.h"
#include <iostream>
#include <SDL_ttf.h>
#include "Warrior.h"
#include "fly.h"
#include "FatEnemy.h"
#include "Rat.h"

int distance(Sprite*spr1,Sprite*spr2)
{
    return sqrt((spr1->get_x()-spr2->get_x())*(spr1->get_x()-spr2->get_x())+(spr1->get_y()-spr2->get_y())*(spr1->get_y()-spr2->get_y()));
}
Map::Map(SDL_Renderer* ren,Camera* cum)
{
    dead_boss=false;
    Render=ren;
    camera = cum;
    cg = 1;
    t = nullptr;
}
void Map::add_sprite(Sprite*spr)
{
    data[spr->get_layr()].insert(pair<string ,Sprite*>(spr->name,spr));
}
void Map::del_sprite(string name,int layr)
{

    auto it = data[layr].find(name);
    if(it!=data[layr].end())data[layr].erase(it);

}
bool Map::find_sprite(string name,int layr,Sprite** tmp)
{
    auto it = data[layr].find(name);
    if(it==data[layr].end())return 0;
    *tmp = (*it).second;
    return 1;

}
void Map::CameraUpdate(){
    camera->set_x(sprite_with_camera->get_x()+camera->offset_x);
    camera->set_y(sprite_with_camera->get_y()+camera->offset_y);
}
void Map::collision(Sprite* spr,SDL_Rect LastHitbox){
    calculation();
    SDL_Rect tmp = spr->Hitbox;

    if(is_intersection(spr)) {
        spr->Hitbox.x=LastHitbox.x;
        calculation();
        if (is_intersection(spr))spr->Hitbox = tmp;
    }
    if(is_intersection(spr)) {
        spr->Hitbox.y=LastHitbox.y;
        calculation();
        if (is_intersection(spr))spr->Hitbox = tmp;
    }
    calculation();
    if (is_intersection(spr))spr->Hitbox = LastHitbox;

    //
//
//    while(is_intersection(spr)){
//        for (auto &item: data[spr->get_layr()]) {
//            int s = Square(spr, item.second);
//            if(item.second->flag_collision && item.first!=spr->name && s) {
//                int s1, s2, s3, s4;
//                camera->add_x(1);
//                calculation(spr);
//                s1 = Square(spr, item.second);
//                camera->add_x(-1);
//
//                camera->add_x(-1);
//                calculation(spr);
//                s2 = Square(spr, item.second);
//                camera->add_x(1);
//
//                camera->add_y(-1);
//                calculation(spr);
//                s3 = Square(spr, item.second);
//                camera->add_y(1);
//
//                camera->add_y(1);
//                calculation(spr);
//                s4 = Square(spr, item.second);
//                camera->add_y(-1);
//
//
//                calculation(spr);
//
//
//                if (s1 <= s2 && s1 <= s3 && s1 <= s4) {
//                    while (s1) {
//                        camera->add_x(1);
//                        calculation(spr);
//                        s1 = Square(spr, item.second);
//                    }
//                } else if (s2 <= s1 && s2 <= s3 && s2 <= s4) {
//                    while (s2) {
//                        camera->add_x(-1);
//                        calculation(spr);
//                        s2 = Square(spr, item.second);
//                    }
//                } else if (s3 <= s1 && s3 <= s2 && s3 <= s4) {
//                    while (s3) {
//                        camera->add_y(-1);
//                        calculation(spr);
//                        s3 = Square(spr, item.second);
//                    }
//                } else if (s4 <= s1 && s4 <= s3 && s4 <= s2) {
//                    while (s4) {
//                        camera->add_y(1);
//                        calculation(spr);
//                        s4 = Square(spr, item.second);
//                    }
//                }
//
//                calculation(spr);
//            }
//        }
//    }


}
void Map::Update(bool *buttons)
{
    CameraUpdate();
    pl->Update(buttons);

    if(pl->GetAt()){
        if(!pl->TypeOfHero()) {
            int call = 0, cy = 0;
            int dm = pl->GetDmg();
            Sprite *s = nullptr;
            if(pl->GetQ()) {
                dm *= 10;
                if(t == nullptr)
                    s = new Sprite(Render, to_string(pl->GetCb()), "slashq.png", 300, 139,
                                   pl->GetSpr()->Hitbox.x - pl->GetSpr()->Hitbox.w,
                                   pl->GetSpr()->Hitbox.y, 3, "qslash_cfg.txt");
            }
            if(pl->GetE()){
                dm *= 2;
                if(t == nullptr)
                    if (pl->GetDir())
                        s = new Sprite(Render, to_string(pl->GetCb()), "splasher.png", 300, 139,
                                       pl->GetSpr()->Hitbox.x + pl->GetSpr()->Hitbox.w / 2,
                                       pl->GetSpr()->Hitbox.y - pl->GetSpr()->Hitbox.h / 3, 3, "splashe_cfg.txt");
                    else
                        s = new Sprite(Render, to_string(pl->GetCb()), "splashel.png", 300, 139,
                                       pl->GetSpr()->Hitbox.x - pl->GetSpr()->Hitbox.w * 3,
                                       pl->GetSpr()->Hitbox.y - pl->GetSpr()->Hitbox.h / 3, 3, "splashe_cfg.txt");
            }
            if(pl->GetAtc()) {
                cout << "РЈРјРµСЂР»Рѕ С‚СѓС‚" << endl;
                if(t == nullptr)
                    if (pl->GetDir())
                        s = new Sprite(Render, to_string(pl->GetCb()), "splashr.png", 150, 89,
                                       pl->GetSpr()->Hitbox.x + pl->GetSpr()->Hitbox.w / 2,
                                       pl->GetSpr()->Hitbox.y - pl->GetSpr()->Hitbox.h / 3, 3, "splasha_cfg.txt");
                    else
                        s = new Sprite(Render, to_string(pl->GetCb()), "splashl.png", 150, 89,
                                       pl->GetSpr()->Hitbox.x - pl->GetSpr()->Hitbox.w,
                                       pl->GetSpr()->Hitbox.y - pl->GetSpr()->Hitbox.h / 3, 3, "splasha_cfg.txt");
            }
            if(s != nullptr) {
                add_sprite(s);
                t = s;
                strtta = clock();
            }
            for (auto &item: Enemy) {
                call += 1;
                if (pl->CheckR(item.second->sprt)) {
                    item.second->TakeDmg(dm);
                    pl->TakeDmg(-dm/100);
                    cy += 1;
                }
            }
            cout << "Р’СЃРµРіРѕ СЃРїСЂР°Р№С‚РѕРІ - " << call << "\nРђС‚Р°РєР° РїСЂРѕС€Р»Р° РїРѕ - " << cy << endl;
        }

        else{
            FireBall *tmp = pl->CreateFb();
            FBalls.insert(pair<string, FireBall*>(tmp->fspr->name, tmp));
            add_sprite(tmp->fspr);
        }
    }
    for(int i=0;i<4;i++)
    {
        for(auto& item:data[i])
        {
            item.second->Update();
        }
    }
    for(auto& item:FBalls){
        item.second->Update(is_intersection(item.second->fspr));
    }
    if(pl->TypeOfHero())
        CheckBalls();
    for (auto item = Enemy.begin(); item != Enemy.end();)
    {
        int d =distance(pl->GetSpr(),item->second->sprt);
        if(d<70*13) {
            for(auto &item2:FBalls){
                if(Square(item->second->sprt,item2.second->fspr)){
                    if(!(item2.second->ycol)&& item->second->cdE==50)
                        item->second->TakeDmg(item2.second->stdmg);


                    if(item2.second->ycol!=0)
                        item->second->TakeDmg(item2.second->stdmg);
                    if(item2.second->ycol)
                        item2.second->al=false;
                }
            }
            item->second->Update();
            SDL_Rect tmp = item->second->Move();
            // if(!(item->second->sprt->name.find("fly", 0) + 1))
            collision(item->second->sprt, tmp);
        }
        if(item->second->is_Death){
            if (item->second->CheckBoss()==true) dead_boss=true;
            pl->TakeDmg(-pl->GetDmg());
            pl->GetExp(cg * 10);
            auto it = data[item->second->sprt->get_layr()].find(item->second->sprt->name);
            data[item->second->sprt->get_layr()].erase(it);
            Enemy.erase(item++);
        }
        else{
            item++;
        }
    }

}
bool Map::is_intersection(Sprite* spr)
{

    for (auto &item: data[spr->get_layr()])
    {
        if(item.second->flag_collision && item.first!=spr->name){
            if(Square(spr, item.second))
                return true;
        }
    }
    return false;
}

void Map::print()
{
    for(int i=0;i<4;i++) {
        for (auto &item: data[i]) {

            if( item.second->flag_moving_with_camera){
                item.second->Hitbox.x=camera->get_x()+item.second->moving_with_camera_offset_x;
                item.second->Hitbox.y=camera->get_y()+item.second->moving_with_camera_offset_y;
                item.second->PrintSprite(Render,camera,1);
            }
            else {

                int dist = distance(sprite_with_camera, item.second);
                if (!(i == sprite_with_camera->get_layr() && dist > 70 * 18))
                    item.second->PrintSprite(Render, camera, 1);
                else item.second->PrintSprite(Render, camera, 0);

            }
        }
    }
    if(clock() - strtta >= 40 && t != nullptr){
        del_sprite(t->name, 3);
        t = nullptr;
    }
    DrawHP(pl->GetHP());
    DrawCD();
}
void Map::calculation()
{
    for(int i=0;i<4;i++) {
        for (auto &item: data[i]) {
            int dist =distance(sprite_with_camera,item.second);
            if(!(dist>70*2))
                item.second->PrintSprite(Render,camera,0);
        }
    }
}
//площадь
int Map::Square(Sprite *s1, Sprite *s2) {
    int left = std::max(s1->Hitbox.x, s2->Hitbox.x);
    int top = std::min(s1->Hitbox.y + s1->Hitbox.h, s2->Hitbox.y + s2->Hitbox.h);
    int right = std::min(s1->Hitbox.x + s1->Hitbox.w, s2->Hitbox.x + s2->Hitbox.w);
    int bottom = std::max(s1->Hitbox.y, s2->Hitbox.y);
    int width = right - left;
    int height = top - bottom;
    if (width < 0 || height < 0)
        return 0;
    return width * height;
}

void ChangeRoom(Room *R){
    if (R->doors[3] == 0)
        R->room_configuration[R->room_size/2][0] = R->room_configuration[R->room_size/2 - 1][0] = 1;
    if (R->doors[2] == 0)
        R->room_configuration[R->room_size-1][R->room_size/2] = R->room_configuration[R->room_size-1][R->room_size/2 - 1] = 1;
    if (R->doors[1] == 0)
        R->room_configuration[R->room_size/2][R->room_size-1] = R->room_configuration[R->room_size/2 - 1][R->room_size-1] = 1;
    if (R->doors[0] == 0)
        R->room_configuration[0][R->room_size/2] = R->room_configuration[0][R->room_size/2 - 1] = 1;
}

pair<pair<pair<int,int>,Sprite*>,int> Map:: CreateFloor(FLoor* FL, SDL_Renderer* ren)
{
    dead_boss=false;
    const char *PolName;
    const char *WallName;
    if(FL->FloorNumber == cg)
        cg += 1;
    switch(FL->FloorNumber) {
        case 0:
            PolName = "1floor.jpg";
            WallName = "1wall.jpg";
            break;
        case 1:
             PolName = "2floor.jpg";
             WallName = "2wall.jpg";
            break;
        case 2:
            PolName = "3floor.jpg";
            WallName = "3wall.jpg";
            break;
        case 3:
            PolName = "4floor.jpg";
            WallName = "4wall.jpg";
            break;
    }
    cout<<PolName<<" "<<WallName;
    int BuildPosX = -3500;
    int BuildPosY = -3500;
    int FloorSize = FL->GetSize()+2;
    int ListSize = FloorSize*400+1;
    int SpriteH = 70;
    int SpriteW = 70;
    int RS = 20;
    int x1, y1;
    Sprite** SpriteList = new Sprite*[ListSize]; //Да поможет мне Анемо Архонт....
    pair<pair<pair<int,int>,Sprite*>,int> Start = make_pair(make_pair(make_pair(0,0),SpriteList[0]),0);
    while(ListSize && FloorSize>0)
        for (int i = 0; i<FL->GetH(); i++) {
            for (int j = 0; j < FL->GetW(); j++) {
                if (FL->GetFloor()[i][j].room_type == 404) {
                    BuildPosX += SpriteW * RS;
                } else {
                    if (FL->GetFloor()[i][j].room_type == 0)
                        Start.first.first = make_pair(BuildPosX,BuildPosY);
                    std::cout << "Комната выбрана. Размещение спрайтов" << std::endl;
                    std::cout << "Текущий размер: " << FloorSize << std::endl;
                    cout<<"Двери: "<<FL->GetFloor()[i][j].doors[0]<<FL->GetFloor()[i][j].doors[1]<<FL->GetFloor()[i][j].doors[2]<<FL->GetFloor()[i][j].doors[3]<<endl;
                    ChangeRoom(&FL->GetFloor()[i][j]);
                    std::cout << "Размер комнаты: " << FL->GetFloor()[i][j].room_size << std::endl;
                    cout<<"Тип комнаты: "<<FL->GetFloor()[i][j].room_type<<endl;
                    cout<<"x "<<j<<"y "<<i<<endl;
                    cout<<"Двери: "<<FL->GetFloor()[i][j].doors[0]<<FL->GetFloor()[i][j].doors[1]<<FL->GetFloor()[i][j].doors[2]<<FL->GetFloor()[i][j].doors[3]<<endl;

                    int room_x=BuildPosX;
                    int room_y=BuildPosY;


                    for (int ri = 0; ri < FL->GetFloor()[i][j].room_size; ri++) {
                        for (int rj = 0; rj < FL->GetFloor()[i][j].room_size; rj++) {
                            char a[2] = "";
                            sprintf(a, "%d", FL->FloorNumber+1);

                            //cout<< FL->GetFloor()[i][j].room_configuration[ri][rj];
                            switch (FL->GetFloor()[i][j].room_configuration[ri][rj]) {
                                case 2: {
                                    // std::cout << "Сработал кейс 2" << std::endl;
                                    //std::cout << i << ' ' << j << ' ' << FL->GetFloor()[i][j].doors[0] << ' '  << FL->GetFloor()[i][j].doors[1] << ' '  << FL->GetFloor()[i][j].doors[2] << ' '  << FL->GetFloor()[i][j].doors[3] << std::endl;
                                    SpriteList[ListSize - 1] = new Sprite(ren, to_string(ListSize - 1), PolName, SpriteW, SpriteH, BuildPosX,
                                                                          BuildPosY, 1,"mfloorc_cfg.txt");
                                    add_sprite(SpriteList[ListSize - 1]);
                                    BuildPosX += SpriteW;
                                    ListSize--;
                                    break;
                                }
                                case 1: {
                                    //  std::cout << "Сработал кейс 1" << std::endl;
                                    SpriteList[ListSize - 1] = new Sprite(ren, to_string(ListSize - 1), WallName, SpriteW, SpriteH, BuildPosX,
                                                                          BuildPosY, 2,"wall_cfg.txt");
                                    add_sprite(SpriteList[ListSize - 1]);
                                    BuildPosX += SpriteW;
                                    ListSize--;
                                    break;
                                }
                                case 3: {
                                    // std::cout << "Сработал кейс 3" << std::endl;
                                    CreateEnemy(BuildPosX,BuildPosY,room_x,room_y,cg);
                                    SpriteList[ListSize - 1] = new Sprite(ren, to_string(ListSize - 1), PolName, SpriteW, SpriteH, BuildPosX,
                                                                          BuildPosY, 1,"mfloorc_cfg.txt");
                                    add_sprite(SpriteList[ListSize - 1]);
                                    ListSize--;
                                    BuildPosX += SpriteW;
                                    break;
                                }
                                case 6: {
                                    // std::cout << "Сработал кейс 3" << std::endl;
                                    CreateEnemy(BuildPosX,BuildPosY,room_x,room_y,cg);
                                    SpriteList[ListSize - 1] = new Sprite(ren, to_string(ListSize - 1), PolName, SpriteW, SpriteH, BuildPosX,
                                                                          BuildPosY, 1,"mfloorc_cfg.txt");
                                    add_sprite(SpriteList[ListSize - 1]);
                                    ListSize--;
                                    BuildPosX += SpriteW;
                                    break;
                                }
                                case 4: {
                                    // std::cout << "Сработал кейс 4" << std::endl;
                                    Start.second = count_enemy;
                                    CreateEnemy(BuildPosX,BuildPosY,room_x,room_y,5 * cg);
                                    SpriteList[ListSize - 1] = new Sprite(ren, to_string(ListSize - 1), PolName, SpriteW, SpriteH, BuildPosX,
                                                                          BuildPosY, 1,"mfloorc_cfg.txt");
                                    add_sprite(SpriteList[ListSize - 1]);
                                    BuildPosX += SpriteW;
                                    ListSize--;
                                    break;
                                }
                                case 5:{
                                        // std::cout << "Сработал кейс 5" << std::endl;
                                        SpriteList[ListSize - 1] = new Sprite(ren, "EXIT", "portal.png", SpriteW, SpriteH, BuildPosX,
                                                                              BuildPosY, 1,"portal_cfg.txt");
                                        Start.first.second=SpriteList[ListSize - 1];
                                        ListSize--;
                                        SpriteList[ListSize - 1] = new Sprite(ren, to_string(ListSize - 1), PolName, SpriteW, SpriteH, BuildPosX,
                                                                          BuildPosY, 1,"mfloorc_cfg.txt");
                                        add_sprite(SpriteList[ListSize - 1]);
                                        BuildPosX += SpriteW;
                                        ListSize--;
                                        break;
                                }
                            }
                        }
                        BuildPosY += SpriteH;
                        BuildPosX -= SpriteW * FL->GetFloor()[i][j].room_size;
                    }
                    cout<<" "<<ListSize;
                    BuildPosY -= SpriteH * FL->GetFloor()[i][j].room_size;
                    BuildPosX += SpriteW * FL->GetFloor()[i][j].room_size;
                    FloorSize--;
                }
            }
            BuildPosY += SpriteH * RS;
            BuildPosX -= SpriteW * RS * FL->GetW();
        }
    return Start;
}

void Map::CreatePl(int r, Sprite *s) {
    pl = new Player(r, s);
    pl->SetRen(Render);
    cout << "Игрок создан" << endl;
    startg = clock();
    for(auto& item:Enemy)
    {
        item.second->player=pl;
    }
}

void Map::DrawHP(int h) {
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    if(h > 1000)
        r.w = h + 4;
    else
        r.w = 1004;
    r.h = 50;
    SDL_Rect rh;
    rh.x = 2;
    rh.y = 2;
    if(h < 0)
        rh.w = 0;
    else
        rh.w = h;
    rh.h = 46;
    SDL_Rect re;
    re.x = 2;
    re.y = 54;
    re.w = pl->CheckExp() * 10;
    re.h = 20;
    SDL_Rect reb;
    reb.x = 0;
    reb.y = 52;
    reb.w = 104 * 10;
    reb.h = 25;
    SDL_SetRenderDrawColor( Render, 0, 0, 0, 255 );
    SDL_RenderFillRect( Render, &r );
    SDL_SetRenderDrawColor( Render, 255, 0, 0, 255 );
    SDL_RenderFillRect( Render, &rh );
    SDL_SetRenderDrawColor( Render, 0, 0, 0, 255 );
    SDL_RenderFillRect( Render, &reb );
    SDL_SetRenderDrawColor( Render, 0, 255, 255, 255 );
    SDL_RenderFillRect( Render, &re );
}

void Map::CheckBalls() {
    for (auto it = FBalls.cbegin(); it != FBalls.cend();)
    {
        if (!it->second->al)
        {
            del_sprite(it->first, 2);
            FBalls.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

void Map::CreateEnemy(int x,int y,int room_x,int room_y, int type)
{
    char a[33];
    itoa(count_enemy,a,10);
    //sprintf(a, "%d", Y);
    const char* Name;
    Warrior* w;
    fly* f;
    FatEnemy* fe;
    Rat*r;
    if(type==2) {
        Name = "warrior";
        Name = strcat(a, Name);
        w = new Warrior(Render, Name, x, y, room_x, room_y,false);
        add_sprite(w->sprt);
        w->sprt->flag_collision = true;
        w->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, w));
    }
    if(type==1) {
        Name = "fly";
        Name = strcat(a, Name);
        f = new fly(Render, Name, x, y, room_x, room_y,false);
        add_sprite(f->sprt);
        f->sprt->flag_collision = true;
        f->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, f));
    }
    if(type==4) {
        Name = "FatEnemy";
        Name = strcat(a, Name);
        fe = new FatEnemy(Render, Name, x, y, room_x, room_y,false);
        add_sprite(fe->sprt);
        fe->sprt->flag_collision = true;
        fe->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, fe));
    }
    if(type==3) {
        Name = "Rat";
        Name = strcat(a, Name);
        r = new Rat(Render, Name, x, y, room_x, room_y,false);
        add_sprite(r->sprt);
        r->sprt->flag_collision = true;
        r->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, r));
    }
    if(type==10) {
        Name = "warriorboss";
        Name = strcat(a, Name);
        w = new Warrior(Render, Name, x, y, room_x, room_y,true);
        add_sprite(w->sprt);
        w->sprt->flag_collision = true;
        w->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, w));
    }
    if(type==5) {
        Name = "flyboss";
        Name = strcat(a, Name);
        f = new fly(Render, Name, x, y, room_x, room_y, true);
        add_sprite(f->sprt);
        f->sprt->flag_collision = true;
        f->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, f));
    }
    if(type==15) {
        Name = "RatBoss";
        Name = strcat(a, Name);
        r = new Rat(Render, Name, x, y, room_x, room_y, true);
        add_sprite(r->sprt);
        r->sprt->flag_collision = true;
        r->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, r));
    }
    if(type == 20){
        Name = "FatEnemyBoss";
        Name = strcat(a, Name);
        fe = new FatEnemy(Render, Name, x, y, room_x, room_y, true);
        add_sprite(fe->sprt);
        fe->sprt->flag_collision = true;
        fe->player = pl;
        Enemy.insert(pair<int, TypeEnemy *>(count_enemy, fe));
    }
    count_enemy++;
}

void Map::DrawCD() {
    SDL_Rect ra1;
    SDL_Rect re2;
    SDL_Rect rq3;
    ra1.x = 0;
    ra1.y = 930;
    ra1.h = 100;
    ra1.w = 200;
    re2.x = 210;
    re2.y = 930;
    re2.h = 100;
    re2.w = 200;
    rq3.x = 0;
    rq3.y = 820;
    rq3.h = 100;
    rq3.w = 450;
    char *AA = new char[11];
    char *E = new char[11];
    char *Q = new char[11];
    AA[0] = '-';
    AA[1] = 'A';
    AA[2] = 'A';
    AA[3] = '\0';
    Q[0] = '-';
    Q[1] = 'Q';
    Q[2] = '\0';
    E[0] = '-';
    E[1] = 'E';
    E[2] = '\0';
    char a[7];
    char e[7];
    char q[7];
    SDL_SetRenderDrawColor( Render, 0, 0, 0, 255 );
    SDL_RenderFillRect( Render, &ra1 );
    SDL_RenderFillRect( Render, &re2 );
    SDL_RenderFillRect( Render, &rq3 );
    double ca = pl->GetCdA(), ce = pl->GetCdE(), cq = pl->GetCdQ();
    sprintf(a, "%.2lf", ca);
    sprintf(e, "%.2lf", ce);
    sprintf(q, "%.2lf", cq);
    AA = strcat(a,AA);
    TTF_Font *font = TTF_OpenFont("timesnewromanpsmt.ttf", 20 );
    SDL_Color color = { 0, 255, 0};
    SDL_Surface * surface1 = TTF_RenderText_Solid(font,AA, color);
    SDL_Texture * texture1 = SDL_CreateTextureFromSurface(Render, surface1);
    SDL_RenderCopy(Render, texture1, NULL, &ra1);
    E = strcat(e,E);
    SDL_Surface * surface2 = TTF_RenderText_Solid(font,E, color);
    SDL_Texture * texture2 = SDL_CreateTextureFromSurface(Render, surface2);
    SDL_RenderCopy(Render, texture2, NULL, &re2);
    Q = strcat(q,Q);
    SDL_Surface * surface3 = TTF_RenderText_Solid(font,Q, color);
    SDL_Texture * texture3 = SDL_CreateTextureFromSurface(Render, surface3);
    SDL_RenderCopy(Render, texture3, NULL, &rq3);
    SDL_Rect rt;
    rt.x = 0;
    rt.y = 700;
    rt.h = 100;
    double time = ((double)clock() - (double)startg) / 1000;
    char tm[7];
    sprintf(tm, "%.2lf", time);
    SDL_Surface * surface4 = TTF_RenderText_Solid(font,tm, {255, 255, 255});
    rt.w = surface4->w;
    SDL_Texture * texture4 = SDL_CreateTextureFromSurface(Render, surface4);
    SDL_RenderCopy(Render, texture4, NULL, &rt);

    SDL_Rect rl;
    rl.x = 0;
    rl.y = 70;
    rl.h = 50;
    int l = pl->GetLVL();
    char lv[7];
    sprintf(lv, "%d", l);
    SDL_Surface * surface5 = TTF_RenderText_Solid(font,lv, {173, 255, 47});
    rl.w = surface5->w;
    SDL_Texture * texture5 = SDL_CreateTextureFromSurface(Render, surface5);
    SDL_RenderCopy(Render, texture5, NULL, &rl);
    //SDL_RenderPresent(Render);

    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface2);
    SDL_DestroyTexture(texture3);
    SDL_FreeSurface(surface3);
    SDL_DestroyTexture(texture4);
    SDL_FreeSurface(surface4);
    SDL_DestroyTexture(texture5);
    SDL_FreeSurface(surface5);
    TTF_CloseFont(font);
}

bool Map::PLDeath(){
    if(pl->GetHP()==0) return true;
    if(pl->GetHP()>0) return false;
}