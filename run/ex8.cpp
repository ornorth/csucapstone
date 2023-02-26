// g++ -std=c++17 run\ex8.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex8_collision

#include <iostream>
#include <random>
#include "CApp.h"

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {0, 0, 0, 255});

    // Debug Objects
    // app.addGameObject("obj1", Shape::RECTANGLE, {220, 150, 0, 255}, 100, 175, 300, 300);
    // app.addKeyEvent(KeyCode::W, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::Y_POSITION, -5);
    // app.addKeyEvent(KeyCode::A, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::X_POSITION, -5);
    // app.addKeyEvent(KeyCode::S, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::Y_POSITION,  5);
    // app.addKeyEvent(KeyCode::D, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::X_POSITION,  5);
    // app.addKeyEvent(KeyCode::Q, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::ANGLE, -1);
    // app.addKeyEvent(KeyCode::E, KeyPressType::HELD, GameAction::INCVAR, "obj1", ObjectAttribute::ANGLE,  1);

    // app.addGameObject("obj2", Shape::TRIANGLE, {0, 230, 220, 255}, 125, 80, 500, 500);
    // app.addKeyEvent(KeyCode::UPARROW,    KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::Y_POSITION, -5);
    // app.addKeyEvent(KeyCode::LEFTARROW,  KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::X_POSITION, -5);
    // app.addKeyEvent(KeyCode::DOWNARROW,  KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::Y_POSITION,  5);
    // app.addKeyEvent(KeyCode::RIGHTARROW, KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::X_POSITION,  5);
    // app.addKeyEvent(KeyCode::COMMA,  KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::ANGLE, -1);
    // app.addKeyEvent(KeyCode::PERIOD, KeyPressType::HELD, GameAction::INCVAR, "obj2", ObjectAttribute::ANGLE,  1);

    app.addGameObject( "ball1", Shape::CIRCLE, {rand()%256, rand()%256, rand()%256, 255}, rand()%25+55, rand()%25+35, rand()%900+100, rand()%600+100);
    app.setObjectValue("ball1", ObjectAttribute::X_VELOCITY, 7);
    app.setObjectValue("ball1", ObjectAttribute::Y_VELOCITY, 7);
    app.setObjectValue("ball1", ObjectAttribute::ANG_VELOCITY, 2);
    app.addObjectEvent("ball1", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("ball1", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);

    app.addGameObject( "ball2", Shape::CIRCLE, {rand()%256, rand()%256, rand()%256, 255}, rand()%25+55, rand()%25+35, rand()%900+100, rand()%600+100);
    app.setObjectValue("ball2", ObjectAttribute::X_VELOCITY, -7);
    app.setObjectValue("ball2", ObjectAttribute::Y_VELOCITY, 7);
    app.setObjectValue("ball2", ObjectAttribute::ANG_VELOCITY, 2);
    app.addObjectEvent("ball2", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("ball2", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);

    app.addGameObject( "ball3", Shape::CIRCLE, {rand()%256, rand()%256, rand()%256, 255}, rand()%25+55, rand()%25+35, rand()%900+100, rand()%600+100);
    app.setObjectValue("ball3", ObjectAttribute::X_VELOCITY, 7);
    app.setObjectValue("ball3", ObjectAttribute::Y_VELOCITY, -7);
    app.setObjectValue("ball3", ObjectAttribute::ANG_VELOCITY, 2);
    app.addObjectEvent("ball3", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("ball3", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);
    
    app.addGameObject( "ball4", Shape::CIRCLE, {rand()%256, rand()%256, rand()%256, 255}, rand()%25+55, rand()%25+35, rand()%900+100, rand()%600+100);
    app.setObjectValue("ball4", ObjectAttribute::X_VELOCITY, -7);
    app.setObjectValue("ball4", ObjectAttribute::Y_VELOCITY, -7);
    app.setObjectValue("ball4", ObjectAttribute::ANG_VELOCITY, 2);
    app.addObjectEvent("ball4", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("ball4", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);   

    app.addGameObject( "ball5", Shape::CIRCLE, {rand()%256, rand()%256, rand()%256, 255}, rand()%25+55, rand()%25+35, rand()%900+100, rand()%600+100);
    app.setObjectValue("ball5", ObjectAttribute::X_VELOCITY, 7);
    app.setObjectValue("ball5", ObjectAttribute::Y_VELOCITY, 7);
    app.setObjectValue("ball5", ObjectAttribute::ANG_VELOCITY, 2);
    app.addObjectEvent("ball5", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    app.addObjectEvent("ball5", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);
    
    app.addCollisionEvent("ball1", "ball2", GameAction::BOUNCE_X, "ball1");
    app.addCollisionEvent("ball1", "ball2", GameAction::BOUNCE_Y, "ball1");
    app.addCollisionEvent("ball1", "ball2", GameAction::BOUNCE_X, "ball2");
    app.addCollisionEvent("ball1", "ball2", GameAction::BOUNCE_Y, "ball2");

    app.addCollisionEvent("ball1", "ball3", GameAction::BOUNCE_X, "ball1");
    app.addCollisionEvent("ball1", "ball3", GameAction::BOUNCE_Y, "ball1");
    app.addCollisionEvent("ball1", "ball3", GameAction::BOUNCE_X, "ball3");
    app.addCollisionEvent("ball1", "ball3", GameAction::BOUNCE_Y, "ball3");

    app.addCollisionEvent("ball1", "ball4", GameAction::BOUNCE_X, "ball1");
    app.addCollisionEvent("ball1", "ball4", GameAction::BOUNCE_Y, "ball1");
    app.addCollisionEvent("ball1", "ball4", GameAction::BOUNCE_X, "ball4");
    app.addCollisionEvent("ball1", "ball4", GameAction::BOUNCE_Y, "ball4");

    app.addCollisionEvent("ball1", "ball5", GameAction::BOUNCE_X, "ball1");
    app.addCollisionEvent("ball1", "ball5", GameAction::BOUNCE_Y, "ball1");
    app.addCollisionEvent("ball1", "ball5", GameAction::BOUNCE_X, "ball5");
    app.addCollisionEvent("ball1", "ball5", GameAction::BOUNCE_Y, "ball5");

    app.addCollisionEvent("ball2", "ball3", GameAction::BOUNCE_X, "ball2");
    app.addCollisionEvent("ball2", "ball3", GameAction::BOUNCE_Y, "ball2");
    app.addCollisionEvent("ball2", "ball3", GameAction::BOUNCE_X, "ball3");
    app.addCollisionEvent("ball2", "ball3", GameAction::BOUNCE_Y, "ball3");

    app.addCollisionEvent("ball2", "ball4", GameAction::BOUNCE_X, "ball2");
    app.addCollisionEvent("ball2", "ball4", GameAction::BOUNCE_Y, "ball2");
    app.addCollisionEvent("ball2", "ball4", GameAction::BOUNCE_X, "ball4");
    app.addCollisionEvent("ball2", "ball4", GameAction::BOUNCE_Y, "ball4");

    app.addCollisionEvent("ball2", "ball5", GameAction::BOUNCE_X, "ball2");
    app.addCollisionEvent("ball2", "ball5", GameAction::BOUNCE_Y, "ball2");
    app.addCollisionEvent("ball2", "ball5", GameAction::BOUNCE_X, "ball5");
    app.addCollisionEvent("ball2", "ball5", GameAction::BOUNCE_Y, "ball5");

    app.addCollisionEvent("ball3", "ball4", GameAction::BOUNCE_X, "ball3");
    app.addCollisionEvent("ball3", "ball4", GameAction::BOUNCE_Y, "ball3");
    app.addCollisionEvent("ball3", "ball4", GameAction::BOUNCE_X, "ball4");
    app.addCollisionEvent("ball3", "ball4", GameAction::BOUNCE_Y, "ball4");

    app.addCollisionEvent("ball3", "ball5", GameAction::BOUNCE_X, "ball3");
    app.addCollisionEvent("ball3", "ball5", GameAction::BOUNCE_Y, "ball3");
    app.addCollisionEvent("ball3", "ball5", GameAction::BOUNCE_X, "ball5");
    app.addCollisionEvent("ball3", "ball5", GameAction::BOUNCE_Y, "ball5");

    app.addCollisionEvent("ball4", "ball5", GameAction::BOUNCE_X, "ball4");
    app.addCollisionEvent("ball4", "ball5", GameAction::BOUNCE_Y, "ball4");
    app.addCollisionEvent("ball4", "ball5", GameAction::BOUNCE_X, "ball5");
    app.addCollisionEvent("ball4", "ball5", GameAction::BOUNCE_Y, "ball5");


    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 8: Collision Detection");
}