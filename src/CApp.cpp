#include <ratio>
#include <chrono>
#include "CApp.h"


CApp::CApp(int window_width, int window_height, int r, int g, int b, int a)
         : Main_Window(nullptr), Renderer(nullptr), running(true),
           window_width(window_width), window_height(window_height),
           bg_color({r, g, b, a})
{ }

/////////////////////////////////////////////////////////////////////////////
/////// Game Objects
/////////////////////////////////////////////////////////////////////////////

bool CApp::addGameObject(const std::string& name, Shape shape, const Color& color,
                         int dim_x, int dim_y, int pos_x, int pos_y, double angle)
{
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        // Currently this just quietly fails
        // Could keep it like that, or maybe throw an error?
        if (obj_list[i].getName() == name) return false;
    }
    obj_list.push_back(GameObject(name, shape, color, dim_x, dim_y, pos_x, pos_y, angle));
    return true;
}
bool CApp::addGameObject(const GameObject& g_obj)
{
    obj_list.push_back(g_obj);
    return true;
}

GameObject& CApp::getGameObject(const std::string& name)
{
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        if (obj_list[i].getName() == name)
            return obj_list[i];
    }
    throw "Specified object not found";
}

bool CApp::setObjectValue(const std::string& obj_name, ObjectAttribute attribute, double var1, double var2)
{
    GameObject* GOptr = nullptr;
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        if (obj_list[i].getName() == obj_name)
        {
            GOptr = &obj_list[i];
            break;
        }
    }
    if (!GOptr) return false;

    switch(attribute)
    {
        case ObjectAttribute::SIZE:
            GOptr->dim_x = var1;
            GOptr->dim_y = var2;
            break;
        case ObjectAttribute::ANGLE:
            GOptr->angle = var1;
            break;
        case ObjectAttribute::POSITION:
            GOptr->pos_x = var1;
            GOptr->pos_y = var2;
            break;
        case ObjectAttribute::VELOCITY:
            GOptr->vel_x = var1;
            GOptr->vel_y = var2;
            break;
        case ObjectAttribute::ACCELERATION:
            GOptr->acc_x = var1;
            GOptr->acc_y = var2;
            break;
        case ObjectAttribute::ANG_VELOCITY:
            GOptr->vel_ang = var1;
            break;
        case ObjectAttribute::ANG_ACCELERATION:
            GOptr->acc_ang = var1;
            break;
        default:
            std::cerr << "DEFAULT TAKEN ON 'ObjectAttribute' SWITCH\n";
            exit(1);
    }
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
        GameObject* GOptr = &obj_list[i];
        if (GOptr->checkFlag(ObjectFlag::STATIC)) continue;
        
        GOptr->vel_x += GOptr->acc_x;
        GOptr->pos_x += GOptr->vel_x;

        GOptr->vel_y += GOptr->acc_y;
        GOptr->pos_y += GOptr->vel_y;

        GOptr->vel_ang += GOptr->acc_ang;
        GOptr->angle += GOptr->vel_ang;
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
        Color c = obj_list[curObj].color;
        SDL_SetRenderDrawColor(Renderer, c.r, c.g, c.b, c.a);
        switch(obj_list[curObj].getShape())
        {       
            case Shape::RECTANGLE:
            {
                int c_dim_x = obj_list[curObj].dim_x;
                int c_dim_y = obj_list[curObj].dim_y;

                for (int x = (c_dim_x / 2) * -1; x < c_dim_x / 2; x++)
                {
                    for (int y = (c_dim_y / 2) * -1; y < c_dim_y / 2; y++)
                    {
                        obj_list[curObj].drawPixel(Renderer, x, y);
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

                // Be careful of overflow here
                long hh = c_dim_y*c_dim_y;
                long ww = c_dim_x*c_dim_x;
                long hhww = hh*ww;
                int x0 = c_dim_x;
                int dx = 0;

                // Horizontal line - origin
                for (int x = -c_dim_x; x <= c_dim_x; ++x)
                    obj_list[curObj].drawPixel(Renderer, x, 0);

                // Draw semicircles above and below the origin
                for (int y = 1; y <= c_dim_y; ++y)
                {
                    // using 'dx', we limit the number of squares we have to test
                    // because as we approach the apex (away from the horizontal diameter),
                    // the amount by which each line shortens either increases or stays the same

                    // find the outer edge
                    int x1 = x0 - (dx - 1);
                    for ( ; x1 > 0; --x1)
                        if (x1*x1*hh + y*y*ww <= hhww) break;
                    
                    // update dx
                    dx = x0 - x1;
                    x0 = x1;

                    // draw within the discovered bounds
                    for (int x = -x0; x <= x0; ++x)
                    {
                        obj_list[curObj].drawPixel(Renderer, x, y);
                        obj_list[curObj].drawPixel(Renderer, x, -y);
                    }
                }
                break;
            }
            case Shape::TRIANGLE:
            {
                int c_dim_x = obj_list[curObj].dim_x;
                int c_dim_y = obj_list[curObj].dim_y;
                double aspectRatio = (double)c_dim_x / c_dim_y;
                double x_width = c_dim_x;

                for (int y = 0; y <= c_dim_y; ++y)
                {
                    for (int x = (x_width/2) * -1; x <= (x_width/2); ++x)
                    {
                        obj_list[curObj].drawPixel(Renderer, x, y);
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