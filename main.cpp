#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include "Sprite.h"
#include "Map.h"
#include "Camera.h"
#include "FLOOR.h"
#include <windows.h>
#define Komnata 9
#define Sound 7
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>

int WINDOW_WIDTH=1920;
int WINDOW_HEIGHT=1080;

SDL_Window * gWindow=NULL;
SDL_Renderer* gRender=NULL;
Mix_Music **music = new Mix_Music*[4];

string name_player;

void Init();
void DeInit(int);

void Init()
{
    TTF_Init();
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        printf("SDL не инициолезирован! Ошибка: %s",SDL_GetError());
        DeInit(1);
    }

    if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG))
    {
        printf("SDL_IMG не инициолезирован! Ошибка: %s",IMG_GetError());
        DeInit(1);
    }

    gWindow = SDL_CreateWindow("TimEyes",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN |SDL_WINDOW_RESIZABLE);
    if(gWindow==NULL)
    {
        printf("SDL не создано окно! Ошибка: %s",SDL_GetError());
        DeInit(1);
    }

    gRender = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);//-1-видеокарта по умолчанию SDL_RENDERER_ACCELERATED-графический ускоритель
    if(gRender==NULL)
    {
        printf("SDL не создан renderer! Ошибка: %s",SDL_GetError());
        DeInit(1);
    }
    SDL_Delay(2);

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
        printf("SDL не создан mixer! Звук умер! Ошибка: %s",SDL_GetError());
        DeInit(1);
    }
}
void DeInit(int error)
{
    if(gRender != NULL)SDL_DestroyRenderer(gRender);
    if(gWindow != NULL)SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
    exit(error);

}

void Spravka()
{
    SDL_Surface* temp;
    temp = IMG_Load("spravka.png");
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* spr=SDL_CreateTextureFromSurface(gRender, temp);
    SDL_FreeSurface(temp);
    Camera camera(0,0,1);
    bool isRunningMenu=1;
    int quit = 0,x=0,y=0;
    SDL_Event Event;
    while(isRunningMenu) {
        SDL_PollEvent(&Event);
        switch (Event.type) {
            case SDL_QUIT:
                isRunningMenu = 0;
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunningMenu = false;
                        break;
                }
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(x>=1244&&x<=1471&&y>=942&&y<=1018)
                    isRunningMenu = 0;
                break;
        }

        SDL_SetRenderDrawColor(gRender, 200, 200, 200, 255);
        SDL_RenderClear(gRender);
        SDL_RenderCopy(gRender,spr,NULL,NULL);
        SDL_RenderPresent(gRender);
        SDL_Delay(2);
    }

}
void Records()
{
    ifstream file("records.txt");
    vector <pair<int,string>>arr(99);
    int n=0;
    int f;
    string s;
    while (!file.eof()){
        file>>s;
        file>>f;
        arr[n++]=(pair<int,string>(f,s));
    }
    file.close();
    sort(arr.begin(),arr.end());

    SDL_Surface* text;
// Set color to black
    SDL_Color color = { 0, 0, 0 };

    TTF_Font* font;
    font = TTF_OpenFont("timesnewromanpsmt.ttf", 50);
    if ( !font ) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }
    text = TTF_RenderText_Solid( font, "Hello World!", color );
    if ( !text ) {
        cout << "Failed to render text: " << TTF_GetError() << endl;
    }
    SDL_Texture* text_texture;



    SDL_Surface* temp;
    temp = IMG_Load("Records.png");
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* spr=SDL_CreateTextureFromSurface(gRender, temp);
    SDL_FreeSurface(temp);
    Camera camera(0,0,1);
    bool isRunningMenu=1;
    int quit = 0,x=0,y=0;
    SDL_Event Event;
    while(isRunningMenu) {
        SDL_PollEvent(&Event);
        switch (Event.type) {
            case SDL_QUIT:
                isRunningMenu = 0;
                TTF_CloseFont( font );
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunningMenu = false;
                        TTF_CloseFont( font );
                        break;
                }
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(x>=1348&&x<=1581&&y>=962&&y<=1055)
                    isRunningMenu = 0;
                break;
        }

        SDL_SetRenderDrawColor(gRender, 200, 200, 200, 255);
        SDL_RenderClear(gRender);
        SDL_RenderCopy(gRender,spr,NULL,NULL);

        string ss="";
        char a[10];
        int count=0;
        for(int i=0;i<99&&count<10;i++){
            ss="";
            if(arr[i].second!="") {
                itoa(count+1,a,10);
                ss+=a;
                ss += ")";
                ss += arr[i].second;
                ss +="       Sec: ";
                itoa(arr[i].first,a,10);
                ss+=a;

                text = TTF_RenderText_Solid(font, ss.c_str(), color);
                if (text != NULL) {
                    SDL_Rect dest = {680, 200+ count * text->h, text->w, text->h};
                    text_texture = SDL_CreateTextureFromSurface(gRender, text);
                    SDL_RenderCopy(gRender, text_texture, NULL, &dest);
                    SDL_DestroyTexture(text_texture);
                    SDL_FreeSurface(text);
                }
                count++;
            }

        }


        SDL_RenderPresent(gRender);
        SDL_Delay(2);
    }
    s.erase(s.begin(),s.end());
    if(text_texture!=NULL)SDL_DestroyTexture( text_texture );
    arr.erase(arr.begin(),arr.end());
    SDL_DestroyTexture( text_texture );
    TTF_CloseFont( font );

}
void Pause()
{
    SDL_Surface* temp;
    temp = IMG_Load("Pause.png");
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* spr=SDL_CreateTextureFromSurface(gRender, temp);
    SDL_FreeSurface(temp);
    Camera camera(0,0,1);
    bool isRunningMenu=1;
    int quit = 0,x=0,y=0;
    SDL_Event Event;
    while(isRunningMenu) {
        SDL_PollEvent(&Event);
        switch (Event.type) {
            case SDL_QUIT:
                isRunningMenu = 0;
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        isRunningMenu = false;
                        break;
                }
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(x>=600&&x<=1201&&y>=207&&y<=313)
                    isRunningMenu = 0;
                if(x>=599&&x<=1200&&y>=387&&y<=493)
                    DeInit(0);
        }

        SDL_SetRenderDrawColor(gRender, 200, 200, 200, 255);
        SDL_RenderClear(gRender);
        SDL_RenderCopy(gRender,spr,NULL,NULL);
        SDL_RenderPresent(gRender);
        SDL_Delay(2);
    }

}

