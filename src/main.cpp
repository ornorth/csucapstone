//g++ -std=c++17 src\*.cpp -ISDL2\include -LSDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main

#include <iostream>
#include "CApp.h"


int main(int argc, char* argv[])
{
    CApp app(1080, 720, 73, 213, 52, 255);
    app.addGameObject("obj1");
    app.addGameObject("obj2", Shape::RECTANGLE, {165, 13, 2, 200}, 30, 70, 350, 400);
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