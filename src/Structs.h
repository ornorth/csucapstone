#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL.h"
//#include "GameObject.h"
class GameObject;


struct Color {
    int r;
    int g;
    int b;
    int a;
};

enum Shape {
    SQUARE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
};

struct KeyEvent {
    SDL_KeyCode key;
    GameObject& target;
    //action
};

#endif