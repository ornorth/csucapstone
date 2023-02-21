// g++ -std=c++17 run\ex2.cpp src\*.cpp -ISDL2\include -Isrc\ -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o run\ex2_rotate_objects

#include <iostream>
#include "CApp.h"

#define GRID_ACTIVE 1

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    app.addGameObject( "rct1", Shape::RECTANGLE, {255, 0, 0,   255}, 100, 100, 200, 150, 253);
    app.setObjectValue("rct1", ObjectAttribute::ANG_VELOCITY, 4);
    
    app.addGameObject( "rct2", Shape::RECTANGLE, {0,   0, 255, 255}, 200, 100, 450, 150, 14);
    app.setObjectValue("rct2", ObjectAttribute::ANG_VELOCITY, 4);
    
    app.addGameObject( "tri1", Shape::TRIANGLE,  {255, 0, 0,   255}, 150, 100, 300, 350, 7);
    app.setObjectValue("tri1", ObjectAttribute::ANG_VELOCITY, 4);
    
    app.addGameObject( "tri2", Shape::TRIANGLE,  {0,   0, 255, 255}, 100, 200, 550, 350, 170);
    app.setObjectValue("tri2", ObjectAttribute::ANG_VELOCITY, 4);
    
    app.addGameObject( "cir1", Shape::CIRCLE,    {255, 0, 0,   255}, 100, 100, 400, 550, 355);
    app.setObjectValue("cir1", ObjectAttribute::ANG_VELOCITY, 4);
    
    app.addGameObject( "cir2", Shape::CIRCLE,    {0,   0, 255, 255}, 175, 100, 650, 550, 125);
    app.setObjectValue("cir2", ObjectAttribute::ANG_VELOCITY, 4);
    
    // GRID for testing purposes
    if (GRID_ACTIVE)
    {
        // Vertical lines
        app.addGameObject("long1",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 50,   360);
        app.addGameObject("long2",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 100,  360);
        app.addGameObject("long3",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 150,  360);
        app.addGameObject("long4",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 200,  360);
        app.addGameObject("long5",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 250,  360);
        app.addGameObject("long6",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 300,  360);
        app.addGameObject("long7",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 350,  360);
        app.addGameObject("long8",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 400,  360);
        app.addGameObject("long9",  Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 450,  360);
        app.addGameObject("long10", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 500,  360);
        app.addGameObject("long11", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 550,  360);
        app.addGameObject("long12", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 600,  360);
        app.addGameObject("long13", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 650,  360);
        app.addGameObject("long14", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 700,  360);
        app.addGameObject("long15", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 750,  360);
        app.addGameObject("long16", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 800,  360);
        app.addGameObject("long17", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 850,  360);
        app.addGameObject("long18", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 900,  360);
        app.addGameObject("long19", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 950,  360);
        app.addGameObject("long20", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 1000, 360);
        app.addGameObject("long21", Shape::RECTANGLE, {0, 0, 0, 255}, 3, 800, 1050, 360);

        // Horizontal lines
        app.addGameObject("lat1",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 50);
        app.addGameObject("lat2",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 100);
        app.addGameObject("lat3",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 150);
        app.addGameObject("lat4",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 200);
        app.addGameObject("lat5",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 250);
        app.addGameObject("lat6",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 300);
        app.addGameObject("lat7",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 350);
        app.addGameObject("lat8",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 400);
        app.addGameObject("lat9",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 450);
        app.addGameObject("lat10",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 500);
        app.addGameObject("lat11",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 550);
        app.addGameObject("lat12",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 600);
        app.addGameObject("lat13",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 650);
        app.addGameObject("lat14",  Shape::RECTANGLE, {0, 0, 0, 255}, 1100, 3, 540, 700);
    }


    app.addKeyEvent(KeyCode::ESCAPE, KeyPressType::DOWN, GameAction::QUIT);
    return app.Execute("Milestone 2: Rotating Objects");
}