#pragma once
#include <SDL2/SDL.h>
//#include "Map.h"

//#include "Sprite.h"
class Camera {
private:
    int m_x;
    int m_y;
    int m_size;
public:
    int offset_x;
    int offset_y;
    Camera(int x,int y,int size);
    void Update(bool *buttons);
    void add_x(int a);
    void add_y(int a);
    int get_x();
    int get_y();
    void set_x(int x);
    void set_y(int y);
};