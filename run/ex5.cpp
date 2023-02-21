// g++ -std=c++17 run\ex5.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex5_bounce-and-change

#include <iostream>
#include <random>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    // Complicated rectangle
    app.addGameObject("rct1", Shape::RECTANGLE, {0, 13, 200, 255}, 100, 100, rand()%800 + 100, rand()%600 + 100, 100);
    app.setObjectValue("rct1", ObjectAttribute::X_VELOCITY, rand()%20 + 1);
    app.setObjectValue("rct1", ObjectAttribute::Y_VELOCITY, rand()%20 + 1);

    // Object Events
    app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::SETVAR,   ObjectAttribute::ANG_ACCELERATION, 0.5);
    app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::INCVAR,   ObjectAttribute::HEIGHT, 20);
    app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::X_VELOCITY, 1.05);
    app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::Y_VELOCITY, 1.05);

    app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);
    app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::SETVAR,   ObjectAttribute::ANG_ACCELERATION, -0.5);
    app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::INCVAR,   ObjectAttribute::WIDTH, 20);
    app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::X_VELOCITY, 0.95);
    app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::Y_VELOCITY, 0.95);

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 5: More Ability to Mutate Objects During Runtime");
}