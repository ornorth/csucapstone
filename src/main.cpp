//g++ -std=c++17 src\*.cpp -ISDL2\include -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main

#include <iostream>
#include "CApp.h"

#define GRID_ACTIVE 0

int main(int argc, char* argv[])
{
    CApp app(1080, 720, 73, 213, 52, 255);
    app.addGameObject("rct1", Shape::RECTANGLE, {0, 13, 200, 255}, 100, 100, 200, 130, 0);
    app.setObjectValue("rct1", ObjectAttribute::VELOCITY, 11, 8);
    app.addEvent("rct1", GameEvent::BORDERCOLLISION, GameAction::BOUNCE, 1);

    app.addGameObject("cir1", Shape::CIRCLE, {255, 0, 0, 5}, 60, 100, 700, 500, 90);
    app.setObjectValue("cir1", ObjectAttribute::VELOCITY, 7, -5);
    app.addEvent("cir1", GameEvent::BORDERCOLLISION, GameAction::BOUNCE, 2);

    app.addGameObject("tri1", Shape::TRIANGLE, {255, 0, 0, 255}, 90, 150, 300, 500, 180);
    app.setObjectValue("tri1", ObjectAttribute::VELOCITY, 14, -1);
    app.addEvent("tri1", GameEvent::BORDERCOLLISION, GameAction::BOUNCE, -3);
/*
    // Spinny bois
    app.addGameObject("rct1", Shape::RECTANGLE, {0, 13, 200, 255}, 100, 100, 200, 130, 70);
    app.setObjectValue("rct1", ObjectAttribute::ANG_VELOCITY, 2);
    
    app.addGameObject("rct2", Shape::RECTANGLE, {0, 13, 200, 255}, 50, 50, 200, 350, 30);
    app.setObjectValue("rct2", ObjectAttribute::ANG_VELOCITY, -2);

    app.addGameObject("cir1", Shape::CIRCLE, {255, 0, 0, 5}, 60, 100, 700, 500, 90);
    app.setObjectValue("cir1", ObjectAttribute::ANG_VELOCITY, 2);

    app.addGameObject("cir2", Shape::CIRCLE, {0, 0, 255, 75}, 50, 90, 500, 300, 125);
    app.setObjectValue("cir2", ObjectAttribute::ANG_VELOCITY, -2);

    app.addGameObject("tri1", Shape::TRIANGLE, {255, 0, 0, 255}, 90, 150, 300, 500, 180);
    app.setObjectValue("tri1", ObjectAttribute::ANG_VELOCITY, 2);

    app.addGameObject("tri2", Shape::TRIANGLE, {0, 0, 255, 255}, 170, 92, 800, 300, 270);
    app.setObjectValue("tri2", ObjectAttribute::ANG_VELOCITY, -2);
*/

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


    return app.Execute();
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