// g++ -std=c++17 run\ex3.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex3_state-detection

#include <iostream>
#include <random>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});
    
    app.addGameObject( "rct1", Shape::RECTANGLE, {0, 13, 200, 255}, 100, 100, 400, 360);

    app.setObjectValue("rct1", ObjectAttribute::X_ACCELERATION, 2);

    app.addObjectEvent("rct1", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_VELOCITY,  25, GameAction::SETVAR, ObjectAttribute::X_ACCELERATION, -2);
    app.addObjectEvent("rct1", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_VELOCITY, -25, GameAction::SETVAR, ObjectAttribute::X_ACCELERATION,  2); 
    
    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 3: Motion & Objects' State is Observable");
}