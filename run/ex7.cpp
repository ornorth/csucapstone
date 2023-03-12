// g++ -std=c++17 run\ex7.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex7_fancy-movement

#include <iostream>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    app.addGameObject("Player", Shape::RECTANGLE, {200, 0, 150, 255}, 100, 100, 540, 360, 0);

    app.addKeyEvent(KeyCode::W, KeyPressType::DOWN, GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_2, -1);
    app.addKeyEvent(KeyCode::W, KeyPressType::UP,   GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_2,  1);
    app.addKeyEvent(KeyCode::A, KeyPressType::DOWN, GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_1, -1);
    app.addKeyEvent(KeyCode::A, KeyPressType::UP,   GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_1,  1);
    app.addKeyEvent(KeyCode::S, KeyPressType::DOWN, GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_2,  1);
    app.addKeyEvent(KeyCode::S, KeyPressType::UP,   GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_2, -1);
    app.addKeyEvent(KeyCode::D, KeyPressType::DOWN, GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_1,  1);
    app.addKeyEvent(KeyCode::D, KeyPressType::UP,   GameAction::INCVAR, "Player", ObjectAttribute::USER_DOUBLE_1, -1);

    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::USER_DOUBLE_1, 0, GameAction::SETVAR, ObjectAttribute::X_VELOCITY,  7);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::USER_DOUBLE_1, 0, GameAction::SETVAR, ObjectAttribute::X_VELOCITY, -7);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_EQUALS,     ObjectAttribute::USER_DOUBLE_1, 0, GameAction::SCALEVAR, ObjectAttribute::X_VELOCITY,  0.9);

    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::USER_DOUBLE_2, 0, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY,  7);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::USER_DOUBLE_2, 0, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY, -7);
    app.addObjectEvent("Player", GameEvent::OBJ_VAR_EQUALS,     ObjectAttribute::USER_DOUBLE_2, 0, GameAction::SCALEVAR, ObjectAttribute::Y_VELOCITY,  0.9);

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 7: Simple Demonstration of potential for complex motion");
}