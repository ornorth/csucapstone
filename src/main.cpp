//g++ -std=c++17 src\*.cpp -ISDL2\include -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main

#include <iostream>
#include <random>
#include "CApp.h"

#define GRID_ACTIVE 0

int main(int argc, char* argv[])
{
    CApp app(1080, 720, {255, 255, 255, 255});

    // Complicated rectangle
    app.addGameObject("rct1", Shape::TRIANGLE, {0, 13, 200, 255}, 100, 100, rand()%800 + 100, rand()%600 + 100, 100);
    // app.setObjectValue("rct1", ObjectAttribute::X_VELOCITY, rand()%20 + 1);
    // app.setObjectValue("rct1", ObjectAttribute::Y_VELOCITY, rand()%20 + 1);

    // Object Events
    // app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::BOUNCE_X);
    // app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, 0.5);
    // app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::INCVAR, ObjectAttribute::HEIGHT, 20);
    // app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::X_VELOCITY, 1.05);
    // app.addObjectEvent("rct1", GameEvent::X_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::Y_VELOCITY, 1.05);

    // app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::BOUNCE_Y);
    // app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, -0.5);
    // app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::INCVAR, ObjectAttribute::WIDTH, 20);
    // app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::X_VELOCITY, 0.95);
    // app.addObjectEvent("rct1", GameEvent::Y_BORDERCOLLISION, GameAction::SCALEVAR, ObjectAttribute::Y_VELOCITY, 0.95);

    // Keyboard Events
    app.addKeyEvent("rct1", KeyCode::A, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::X_POSITION, -15);
    app.addKeyEvent("rct1", KeyCode::D, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::X_POSITION, 15);
    app.addKeyEvent("rct1", KeyCode::W, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::Y_POSITION, -15);
    app.addKeyEvent("rct1", KeyCode::S, KeyPressType::HELD, GameAction::INCVAR, ObjectAttribute::Y_POSITION, 15);

    app.addKeyEvent("rct1", KeyCode::SPACE, KeyPressType::DOWN, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, 1);
    app.addKeyEvent("rct1", KeyCode::SPACE, KeyPressType::UP, GameAction::SETVAR, ObjectAttribute::ANG_ACCELERATION, -1);

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
    return app.Execute("Dynamic Window Name Here");
}


/*
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool isRunning = true;
    bool colorSwap = false;
    int r = 255, g = 0, b = 0;
    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    colorSwap = true;
                    if (r)
                    {
                        r = 0;
                        g = 255;
                    }
                    else if (g)
                    {
                        g = 0;
                        b = 255;
                    }
                    else
                    {
                        b = 0;
                        r = 255;
                    }
                }
            }
        }

        if (colorSwap)
        {
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/