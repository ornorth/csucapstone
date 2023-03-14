// g++ -std=c++17 run\ex8.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex8_collision

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

    app.addGameObject("obj2", Shape::CIRCLE, {0, 0, 0, 255}, 125, 80, 500, 500);
    app.addKeyEvent(KeyCode::UPARROW,    KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::Y_POSITION, -5);
    app.addKeyEvent(KeyCode::LEFTARROW,  KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::X_POSITION, -5);
    app.addKeyEvent(KeyCode::DOWNARROW,  KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::Y_POSITION,  5);
    app.addKeyEvent(KeyCode::RIGHTARROW, KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::X_POSITION,  5);
    app.addKeyEvent(KeyCode::COMMA,      KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::ANGLE, -3);
    app.addKeyEvent(KeyCode::PERIOD,     KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::ANGLE,  3);

    app.addGameObject("obj3", Shape::TRIANGLE, {0, 0, 0, 255}, 125, 80, 600, 200);
    app.addKeyEvent(KeyCode::I, KeyPressType::HELD, GameAction::INCVAR, "obj3", ObjectAttribute::Y_POSITION, -5);
    app.addKeyEvent(KeyCode::J, KeyPressType::HELD, GameAction::INCVAR, "obj3", ObjectAttribute::X_POSITION, -5);
    app.addKeyEvent(KeyCode::K, KeyPressType::HELD, GameAction::INCVAR, "obj3", ObjectAttribute::Y_POSITION,  5);
    app.addKeyEvent(KeyCode::L, KeyPressType::HELD, GameAction::INCVAR, "obj3", ObjectAttribute::X_POSITION,  5);
    app.addKeyEvent(KeyCode::U, KeyPressType::HELD, GameAction::INCVAR, "obj3", ObjectAttribute::ANGLE, -3);
    app.addKeyEvent(KeyCode::O, KeyPressType::HELD, GameAction::INCVAR, "obj3", ObjectAttribute::ANGLE,  3);

    // Color changing
    Color black = {0, 0, 0, 255};
    Color red = {255, 0, 0, 255};
    app.addObjectEvent("obj1", GameEvent::ALWAYS, GameAction::SETVAR, ObjectAttribute::COLOR, black);
    app.addObjectEvent("obj2", GameEvent::ALWAYS, GameAction::SETVAR, ObjectAttribute::COLOR, black);
    app.addObjectEvent("obj3", GameEvent::ALWAYS, GameAction::SETVAR, ObjectAttribute::COLOR, black);

    app.addCollisionEvent("obj1", "obj2", GameAction::SETVAR, "obj1", ObjectAttribute::COLOR, red);
    app.addCollisionEvent("obj1", "obj2", GameAction::SETVAR, "obj2", ObjectAttribute::COLOR, red);    

    app.addCollisionEvent("obj1", "obj3", GameAction::SETVAR, "obj1", ObjectAttribute::COLOR, red);
    app.addCollisionEvent("obj1", "obj3", GameAction::SETVAR, "obj3", ObjectAttribute::COLOR, red);    

    app.addCollisionEvent("obj2", "obj3", GameAction::SETVAR, "obj2", ObjectAttribute::COLOR, red);
    app.addCollisionEvent("obj2", "obj3", GameAction::SETVAR, "obj3", ObjectAttribute::COLOR, red);    

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 8: Collision Detection (Testing Environment)");
}