void Menu()
{
    TTF_Font* font;
    font = TTF_OpenFont("timesnewromanpsmt.ttf", 50);
    if ( !font ) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }
    SDL_Surface* text;
// Set color to black
    SDL_Color color = { 255, 255, 255 };

    SDL_Texture* text_texture;



    SDL_Surface* temp;
    temp = IMG_Load("inc.png");
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* inc=SDL_CreateTextureFromSurface(gRender, temp);
    SDL_RenderCopy( gRender, inc,NULL, NULL );
    SDL_FreeSurface(temp);
    SDL_RenderPresent(gRender);

    SDL_Delay(5000);


    temp = IMG_Load("backg.png");
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* beck=SDL_CreateTextureFromSurface(gRender, temp);
    SDL_FreeSurface(temp);
    bool isRunningMenu=1;
    int x=0,y=0;
    SDL_Event Event;
    SDL_StartTextInput();
    string in="1";
    while(isRunningMenu) {
        SDL_PollEvent(&Event);
        switch (Event.type) {
            case SDL_QUIT:
                isRunningMenu = 0;
                break;
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if(text_texture!=NULL)SDL_DestroyTexture( text_texture );
                        SDL_StopTextInput();
                        TTF_CloseFont( font );
                        in.erase(in.begin(),in.end());
                        DeInit(0);
                        break;
                }
                if (Event.key.keysym.sym == SDLK_BACKSPACE && in.size()) {
                    in.pop_back();
                    cout << " > " << in << endl;
                }
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                break;
            case SDL_TEXTINPUT:
                in += Event.text.text;
                cout << " > " << in << endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(x>=711&&x<=1070&&y>=360&&y<=429&&text!=NULL)
                    isRunningMenu = 0;
                if(x>=772&&x<=1071&&y>=533&&y<=622)
                    Spravka();
                if(x>=772&&x<=1071&&y>=456&&y<=525)
                    Records();
                if(x>=722&&x<=1071&&y>=653&&y<=722){

                    if(text_texture!=NULL)SDL_DestroyTexture( text_texture );

                    SDL_StopTextInput();
                    TTF_CloseFont( font );
                    in.erase(in.begin(),in.end());
                    DeInit(0);
                }
                break;
        }
        name_player = in;


        SDL_SetRenderDrawColor(gRender, 200, 200, 200, 255);
        SDL_RenderClear(gRender);



        SDL_RenderCopy(gRender,beck,NULL,NULL);

        text = TTF_RenderText_Solid( font, in.c_str(), color );

        if ( text!=NULL ) {
            SDL_Rect dest = { 1282, 946, text->w, text->h };
            text_texture = SDL_CreateTextureFromSurface( gRender, text );
            SDL_RenderCopy( gRender, text_texture,NULL, &dest );
            SDL_DestroyTexture( text_texture );
            SDL_FreeSurface( text );
        }



        SDL_RenderPresent(gRender);

        SDL_Delay(2);

    }

    SDL_StopTextInput();
    temp = IMG_Load("loading.jpg");
    if (temp == NULL) {
        std::cout << "Can't load: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* load=SDL_CreateTextureFromSurface(gRender, temp);
    SDL_FreeSurface(temp);

    SDL_SetRenderDrawColor(gRender, 200, 200, 200, 255);
    SDL_RenderClear(gRender);
    SDL_RenderCopy(gRender,load,NULL,NULL);
    SDL_RenderPresent(gRender);
    in.erase(in.begin(),in.end());


}

