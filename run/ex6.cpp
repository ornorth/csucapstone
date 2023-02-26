// g++ -std=c++17 run\ex6.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex6_player-input

#include <iostream>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    // Press
    app.addGameObject("shiftySquare", Shape::RECTANGLE, {200, 0, 150, 255}, 100, 100, 540, 360, 0);

    app.addKeyEvent(KeyCode::LEFTARROW,  KeyPressType::DOWN, GameAction::INCVAR, "shiftySquare", ObjectAttribute::X_POSITION, -75);
    app.addKeyEvent(KeyCode::RIGHTARROW, KeyPressType::DOWN, GameAction::INCVAR, "shiftySquare", ObjectAttribute::X_POSITION,  75);
    app.addKeyEvent(KeyCode::UPARROW,    KeyPressType::DOWN, GameAction::INCVAR, "shiftySquare", ObjectAttribute::Y_POSITION, -75);
    app.addKeyEvent(KeyCode::DOWNARROW,  KeyPressType::DOWN, GameAction::INCVAR, "shiftySquare", ObjectAttribute::Y_POSITION,  75);

    // Press and Release
    app.addGameObject("spinnySquare", Shape::RECTANGLE, {0, 13, 200, 255}, 175, 90, 200, 150, 0);

    app.addKeyEvent(KeyCode::SPACE, KeyPressType::DOWN, GameAction::SETVAR, "spinnySquare", ObjectAttribute::ANG_ACCELERATION,  3);
    app.addKeyEvent(KeyCode::SPACE, KeyPressType::UP,   GameAction::SETVAR, "spinnySquare", ObjectAttribute::ANG_ACCELERATION, -2);

    app.addObjectEvent("spinnySquare", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::ANG_VELOCITY, 0, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, 0);
    app.addObjectEvent("spinnySquare", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::ANG_VELOCITY, 0, GameAction::SETVAR, ObjectAttribute::ANG_VELOCITY,     0);

    // Press and Hold
    app.addGameObject("moveyCircle", Shape::CIRCLE, {0, 0, 0, 255}, 100, 100, 800, 500);

    app.addKeyEvent(KeyCode::D, KeyPressType::HELD, GameAction::INCVAR, "moveyCircle", ObjectAttribute::X_POSITION,  7);
    app.addKeyEvent(KeyCode::A, KeyPressType::HELD, GameAction::INCVAR, "moveyCircle", ObjectAttribute::X_POSITION, -7);
    app.addKeyEvent(KeyCode::S, KeyPressType::HELD, GameAction::INCVAR, "moveyCircle", ObjectAttribute::Y_POSITION,  7);
    app.addKeyEvent(KeyCode::W, KeyPressType::HELD, GameAction::INCVAR, "moveyCircle", ObjectAttribute::Y_POSITION, -7);


    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 6: Basic types of user input (Press, Release, Hold)");
}