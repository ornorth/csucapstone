// g++ -std=c++17 run\ex7.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex7_fancy-movement

#include <iostream>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    app.addGameObject("Player", Shape::RECTANGLE, {200, 0, 150, 255}, 100, 100, 540, 360, 0);

    app.addKeyEvent("Player", KeyCode::D, KeyPressType::HELD, GameAction::SETVAR, ObjectAttribute::X_ACCELERATION,  2);
    app.addKeyEvent("Player", KeyCode::A, KeyPressType::HELD, GameAction::SETVAR, ObjectAttribute::X_ACCELERATION, -2);
    app.addKeyEvent("Player", KeyCode::W, KeyPressType::HELD, GameAction::SETVAR, ObjectAttribute::Y_ACCELERATION, -2);
    app.addKeyEvent("Player", KeyCode::S, KeyPressType::HELD, GameAction::SETVAR, ObjectAttribute::Y_ACCELERATION,  2);


    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_VELOCITY, 10, GameAction::SETVAR, ObjectAttribute::X_VELOCITY, 10);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::X_VELOCITY, -10, GameAction::SETVAR, ObjectAttribute::X_VELOCITY, -10);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::Y_VELOCITY, -10, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY, -10);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::Y_VELOCITY, 10, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY, 10);

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 5: Basic types of user input (Press, Release, Hold)");
}