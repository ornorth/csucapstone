// g++ -std=c++17 run\ex10.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex10_visibility-and-phase

#include <iostream>
#include <random>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    // Debug Objects
    app.addGameObject("obj1", Shape::RECTANGLE, {0, 0, 0, 255}, 100, 175, 350, 350);
    app.addKeyEvent(KeyCode::W, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::Y_POSITION, -5);
    app.addKeyEvent(KeyCode::A, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::X_POSITION, -5);
    app.addKeyEvent(KeyCode::S, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::Y_POSITION,  5);
    app.addKeyEvent(KeyCode::D, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::X_POSITION,  5);
    app.addKeyEvent(KeyCode::Q, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::ANGLE, -3);
    app.addKeyEvent(KeyCode::E, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::ANGLE,  3);

    app.addKeyEvent(KeyCode::ONE, KeyPressType::DOWN, GameAction::SETFLAG, "obj1", ObjectFlag::INVISIBLE, 1);
    app.addKeyEvent(KeyCode::TWO, KeyPressType::DOWN, GameAction::SETFLAG, "obj1", ObjectFlag::INVISIBLE, 0);
    app.addKeyEvent(KeyCode::THREE, KeyPressType::DOWN, GameAction::TOGGLEFLAG, "obj1", ObjectFlag::INVISIBLE);
    app.addKeyEvent(KeyCode::SPACE, KeyPressType::DOWN, GameAction::TOGGLEFLAG, "obj1", ObjectFlag::PHASED);


    app.addGameObject("obj2", Shape::CIRCLE, {113, 175, 0, 255}, 100, 100, 500, 500);
    app.addObjectEvent("obj2", GameEvent::ALWAYS, GameAction::SETVAR, ObjectAttribute::COLOR, {113, 175, 0, 255});
    app.addCollisionEvent("obj1", "obj2", GameAction::SETVAR, "obj2", ObjectAttribute::COLOR, {255, 0, 0, 255});

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 10: Objects can be made invisible, collision can be disabled");
}