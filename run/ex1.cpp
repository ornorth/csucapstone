// g++ -std=c++17 run\ex1.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex1_draw_objects

#include <iostream>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    app.addGameObject("rct1", Shape::RECTANGLE, {255, 0, 0,   255}, 100, 100, 200, 100);
    app.addGameObject("rct2", Shape::RECTANGLE, {0,   0, 255, 255}, 200, 100, 400, 100);
    app.addGameObject("tri1", Shape::TRIANGLE,  {255, 0, 0,   255}, 150, 100, 200, 300);
    app.addGameObject("tri2", Shape::TRIANGLE,  {0,   0, 255, 255}, 100, 200, 400, 300);
    app.addGameObject("cir1", Shape::CIRCLE,    {255, 0, 0,   255}, 100, 100, 200, 500);
    app.addGameObject("cir2", Shape::CIRCLE,    {0,   0, 255, 255}, 175, 100, 400, 500);


    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 1: Drawwing Objects to the Screen");
}