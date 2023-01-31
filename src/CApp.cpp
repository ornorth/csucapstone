#include <ctime>
#include <ratio>
#include <chrono>
#include "CApp.h"

int p_x = 100;
int p_y = 100;

CApp::CApp(int window_width, int window_height, int r, int g, int b, int a)
         : Main_Window(nullptr), Renderer(nullptr), running(true),
           window_width(window_width), window_height(window_height),
           bg_color({r, g, b, a})
{ }

/////////////////////////////////////////////////////////////////////////////
/////// Game Objects
/////////////////////////////////////////////////////////////////////////////

bool CApp::addGameObject(const std::string& obj_name, Shape obj_shape, const Color& obj_color, int dim_x, int dim_y, int pos_x, int pos_y)
{
    obj_list.push_back(GameObject(obj_name, obj_shape, obj_color, dim_x, dim_y, pos_x, pos_y));
    return true;
}
bool CApp::addGameObject(const GameObject& go)
{
    obj_list.push_back(go);
    return true;
}







/////////////////////////////////////////////////////////////////////////////
/////// Primary Loop
/////////////////////////////////////////////////////////////////////////////
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

    // Render Game Objects
    for (unsigned curObj = 0; curObj < obj_list.size(); curObj++)
    {
        Color c = obj_list[curObj].obj_color;
        SDL_SetRenderDrawColor(Renderer, c.r, c.b, c.g, c.a);
        switch(obj_list[curObj].obj_shape)
        {
            case Shape::RECTANGLE:
                for (int i = (obj_list[curObj].dim_x / 2) * -1; i < obj_list[curObj].dim_x / 2; i++)
                {
                    for (int j = (obj_list[curObj].dim_y / 2) * -1; j < obj_list[curObj].dim_y / 2; j++)
                    {
                        SDL_RenderDrawPoint(Renderer, obj_list[curObj].pos_x+i, obj_list[curObj].pos_y+j);
                    }
                }
                break;
            case Shape::CIRCLE:
                break;
            case Shape::TRIANGLE:
                break;
            default:
                std::cerr << "DEFAULT TAKEN ON 'Shape' SWITCH\n";
                exit(1);
        }
    }
/*
    // Render the Player
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    for (int y = 50 * -1; y < 50; y++)
    {
        for (int x = 50 * -1; x < 50; x++)
        {
            SDL_RenderDrawPoint(Renderer, p_x+x, p_y+y);
        }
    }
*/
    SDL_RenderPresent(Renderer);
}

void CApp::OnCleanup()
{
    SDL_Quit();
}