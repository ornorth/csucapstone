// g++ -std=c++17 run\ex6.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex6_player-input

#include <iostream>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    // Press
    app.addGameObject("shiftySquare", Shape::RECTANGLE, {200, 0, 150, 255}, 100, 100, 540, 360, 0);

    app.addKeyEvent("shiftySquare", KeyCode::LEFTARROW,  KeyPressType::DOWN, GameAction::INCVAR, ObjectAttribute::X_POSITION, -75);
    app.addKeyEvent("shiftySquare", KeyCode::RIGHTARROW, KeyPressType::DOWN, GameAction::INCVAR, ObjectAttribute::X_POSITION,  75);
    app.addKeyEvent("shiftySquare", KeyCode::UPARROW,    KeyPressType::DOWN, GameAction::INCVAR, ObjectAttribute::Y_POSITION, -75);
    app.addKeyEvent("shiftySquare", KeyCode::DOWNARROW,  KeyPressType::DOWN, GameAction::INCVAR, ObjectAttribute::Y_POSITION,  75);

    // Press and Release
    app.addGameObject("spinnySquare", Shape::RECTANGLE, {0, 13, 200, 255}, 175, 90, 200, 150, 0);

    app.addKeyEvent("spinnySquare", KeyCode::SPACE, KeyPressType::DOWN, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION,  3);
    app.addKeyEvent("spinnySquare", KeyCode::SPACE, KeyPressType::UP,   GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, -2);

    app.addObjectEvent("spinnySquare", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::ANG_VELOCITY, 0, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, 0);
    app.addObjectEvent("spinnySquare", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::ANG_VELOCITY, 0, GameAction::SETVAR, ObjectAttribute::ANG_VELOCITY,     0);

    // Press and Hold
    app.addGameObject("moveyCircle", Shape::CIRCLE, {0, 0, 0, 255}, 100, 100, 800, 500);

    app.addKeyEvent("moveyCircle", KeyCode::D, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::X_POSITION,  7);
    app.addKeyEvent("moveyCircle", KeyCode::A, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::X_POSITION, -7);
    app.addKeyEvent("moveyCircle", KeyCode::S, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::Y_POSITION,  7);
    app.addKeyEvent("moveyCircle", KeyCode::W, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::Y_POSITION, -7);


    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 6: Basic types of user input (Press, Release, Hold)");
}