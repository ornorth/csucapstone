// g++ -std=c++17 run\ex4.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex4_basic-border-collision

#include <iostream>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    app.addGameObject("rct1", Shape::RECTANGLE, {0, 13, 200, 255}, 100, 100, rand()%800 + 100, rand()%600 + 100, 100);
    app.setObjectValue("rct1", ObjectAttribute::X_VELOCITY, rand()%20 + 1);
    app.setObjectValue("rct1", ObjectAttribute::Y_VELOCITY, rand()%20 + 1);
    app.setObjectValue("rct1", ObjectAttribute::ANG_VELOCITY, 5);

    // Object Events
    app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 4: Basic Border Collision Detection");
}