#include <ctime>
#include <ratio>
#include <chrono>
#include "CApp.h"

CApp::CApp(int window_width, int window_height, int r, int g, int b, int a)
         : Main_Window(nullptr), Renderer(nullptr), running(true),
           window_width(window_width), window_height(window_height),
           bg_color({r, g, b, a})
{ }

int CApp::Execute()
{
    if (OnInit() == false)
        return -1;
    
    SDL_Event event;
    std::chrono::steady_clock::time_point t1, t2;
    while (running)
    {
        t1 = std::chrono::steady_clock::now();

        while (SDL_PollEvent(&event))
        {
            OnEvent(event);
        }
        OnLoop();
        OnRender();

        //t2 = std::chrono::steady_clock::now();
        for (t2 = std::chrono::steady_clock::now();
             std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1).count() < (1.0/30.0);
             t2 = std::chrono::steady_clock::now())
        {}
    }
    OnCleanup();
    return 0;
}

bool CApp::OnInit()
{
    // General SDL Initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
    // Create the main window
    if ((Main_Window = SDL_CreateWindow("Super Cool and Awesome Window",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        window_width, window_height, 0)) == nullptr)
    { return false; }
    
    // Primary renderer
    Renderer = SDL_CreateRenderer(Main_Window, -1, 0);
    
    return true;
}

void CApp::OnEvent(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            running = false;
        }
        /*
        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            if (p.x >= 30) p.x -= 15;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            if (p.x <= 610) p.x += 15;
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
            if (p.y >= 30) p.y -= 15;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            if (p.y <= 450) p.y += 15;
        }
        */
    }
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
    SDL_RenderClear(Renderer);
    SDL_SetRenderDrawColor(Renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(Renderer);

    /*
    // Render the Player
    SDL_SetRenderDrawColor(Renderer, p.color.r, p.color.g, p.color.b, p.color.a);
    for (int y = (p.length/2) * -1; y < (p.length/2); y++)
    {
        for (int x = (p.length/2) * -1; x < (p.length/2); x++)
        {
            SDL_RenderDrawPoint(Renderer, p.x+x, p.y+y);
        }
    }
    */
    SDL_RenderPresent(Renderer);
}

void CApp::OnCleanup()
{
    SDL_Quit();
}