int main(int argc,char**argv) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    bool buttons[SDL_NUM_SCANCODES]{};
    srand(time(NULL));

    string name="player";


    Init();
    Menu();


    SDL_Event Event;
    bool isRunning=true;


    int MusCount=0, MusC1=MusCount;

    music[1] = Mix_LoadMUS("scifi.wav");
    music[0] = Mix_LoadMUS("SOUL.wav");
    music[2] = Mix_LoadMUS("NARC.wav");
    music[3] = Mix_LoadMUS("TKILLER.wav");
    Mix_Chunk *stepsound = Mix_LoadWAV("Steps.wav");

    Camera c(-3500,-3500,1);
    c.offset_x=-WINDOW_WIDTH/2;
    c.offset_y=-WINDOW_HEIGHT/2;
    Map m(gRender,&c);

    int StartSize=15;

    FLoor Game(StartSize, 10, 10);
    Game.GENERATE();
    Game.PrintTheFloor();

    //Размещение
    //Размещение
    cout<<"Начинается размещение";
    pair<int,int> StartPos;
    pair<pair<pair<int,int>,Sprite*>,int> A = m.CreateFloor(&Game, gRender);
    StartPos.first = A.first.first.first;
    StartPos.second = A.first.first.second;
    cout<<StartPos.first<<" "<<StartPos.second;
    //Размещение
    //Игрок поставиться в середину стартовой комнаты
    Sprite s(gRender,name,"player.png",100,100,StartPos.first+Komnata*70,StartPos.second+Komnata*70,2,"player_cfg.txt");
    m.CreatePl(rand()%2, &s);
    m.add_sprite(&s);
    m.sprite_with_camera=&s;
    //Размещение
    //Игрок поставиться в середину стартовой комнаты
    Sprite** BG = new Sprite*[4];

    BG[0] = new Sprite(gRender,"BG1","space3.png",WINDOW_WIDTH,WINDOW_HEIGHT,StartPos.first+Komnata*70,StartPos.second+Komnata*70,0,"grid_cfg.txt");
    BG[0]->flag_moving_with_camera=1;
    BG[0]->moving_with_camera_offset_y=0;

    BG[1] = new Sprite(gRender,"BG2","space2.jpg",WINDOW_WIDTH,WINDOW_HEIGHT,StartPos.first+Komnata*70,StartPos.second+Komnata*70,0,"grid_cfg.txt");
    BG[1]->flag_moving_with_camera=1;
    BG[1]->moving_with_camera_offset_y=0;

    BG[2] = new Sprite(gRender,"BG3","space1.jpg",WINDOW_WIDTH,WINDOW_HEIGHT,StartPos.first+Komnata*70,StartPos.second+Komnata*70,0,"grid_cfg.txt");
    BG[2]->flag_moving_with_camera=1;
    BG[2]->moving_with_camera_offset_y=0;

    BG[3] = new Sprite(gRender,"BG4","space4.jpg",WINDOW_WIDTH,WINDOW_HEIGHT,StartPos.first+Komnata*70,StartPos.second+Komnata*70,0,"grid_cfg.txt");
    BG[3]->flag_moving_with_camera=1;
    BG[3]->moving_with_camera_offset_y=0;


    cout<<"AAAAAAA";

    Sprite Alarm(gRender,"ALARM","Light.png",WINDOW_WIDTH,WINDOW_HEIGHT,StartPos.first+Komnata*70,StartPos.second+Komnata*70,3,"grid_cfg.txt");
    Alarm.flag_moving_with_camera=1;
    Alarm.moving_with_camera_offset_y=0;


    m.add_sprite(BG[0]);
    cout<<"AAAAAAA";

