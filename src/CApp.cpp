#include <ctime>
#include <ratio>
#include <chrono>
//#include <cmath>
#include "CApp.h"
#include "SDLHelper.h"


CApp::CApp(int window_width, int window_height, int r, int g, int b, int a)
         : Main_Window(nullptr), Renderer(nullptr), running(true),
           window_width(window_width), window_height(window_height),
           bg_color({r, g, b, a})
{ }

/////////////////////////////////////////////////////////////////////////////
/////// Game Objects
/////////////////////////////////////////////////////////////////////////////

bool CApp::addGameObject(const std::string& obj_name, Shape obj_shape, const Color& obj_color, int dim_x, int dim_y, int pos_x, int pos_y, int angle)
{
    obj_list.push_back(GameObject(obj_name, obj_shape, obj_color, dim_x, dim_y, pos_x, pos_y, angle));
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
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        if (obj_list[i].obj_name[0] != 'l')
            obj_list[i].angle++;
    }
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
        SDL_SetRenderDrawColor(Renderer, c.r, c.g, c.b, c.a);
        switch(obj_list[curObj].obj_shape)
        {       
            case Shape::RECTANGLE:
            {
                int c_dim_x = obj_list[curObj].dim_x;
                int c_dim_y = obj_list[curObj].dim_y;
                int c_pos_x = obj_list[curObj].pos_x;
                int c_pos_y = obj_list[curObj].pos_y;
                int angle = obj_list[curObj].angle;
                for (int i = (c_dim_x / 2) * -1; i < c_dim_x / 2; i++)
                {
                    for (int j = (c_dim_y / 2) * -1; j < c_dim_y / 2; j++)
                    {
                        drawPixel(Renderer, c_pos_x, c_pos_y, i, j, c_dim_x/2, c_dim_y/2, angle);
                    }
                }
                break;
            }
            case Shape::CIRCLE:
            {
                // Method for drawing ellipses pulled from here:
                //https://stackoverflow.com/questions/10322341/simple-algorithm-for-drawing-filled-ellipse-in-c-c
                int c_dim_x = obj_list[curObj].dim_x / 2;
                int c_dim_y = obj_list[curObj].dim_y / 2;
                int c_pos_x = obj_list[curObj].pos_x;
                int c_pos_y = obj_list[curObj].pos_y;
                int angle = obj_list[curObj].angle;

                // Be careful of overflow here
                long hh = c_dim_y*c_dim_y;
                long ww = c_dim_x*c_dim_x;
                long hhww = hh*ww;
                int x0 = c_dim_x;
                int dx = 0;

                // Horizontal line - origin
                for (int x = -c_dim_x; x <= c_dim_x; ++x)
                {
                    //SDL_RenderDrawPoint(Renderer, c_pos_x+x, c_pos_y);
                    drawPixel(Renderer, c_pos_x, c_pos_y, x, 0, c_dim_x/2, c_dim_y/2, angle);
                }

                // Draw semicircles above and below the origin
                for (int y = 1; y <= c_dim_y; ++y)
                {
                    // using 'dx', we limit the number of squares we have to test
                    // because as we approach the apex (away from the horizontal diameter),
                    // the amount by which each line shortens either increases or stays the same

                    // find the outer edge
                    int x1 = x0 - (dx - 1);
                    for ( ; x1 > 0; --x1)
                    {
                        if (x1*x1*hh + y*y*ww <= hhww) break;
                    }
                    // update dx
                    dx = x0 - x1;
                    x0 = x1;

                    // draw within the discovered bounds
                    for (int x = -x0; x <= x0; ++x)
                    {
                        drawPixel(Renderer, c_pos_x, c_pos_y, x, y, c_dim_x/2, c_dim_y/2, angle);
                        drawPixel(Renderer, c_pos_x, c_pos_y, x, -y, c_dim_x/2, c_dim_y/2, angle);
                        //SDL_RenderDrawPoint(Renderer, c_pos_x+x, c_pos_y+y);
                        //SDL_RenderDrawPoint(Renderer, c_pos_x+x, c_pos_y-y);
                    }
                }
                break;
            }
            case Shape::TRIANGLE:
            {
                int c_dim_x = obj_list[curObj].dim_x;
                int c_dim_y = obj_list[curObj].dim_y;
                int c_pos_x = obj_list[curObj].pos_x;
                int c_pos_y = obj_list[curObj].pos_y;
                int angle = obj_list[curObj].angle;

                double aspectRatio = (double)c_dim_x / c_dim_y;

                double x_width = c_dim_x;

                for (int y = 0; y <= c_dim_y; ++y)
                {
                    for (int x = (x_width/2) * -1; x <= (x_width/2); ++x)
                    {
                        drawPixel(Renderer, c_pos_x, c_pos_y, x, y, c_dim_x/2, c_dim_y/2, angle);
                        //SDL_RenderDrawPoint(Renderer, (int)c_pos_x+x, (int)c_pos_y-y);
                    }
                    x_width -= aspectRatio;
                }
                break;
            }
            default:
            {
                std::cerr << "DEFAULT TAKEN ON 'Shape' SWITCH\n";
                exit(1);
            }
        }
    }
    SDL_RenderPresent(Renderer);
}

void CApp::OnCleanup()
{
    SDL_Quit();
}