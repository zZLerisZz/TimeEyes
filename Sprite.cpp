#include "Sprite.h"
#include<iostream>
#include<cstring>
#include<string.h>

Sprite::Sprite(SDL_Renderer* ren,string name,const char* filename,int w,int h,int x,int y,int layr,char* file_config_animation)
{
    m_texture=NULL;
    flag_collision= true;
    flag_moving_with_camera=false;
    Hitbox.w=w;
    Hitbox.h=h;
    Hitbox.x=x;
    Hitbox.y=y;
    m_layer =layr;
    this->name=name;
    this->filename=filename;

    Stages=new StagesAnim(file_config_animation);


    moving_with_camera_offset_x=0;
    moving_with_camera_offset_x=0;
    SDL_Surface* temp;
    temp = IMG_Load(filename);
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    m_texture=SDL_CreateTextureFromSurface(ren, temp);
    m_Sw=temp->w;
    m_Sh=temp->h;
    SDL_FreeSurface(temp);

}
Sprite::~Sprite()
{
    if(m_texture)SDL_DestroyTexture(m_texture);
    delete Stages;
}

//Sprite::Sprite(const Sprite &Sp1, char* NewName, SDL_Renderer* ren)
//{
//    m_texture=NULL;
//    flag_collision= true;
//    flag_moving_with_camera=false;
//    Hitbox=Sp1.Hitbox;
//    //?
//    *this->Stages=*Sp1.Stages;
//    m_layer =Sp1.m_layer;
//    this->name=NewName;
//    this->filename=filename;
//
//    SDL_Surface* temp;
//    temp = IMG_Load(filename);
//    if (temp == NULL) {
//        std::cout << "Can't load: " << SDL_GetError() << std::endl;
//    }
//
//    m_texture=SDL_CreateTextureFromSurface(ren, temp);
//}

/*
Sprite Sprite::operator=(const Sprite &left)
{
    m_texture=NULL;
    flag_collision= true;
    flag_moving_with_camera=false;
    Hitbox=left.Hitbox;
    m_frames=left.m_frames;
    m_rate=left.m_rate;
    m_layer =left.m_layer;
    frame=0;
    Startpos=Hitbox;
    char* temp = left.name;
    this->name= strcat((char*)left.name,"copy");
    this->filename=filename;
    m_texture = left.m_texture;
};
*/
void Sprite::set_x(int x){Hitbox.x=x;}
void Sprite::set_y(int y){Hitbox.y=y;}
int Sprite::get_x(){return Hitbox.x;}
int Sprite::get_y(){return Hitbox.y;}
int Sprite::get_layr(){return m_layer;}
void Sprite::Update()
{
    //анимация
    if(Stages->Second_Stage_Animation!=-1){
        m_r={Stages->m_Sw*((Stages->Stages[Stages->Second_Stage_Animation].frame/Stages->Stages[Stages->Second_Stage_Animation].rate)%Stages->Stages[Stages->Second_Stage_Animation].frames),m_Sh/Stages->count_stages*Stages->Second_Stage_Animation,Stages->m_Sw,m_Sh/Stages->count_stages};
        if(m_r.x==(Stages->Stages[Stages->Second_Stage_Animation].frames-1)*Stages->m_Sw)
            Stages->Stages[Stages->Second_Stage_Animation].count_repeats++;
        Stages->Stages[Stages->Second_Stage_Animation].frame++;
        if(Stages->Stages[Stages->Second_Stage_Animation].count_repeats==Stages->Stages[Stages->Second_Stage_Animation].repeats)Stages->Second_Stage_Animation=-1;
    }
    else{
        m_r={Stages->m_Sw*((Stages->Stages[Stages->Main_Stage_Animation].frame/Stages->Stages[Stages->Main_Stage_Animation].rate)%Stages->Stages[Stages->Main_Stage_Animation].frames),m_Sh/Stages->count_stages*Stages->Main_Stage_Animation,Stages->m_Sw,m_Sh/Stages->count_stages};
        Stages->Stages[Stages->Main_Stage_Animation].frame++;
    }

}

void Sprite::PrintSprite(SDL_Renderer* ren,Camera* cum,bool is_drawing)
{
    if(is_drawing){
        SDL_Rect r =Hitbox;
        r.x-=cum->get_x();
        r.y-=cum->get_y();
        SDL_RenderCopy(ren,m_texture,&m_r,&r);
    }

}
void Sprite::setAnimation(int Stage,int count){
    Stages->Second_Stage_Animation=Stage;
    Stages->Stages[Stage].repeats=count;
    Stages->Stages[Stage].count_repeats=0;
    Stages->Stages[Stages->Second_Stage_Animation].frame=0;

}
void Sprite::setMainAnimation(int Stage){
    Stages->Main_Stage_Animation=Stage;
    //Stages->Stages[Stages->Main_Stage_Animation].frame=0;
}

void Sprite::ChangeAlpha(int alpha) {
    SDL_SetTextureAlphaMod(m_texture,alpha);
}