/*

      Sprite s3(gRender,"2","Enemy.png",70,70,70,70,2,300,1);
      m.add_sprite(&s3);
      Sprite s4(gRender,"3","Enemy.png",70,70,-70,0,2,50,1);
      m.add_sprite(&s4);
      Sprite s6(gRender,"4","Enemy.png",70,70,70,140,2,50,1);
      m.add_sprite(&s6);
      Sprite s7(gRender,"5","Enemy.png",70,70,140,140,2,50,1);
      m.add_sprite(&s7);
*/
//    Sprite* tmp;
//    if(!m.find_sprite(name,1,&tmp))DeInit(1);
//    cout<<tmp->name;
//    tmp->set_rate(5);
    bool fog = false;
    int lastAD=0;
    bool CompleteFlag=false;
    bool WIN = false;
    while(isRunning) {
        if (CompleteFlag == false && m.dead_boss==true){
            m.add_sprite(A.first.second);
            CompleteFlag=true;
        }
        if (Mix_PlayingMusic() == 0) {
            Mix_VolumeMusic(Sound);
            if (Mix_PlayMusic(music[MusCount], -1) == -1) {
                return 1;
            }
        }
        if (fog == 0) {
            fog = 1;
            if (Game.FloorNumber == 2)
                m.add_sprite(&Alarm);
        }
        if (m.Square(&s, A.first.second) > 0 && CompleteFlag==true) {
            if(Game.FloorNumber==3){
                WIN=true;
                break;
            }
            CompleteFlag=false;
            for (int i = 0; i < 4; i++) {
                int size = m.data[i].size();
                for (int j = 0; j < size; ++j) {
                    auto it = m.data[i].begin();
                    //advance(it,0);
                    if (it->first != "player" && it->first != "freand")
                        m.data[i].erase(it);
                }
                m.Enemy.erase(m.Enemy.begin(), m.Enemy.end());
            }
            Game.FloorNumber++;
            m.add_sprite(BG[Game.FloorNumber]);
            Game.GENERATE();
            Mix_HaltMusic();
            A = m.CreateFloor(&Game, gRender);
            StartPos.first = A.first.first.first;
            StartPos.second = A.first.first.second;
            s.set_x(StartPos.first + Komnata * 70);
            s.set_y(StartPos.second + Komnata * 70);
            m.sprite_with_camera = &s;
            m.Update(buttons);
            MusCount++;
            if (MusCount == 4) MusCount = 0;
            fog = false;
        }
        int start = SDL_GetTicks();
        SDL_PollEvent(&Event);
        switch (Event.type) {
            case SDL_QUIT:
                isRunning = 0;
                break;
            case SDL_WINDOWEVENT:
                if (Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    WINDOW_WIDTH = Event.window.data1;
                    WINDOW_HEIGHT = Event.window.data2;
                }
                break;
            case SDL_MOUSEBUTTONDOWN: {
                if (Event.key.repeat == 0)
                    buttons[Event.button.button] = true;
            }
                break;
            case SDL_MOUSEBUTTONUP:
                if (Event.key.repeat == 0)
                    buttons[Event.button.button] = false;
                break;
            case SDL_KEYDOWN:
                if (Event.key.repeat == 0)
                    buttons[Event.key.keysym.scancode] = true;
                switch (Event.key.keysym.sym) {
                    case SDLK_f:
                        //ничего не делает
                        //??
                        break;
                    case SDLK_ESCAPE:
                        Pause();
                        break;
                    case SDLK_1:
                        s.setMainAnimation(0);
                        break;
                    case SDLK_2:
                        s.setMainAnimation(1);
                        break;
                    case SDLK_3:
                        s.setMainAnimation(2);
                        break;
                    case SDLK_4:
                        s.setAnimation(3, 1);
                        break;
                    case SDLK_r:
                        for (int i = 0; i < 4; i++) {
                            int size = m.data[i].size();
                            for (int j = 0; j < size; ++j) {
                                auto it = m.data[i].begin();
                                //advance(it,0);
                                if (it->first != "player" && it->first != "freand")
                                    m.data[i].erase(it);
                            }
                            m.Enemy.erase(m.Enemy.begin(), m.Enemy.end());
                        }
                        Game.FloorNumber++;
                        m.add_sprite(BG[Game.FloorNumber]);
                        Game.GENERATE();
                        Mix_HaltMusic();
                        A = m.CreateFloor(&Game, gRender);
                        StartPos.first = A.first.first.first;
                        StartPos.second = A.first.first.second;
                        s.set_x(StartPos.first + Komnata * 70);
                        s.set_y(StartPos.second + Komnata * 70);
                        m.sprite_with_camera = &s;
                        m.Update(buttons);
                        MusCount++;
                        fog = false;
                        if (MusCount == 4) MusCount = 0;
                        break;
                }
                break;
            case SDL_KEYUP:
                if (Event.key.repeat == 0)
                    buttons[Event.key.keysym.scancode] = false;
                break;
        }
        //временно
        double startt;
        SDL_Rect tmp = m.sprite_with_camera->Hitbox;
        if (buttons[SDL_SCANCODE_W] || buttons[SDL_SCANCODE_A] || buttons[SDL_SCANCODE_D] || buttons[SDL_SCANCODE_S])
            if ((clock() - startt) / 1000 > 0.25) {
                startt = clock();
                Mix_PlayChannel(-1, stepsound, 0);
            }
        if (buttons[SDL_SCANCODE_W]){
            m.sprite_with_camera->set_y(m.sprite_with_camera->get_y()-10);
        }
        if (buttons[SDL_SCANCODE_S]){
            m.sprite_with_camera->set_y(m.sprite_with_camera->get_y()+10);
        }
        if (buttons[SDL_SCANCODE_A]){
            m.sprite_with_camera->set_x(m.sprite_with_camera->get_x()-10);
            m.sprite_with_camera->setMainAnimation(0);
            lastAD=0;
        }
        if (buttons[SDL_SCANCODE_D]){
            m.sprite_with_camera->set_x(m.sprite_with_camera->get_x()+10);
            m.sprite_with_camera->setMainAnimation(6);
            lastAD=1;
        }
        if(!buttons[SDL_SCANCODE_A]&&!buttons[SDL_SCANCODE_D])
        {
            if(lastAD)m.sprite_with_camera->setMainAnimation(7);
            else m.sprite_with_camera->setMainAnimation(1);
        }
        c.Update(buttons);
        //временно
        m.collision(m.sprite_with_camera, tmp);
        //c.Update(buttons,&m,&s);

        SDL_SetRenderDrawColor(gRender, 200, 200, 200, 255);
        SDL_RenderClear(gRender);
        m.Update(buttons);
        m.print();
        SDL_RenderPresent(gRender);
        int time = SDL_GetTicks() - start;
        if (time < 0) continue; // if time is negative, the time probably overflew, so continue asap

        int sleepTime = 17 - time;
        if (sleepTime > 0) {
            SDL_Delay(sleepTime);
        }
    if (m.PLDeath()) {
        WIN = false;
        Menu();
    }
    }
    int Result = clock() - m.startg;
    if (WIN==true)
    {
        ofstream F;  //создаем стреам
        cout<<name_player;
        F.open("records.txt", ios::app); //говорим в какой файл
        F.seekp(0, ios::end); //перемещаемся в конец файла
        F << "\n"; //говорим что конец строки
        F << name_player;  //Пишем строку
        F<<" ";
        F<<Result/1000;
        F.close(); // закрываем файл
        Records();
    }
    DeInit(0);
    return 0;
}