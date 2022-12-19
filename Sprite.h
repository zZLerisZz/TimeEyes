#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "Camera.h"
#include <string.h>
#include <string>
#include <fstream>
struct Animation{

    int frames;
    int rate;
    int repeats;

    int frame;
    int count_repeats;
    int last_stage;



    Animation() {
        frames = 0;
        rate = 0;
        repeats = 0;
        frame = 0;
        count_repeats = 0;
    }


};
struct StagesAnim{
    StagesAnim(char* filename){
        this->Main_Stage_Animation=0;
        this->Second_Stage_Animation=0;
        std::ifstream file(filename);
        file >> count_stages;
        file >> m_Sw;
        Stages=new Animation[count_stages];
        for(int i=0;i<count_stages;i++) {
            file >> Stages[i].frames;
            file >> Stages[i].rate;
        }
        file.close();
        Main_Stage_Animation=0;
        Second_Stage_Animation=-1;
    }
    ~StagesAnim(){
        delete[] Stages;
    }
    Animation *Stages;
    int m_Sw;
    int count_stages;
    int Main_Stage_Animation;
    int Second_Stage_Animation;
};



using namespace std;
class Sprite {
private:
    SDL_Texture *m_texture;
    int m_layer;
    SDL_Rect m_r;
    const char* filename;


    int m_Sw;
    int m_Sh;
public:
    void ChangeAlpha(int alpha);

    StagesAnim* Stages;
    string name;
    SDL_Rect Hitbox;
    bool flag_collision;
    bool flag_moving_with_camera;
    int moving_with_camera_offset_x;
    int moving_with_camera_offset_y;

    Sprite(){};
    Sprite(SDL_Renderer* ren, string name,const char* filename,int w,int h,int x,int y,int layr,char* file_config_animation);
    //Sprite(const Sprite &Sp1, char* NewName, SDL_Renderer* ren);
    ~Sprite();

    void setAnimation(int Stage,int count);
    void setMainAnimation(int Stage);
    void Update();

    void set_x(int x);
    void set_y(int y);
    int get_x();
    int get_y();
    int get_layr();

    void PrintSprite(SDL_Renderer* ren,Camera* cum,bool is_drawing);

    //Sprite operator=(const Sprite &left);
};

