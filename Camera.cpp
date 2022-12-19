#include "Camera.h"

Camera::Camera(int x,int y,int size)
{
    m_x=x;
    m_y=y;
    offset_x=0;
    offset_y=0;
    m_size=size;
}
void Camera::Update(bool *buttons){
    if (buttons[SDL_SCANCODE_UP]){
        offset_y-=10;
    }
    if (buttons[SDL_SCANCODE_DOWN]){
        offset_y+=10;
    }
    if (buttons[SDL_SCANCODE_LEFT]){
        offset_x-=10;
    }
    if (buttons[SDL_SCANCODE_RIGHT]){
        offset_x+=10;
    }
}
int Camera::get_x(){return m_x;}
int Camera::get_y(){return m_y;}
void Camera::set_x(int x){m_x=x;}
void Camera::set_y(int y){m_y=y;}
void Camera::add_x(int a){m_x+=a;}
void Camera::add_y(int a){m_y+=a;}