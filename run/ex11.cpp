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
    app.addGameObject( "Enemy1", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 490, 100);
    app.addGameObject( "Enemy2", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 540, 100);
    app.addGameObject( "Enemy3", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 590, 100);
    app.addGameObject( "Enemy4", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 490, 160);
    app.addGameObject( "Enemy5", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 540, 160);
    app.addGameObject( "Enemy6", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 590, 160);
    app.addGameObject( "Enemy7", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 490, 220);
    app.addGameObject( "Enemy8", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 540, 220);
    app.addGameObject( "Enemy9", Shape::RECTANGLE, {100, 255, 100, 255}, 30, 45, 590, 220);

    app.setObjectValue("Enemy1", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy2", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy3", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy4", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy5", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy6", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy7", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy8", ObjectAttribute::X_VELOCITY, 3);
    app.setObjectValue("Enemy9", ObjectAttribute::X_VELOCITY, 3);
  
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
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::X_POSITION, ObjectAttribute::X_POSITION, "Player");
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::Y_POSITION, ObjectAttribute::Y_POSITION, "Player");
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::Y_VELOCITY, -15);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETFLAG, ObjectFlag::INVISIBLE, 0);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETFLAG, ObjectFlag::PHASED, 0);
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 1, GameAction::SETVAR, ObjectAttribute::USER_DOUBLE_1, 2);

    // State 2: Missile is "active"
    // There are no special events to run here except for collision events, because the missile should be in state 2 if these are running

    // State 3: Missile is colliding
    // This is an intermediary phase to allow the collision logic to run before phasing the objects
    app.addObjectEvent("Missile", GameEvent::OBJ_VAR_EQUALS, ObjectAttribute::USER_DOUBLE_1, 3, GameAction::SETVAR, ObjectAttribute::USER_DOUBLE_1, 0);

    // Enemy Events
    // Left Column
    app.addObjectEvent("Enemy1", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 850, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy1", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 150, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy1", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 150, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    app.addObjectEvent("Enemy4", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 850, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy4", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 150, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy4", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 150, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    app.addObjectEvent("Enemy7", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 850, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy7", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 150, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy7", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 150, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    // Middle Column
    app.addObjectEvent("Enemy2", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 900, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy2", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 200, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy2", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 200, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    app.addObjectEvent("Enemy5", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 900, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy5", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 200, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy5", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 200, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    app.addObjectEvent("Enemy8", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 900, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy8", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 200, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy8", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 200, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    // Right Column
    app.addObjectEvent("Enemy3", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 950, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy3", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 250, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy3", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 250, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    app.addObjectEvent("Enemy6", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 950, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy6", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 250, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy6", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 250, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);

    app.addObjectEvent("Enemy9", GameEvent::OBJ_VAR_IS_GREATER, ObjectAttribute::X_POSITION, 950, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy9", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 250, GameAction::BOUNCE_X);
    app.addObjectEvent("Enemy9", GameEvent::OBJ_VAR_IS_LESS,    ObjectAttribute::X_POSITION, 250, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 30);


////////////////////////////////////////////////////////////////////////////////
////// COLLISION EVENTS
////////////////////////////////////////////////////////////////////////////////
    app.addCollisionEvent("Missile", "Enemy1", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy1", GameAction::SETFLAG, "Enemy1", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy1", GameAction::SETFLAG, "Enemy1", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy2", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy2", GameAction::SETFLAG, "Enemy2", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy2", GameAction::SETFLAG, "Enemy2", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy3", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy3", GameAction::SETFLAG, "Enemy3", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy3", GameAction::SETFLAG, "Enemy3", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy4", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy4", GameAction::SETFLAG, "Enemy4", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy4", GameAction::SETFLAG, "Enemy4", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy5", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy5", GameAction::SETFLAG, "Enemy5", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy5", GameAction::SETFLAG, "Enemy5", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy6", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy6", GameAction::SETFLAG, "Enemy6", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy6", GameAction::SETFLAG, "Enemy6", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy7", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy7", GameAction::SETFLAG, "Enemy7", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy7", GameAction::SETFLAG, "Enemy7", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy8", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy8", GameAction::SETFLAG, "Enemy8", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy8", GameAction::SETFLAG, "Enemy8", ObjectFlag::PHASED, 1);

    app.addCollisionEvent("Missile", "Enemy9", GameAction::SETVAR, "Missile", ObjectAttribute::USER_DOUBLE_1, 3);
    app.addCollisionEvent("Missile", "Enemy9", GameAction::SETFLAG, "Enemy9", ObjectFlag::INVISIBLE, 1);
    app.addCollisionEvent("Missile", "Enemy9", GameAction::SETFLAG, "Enemy9", ObjectFlag::PHASED, 1);

    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 10: Objects can be made invisible, collision can be disabled");
}