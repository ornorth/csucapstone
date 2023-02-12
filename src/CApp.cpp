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

// Helper function
int CApp::getGameObject(const std::string& name)
{
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        if (obj_list[i].getName() == name)
            return i;
    }
    return -1;
}

bool CApp::addGameObject(const std::string& name, Shape shape, const Color& color,
                         int dim_x, int dim_y, int pos_x, int pos_y, double angle)
{
    if (getGameObject(name) != -1) return false;
    obj_list.push_back(GameObject(name, shape, color, dim_x, dim_y, pos_x, pos_y, angle));
    return true;
}

bool CApp::setObjectValue(const std::string& obj_name, ObjectAttribute attribute, double var1, double var2)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(attribute)
    {
        case ObjectAttribute::SIZE:
            obj_list[idx].dim_x = var1;
            obj_list[idx].dim_y = var2;
            break;
        case ObjectAttribute::ANGLE:
            obj_list[idx].angle = var1;
            break;
        case ObjectAttribute::POSITION:
            obj_list[idx].pos_x = var1;
            obj_list[idx].pos_y = var2;
            break;
        case ObjectAttribute::VELOCITY:
            obj_list[idx].vel_x = var1;
            obj_list[idx].vel_y = var2;
            break;
        case ObjectAttribute::ACCELERATION:
            obj_list[idx].acc_x = var1;
            obj_list[idx].acc_y = var2;
            break;
        case ObjectAttribute::ANG_VELOCITY:
            obj_list[idx].vel_ang = var1;
            break;
        case ObjectAttribute::ANG_ACCELERATION:
            obj_list[idx].acc_ang = var1;
            break;
        default:
            std::cerr << "DEFAULT TAKEN ON 'ObjectAttribute' SWITCH\n";
            exit(1);
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////
///////  Events
/////////////////////////////////////////////////////////////////////////////
bool CApp::addEvent(const std::string& obj_name, GameEvent event, GameAction action, std::string name)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent(event, action, name);
    return true;
}
bool CApp::addEvent(const std::string& obj_name, GameEvent event, GameAction action, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent(event, action, value);
    return true;
}
bool CApp::addEvent(const std::string& obj_name, GameEvent event, GameAction action, std::string name, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent(event, action, name, value);
    return true;
}

void CApp::runGeneralEvents(GameObject* GOptr)
{
    for (auto& it: GOptr->event_list)
    {
        // Step 1: check if the event has occurred
        bool main_flag = false;
        bool flag2 = false;
        bool flag3 = false;
        switch(it.first)
        {
            case GameEvent::BORDERCOLLISION:
            {
                // GARBAGE VERSION: FIX LATER
                if (GOptr->pos_x + (GOptr->dim_x/2) >= window_width)
                {
                    main_flag = true;
                    flag2 = true;
                }
                if (GOptr->pos_x - (GOptr->dim_x/2) <= 0)
                {
                    main_flag = true;
                    flag2 = true;
                }
                if (GOptr->pos_y + (GOptr->dim_y/2) >= window_height)
                {
                    main_flag = true;
                    flag3 = true;
                }
                if (GOptr->pos_y - (GOptr->dim_y/2) <= 0)
                {
                    main_flag = true;
                    flag3 = true;
                }
                break;
            }
            default:
            {
                std::cerr << "DEFAULT TAKEN ON 'Shape' SWITCH\n";
                exit(1);
            }
        }

        // Step 2: take the actions listed
        for (unsigned idx = 0; main_flag && idx < it.second.size(); ++idx)
        {
            switch(it.second[idx].type)
            {
                case GameAction::BOUNCE:
                {
                    if (flag2) GOptr->vel_x *= -1;
                    if (flag3) GOptr->vel_y *= -1;

                    if (flag2)
                    {
                        GOptr->vel_x += it.second[idx].value;
                        GOptr->vel_y -= it.second[idx].value;
                    }
                    if (flag3)
                    {
                        GOptr->vel_x -= it.second[idx].value;
                        GOptr->vel_y += it.second[idx].value;
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
    }
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
        /*
        for key_event in key_event_list:
            if event.key.keysym.sym == key_event.key:
                take_action(key_event.game_object, key_event.action)
        */
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
        // Skip object if STATIC flag is set
        GameObject* GOptr = &obj_list[i];
        if (GOptr->checkFlag(ObjectFlag::STATIC)) continue;

        // Check event list
        runGeneralEvents(GOptr);
        
        // Update position and velocity
        GOptr->vel_x += GOptr->acc_x;
        GOptr->pos_x += GOptr->vel_x;

        GOptr->vel_y += GOptr->acc_y;
        GOptr->pos_y += GOptr->vel_y;

        GOptr->vel_ang += GOptr->acc_ang;
        GOptr->angle += GOptr->vel_ang;
        while (GOptr->angle >= 360) GOptr->angle -= 360;
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
                        obj_list[curObj].drawPixel(Renderer, x, y);
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