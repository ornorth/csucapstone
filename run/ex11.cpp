// g++ -std=c++17 run\ex11.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex11_space-invaders

#include <iostream>
#include <random>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {30, 0, 40, 2555});

////////////////////////////////////////////////////////////////////////////////
////// GAME OBJECTS
////////////////////////////////////////////////////////////////////////////////
    // Player
    app.addGameObject("Player", Shape::TRIANGLE, {235, 235, 5, 255}, 35, 75, 540, 650);
    
    // Player's projectile
    app.addGameObject("Missile", Shape::CIRCLE, {255, 220, 220, 255}, 7, 25, 1100, 800);
    app.setObjectValue("Missile", ObjectAttribute::USER_DOUBLE_1, 0);   // Inactive

    // Enemies
    app.addGameObject("Enemy1", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 540, 100);
    app.setObjectValue("Enemy1", ObjectAttribute::X_VELOCITY, 3);
    
////////////////////////////////////////////////////////////////////////////////
////// KEY EVENTS
////////////////////////////////////////////////////////////////////////////////
    // Player Movement
    app.addKeyEvent(KeyCode::LEFTARROW,  KeyPressType::HELD, GameAction::INCVAR, "Player", ObjectAttribute::X_POSITION, -8);
    app.addKeyEvent(KeyCode::RIGHTARROW, KeyPressType::HELD, GameAction::INCVAR, "Player", ObjectAttribute::X_POSITION,  8);
    // Fire button
    app.addKeyEvent(KeyCode::SPACE, KeyPressType::DOWN, GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 1);


////////////////////////////////////////////////////////////////////////////////
////// OBJECT EVENTS
////////////////////////////////////////////////////////////////////////////////
    // State 0: Missile is "inactive"
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 0, GameAction::SETFLAG, ObjectFlag::INVISIBLE, 1);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 0, GameAction::SETFLAG, ObjectFlag::PHASED, 1);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 0, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY, 0);

    // ObjectAttribute::X_POSITION, 540/*"Player", ObjectAttribute::X_POSITION*/);

    // State 1: Missile is "prepping"
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::X_POSITION, 540);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::Y_POSITION, 600);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY, -15);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETFLAG, ObjectFlag::INVISIBLE, 0);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETFLAG, ObjectFlag::PHASED, 0);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::USER_DOUBLE_1, 2);

    // State 2: Missile is "active"
    // There are no special events to run here except for collision events, because the missile should be in state 2 if these are running

    // Enemy Events
    app.addObjectEvent("Enemy1", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 800, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy1", GameEvent::OBJ_VAR_IS_LESS, ObjectAttribute::X_POSITION, 300, GameAction::BOUNCE_X);

////////////////////////////////////////////////////////////////////////////////
////// COLLISION EVENTS
////////////////////////////////////////////////////////////////////////////////
    //app.addCollisionEvent

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 10: Objects can be made invisible, collision can be disabled");
}