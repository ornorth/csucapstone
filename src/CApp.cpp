#include <ratio>
#include <chrono>
#include <random>
#include "CApp.h"


CApp::CApp(int window_width, int window_height, const Color& color)
         : Main_Window(nullptr), Renderer(nullptr), running(true),
           window_width(window_width), window_height(window_height),
           bg_color(color)
{
    for (int i = 0; i < KeyCode::MAX_KEYCODE; ++i)
    {
        keyStates[i] = false;
    }
    srand(time(NULL));
}

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

double* CApp::getObjectAttribute(GameObject* GOptr, ObjectAttribute attribute)
{    
    switch(attribute)
    {
        case ObjectAttribute::WIDTH:
            return &GOptr->dim_x;
        case ObjectAttribute::HEIGHT:
            return &GOptr->dim_y;
        case ObjectAttribute::ANGLE:
            return &GOptr->angle;
        case ObjectAttribute::X_POSITION:
            return &GOptr->pos_x;
        case ObjectAttribute::Y_POSITION:
            return &GOptr->pos_y;
        case ObjectAttribute::X_VELOCITY:
            return &GOptr->vel_x;
        case ObjectAttribute::Y_VELOCITY:
            return &GOptr->vel_y;
        case ObjectAttribute::X_ACCELERATION:
            return &GOptr->acc_x;
        case ObjectAttribute::Y_ACCELERATION:
            return &GOptr->acc_y;
        case ObjectAttribute::ANG_VELOCITY:
            return &GOptr->vel_ang;
        case ObjectAttribute::ANG_ACCELERATION:
            return &GOptr->acc_ang;
        case ObjectAttribute::USER_DOUBLE_1:
            return &GOptr->user_double1;
        case ObjectAttribute::USER_DOUBLE_2:
            return &GOptr->user_double2;
        case ObjectAttribute::USER_DOUBLE_3:
            return &GOptr->user_double3;
        default:
            std::cerr << "DEFAULT TAKEN ON 'ObjectAttribute' SWITCH\n";
            exit(1);
    }
}

bool CApp::addGameObject(const std::string& name, Shape shape, const Color& color,
                         int dim_x, int dim_y, int pos_x, int pos_y, double angle)
{
    if (getGameObject(name) != -1) return false;
    obj_list.push_back(GameObject(name, shape, color, dim_x, dim_y, pos_x, pos_y, angle));
    return true;
}

bool CApp::setObjectValue(const std::string& obj_name, ObjectAttribute attribute, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;
    
    *(getObjectAttribute(&obj_list[idx], attribute)) = value;

    return true;
}

/////////////////////////////////////////////////////////////////////////////
///////  Events
/////////////////////////////////////////////////////////////////////////////
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event}, action, "NULL", 0.0);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& name)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event}, action, name, 0.0);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event}, action, "NULL", value);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& name, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event}, action, name, value);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute att, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event}, action, att, value);
    return true;
}

bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event, effector_att, effector_value}, action, "NULL", 0.0);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& name)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event, effector_att, effector_value}, action, name, 0.0);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event, effector_att, effector_value}, action, "NULL", value);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& name, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event, effector_att, effector_value}, action, name, value);
    return true;
}
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute att, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    obj_list[idx].addEvent({event, effector_att, effector_value}, action, att, value);
    return true;
}

bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action)
{
    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, "NULL", "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, nullptr, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, nullptr, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, obj_name, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, obj_name, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, obj_name, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, const std::string& name)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, obj_name, name, 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, obj_name, name, 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, obj_name, name, 0.0, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, obj_name, "NULL", value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, obj_name, "NULL", value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, obj_name, "NULL", value, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, const std::string& name, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, obj_name, name, value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, obj_name, name, value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, obj_name, name, value, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute att, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, obj_name, "NULL", value, att});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, obj_name, "NULL", value, att});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, obj_name, "NULL", value, att});
            break;
    }
    return true;
}

bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    std::pair<std::string, std::string> colliders = std::make_pair(obj_1, obj_2);
    collision_events[colliders].push_back({action, "NULL", "NULL", 0.0});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    std::pair<std::string, std::string> colliders = std::make_pair(obj_1, obj_2);
    collision_events[colliders].push_back({action, obj_name, "NULL", 0.0});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, const std::string& name)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    std::pair<std::string, std::string> colliders = std::make_pair(obj_1, obj_2);
    collision_events[colliders].push_back({action, obj_name, name, 0.0});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, double value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    std::pair<std::string, std::string> colliders = std::make_pair(obj_1, obj_2);
    collision_events[colliders].push_back({action, obj_name, "NULL", value});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, const std::string& name, double value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    std::pair<std::string, std::string> colliders = std::make_pair(obj_1, obj_2);
    collision_events[colliders].push_back({action, obj_name, name, value});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute att, double value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    std::pair<std::string, std::string> colliders = std::make_pair(obj_1, obj_2);
    collision_events[colliders].push_back({action, obj_name, "NULL", value, att});
    return true;
}

void CApp::checkObjectEvents(GameObject* GOptr)
{
    for (auto& it: GOptr->event_list)
    {
        bool flag = false;
        switch(it.first.event)
        {
            case GameEvent::X_BORDERCOLLISION:
            {
                // Check for collision on this frame
                // GARBAGE VERSION: FIX LATER
                if (GOptr->pos_x + (GOptr->dim_x/2) >= window_width)
                    flag = true;
                if (GOptr->pos_x - (GOptr->dim_x/2) <= 0)
                    flag = true;

                // If we were colliding last frame, don't do it again this frame
                bool prevFlag = GOptr->checkFlag(ObjectFlag::X_BORDER_COLLIDED);
                if (prevFlag && flag)
                    flag = false;
                else if (prevFlag)
                    GOptr->clearFlag(ObjectFlag::X_BORDER_COLLIDED);
                else if (flag)
                    GOptr->setFlag(ObjectFlag::X_BORDER_COLLIDED);
                break;
            }
            case GameEvent::Y_BORDERCOLLISION:
            {
                // Check for collision on this frame
                // GARBAGE VERSION: FIX LATER
                if (GOptr->pos_y + (GOptr->dim_y/2) >= window_height)
                    flag = true;
                if (GOptr->pos_y - (GOptr->dim_y/2) <= 0)
                    flag = true;

                // If we were colliding last frame, don't do it again this frame
                bool prevFlag = GOptr->checkFlag(ObjectFlag::Y_BORDER_COLLIDED);
                if (prevFlag && flag)
                    flag = false;
                else if (prevFlag)
                    GOptr->clearFlag(ObjectFlag::Y_BORDER_COLLIDED);
                else if (flag)
                    GOptr->setFlag(ObjectFlag::Y_BORDER_COLLIDED);
                break;
            }
            case GameEvent::OBJ_VAR_EQUALS:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, it.first.attribute);
                flag = (*att_ptr) == it.first.value;
                break;
            }
            case GameEvent::OBJ_VAR_IS_LESS:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, it.first.attribute);
                flag = (*att_ptr) < it.first.value;
                break;
            }
            case GameEvent::OBJ_VAR_IS_GREATER:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, it.first.attribute);
                flag = (*att_ptr) > it.first.value;
                break;
            }
            default:
            {
                std::cerr << "DEFAULT TAKEN ON 'Shape' SWITCH\n";
                exit(1);
            }
        }

        if (flag)
            runObjectEvent(GOptr, it.second);
    }
}
void CApp::runObjectEvent(GameObject* GOptr, std::vector<ActionList>& events)
{
    for (unsigned idx = 0; idx < events.size(); ++idx)
    {
        switch(events[idx].type)
        {
            case GameAction::QUIT:
            {
                running = false;
                break;
            }
            case GameAction::BOUNCE_X:
            {
                // Swap the velocity
                GOptr->vel_x *= -1;
                break;
            }
            case GameAction::BOUNCE_Y:
            {
                // Swap the velocity
                GOptr->vel_y *= -1;
                break;
            }
            case GameAction::SETVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, events[idx].attribute);
                *att_ptr = events[idx].value;
                break;
            }
            case GameAction::INCVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, events[idx].attribute);
                *att_ptr += events[idx].value;
                break;
            }
            case GameAction::SCALEVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, events[idx].attribute);
                *att_ptr *= events[idx].value;
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

void CApp::runKeyEvents(std::vector<KeyActionList>& events)
{
    // Step 2: take the actions listed
    for (unsigned idx = 0; idx < events.size(); ++idx)
    {
        KeyActionList* action = &events[idx];

        // Get pointer to object if relevant
        int obj_idx = getGameObject(events[idx].object_name);
        GameObject* GOptr = nullptr;
        if (obj_idx != -1) GOptr = &obj_list[obj_idx];

        switch(action->type)
        {
            case GameAction::QUIT:
            {
                running = false;
                break;
            }
            case GameAction::BOUNCE_X:
            {
                // Swap the velocity
                GOptr->vel_x *= -1;
                break;
            }
            case GameAction::BOUNCE_Y:
            {
                // Swap the velocity
                GOptr->vel_y *= -1;
                break;
            }
            case GameAction::SETVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, events[idx].attribute);
                *att_ptr = events[idx].value;
                break;
            }
            case GameAction::INCVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, events[idx].attribute);
                *att_ptr += events[idx].value;
                break;
            }
            case GameAction::SCALEVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(GOptr, events[idx].attribute);
                *att_ptr *= events[idx].value;
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

// Initial pass at a working state, still has numerous problems
bool CApp::collisionOccurred(const std::pair<std::string, std::string>& colliders)
{
    //std::cout << "-------------" << std::endl;
    GameObject* obj1 = &obj_list[getGameObject(colliders.first)];
    double Xcorners1[4], Ycorners1[4];
    obj1->getCorners(Xcorners1, Ycorners1);
    
    GameObject* obj2 = &obj_list[getGameObject(colliders.second)];
    double Xcorners2[4], Ycorners2[4];
    obj2->getCorners(Xcorners2, Ycorners2);

    //bool flag = false;
    // Corner of obj1 is touching obj2
    for (int i = 0; i < 4; ++i)
    {
        bool Xflag1 = false,
             Yflag1 = false,
             Xflag2 = false,
             Yflag2 = false;
        for (int j = 0; j < 4; ++j)
        {
            int jPair = (j < 3 ? j+1 : 0);
            // std::cout << "[" << Xcorners1[i]     << "," << Ycorners1[i]     << "] -> ["
            //                  << Xcorners2[j]     << "," << Ycorners2[j]     << "] - ["
            //                  << Xcorners2[jPair] << "," << Ycorners2[jPair] << "] : ";
            Xflag1 = Xflag1 || (Xcorners1[i] < Xcorners2[j] && Xcorners1[i] > Xcorners2[jPair])
                            || (Xcorners1[i] > Xcorners2[j] && Xcorners1[i] < Xcorners2[jPair]);
            Yflag1 = Yflag1 || (Ycorners1[i] < Ycorners2[j] && Ycorners1[i] > Ycorners2[jPair])
                            || (Ycorners1[i] > Ycorners2[j] && Ycorners1[i] < Ycorners2[jPair]);
            // if (Xflag1) std::cout << "X";
            // if (Yflag1) std::cout << "Y";
            // //if (Xflag1 || Yflag1) std::cout << " : ";
            // std::cout << std::endl;

            // std::cout << "[" << Xcorners2[i]     << "," << Ycorners2[i]     << "] -> ["
            //                  << Xcorners1[j]     << "," << Ycorners1[j]     << "] - ["
            //                  << Xcorners1[jPair] << "," << Ycorners1[jPair] << "] : ";
            Xflag2 = Xflag2 || (Xcorners2[i] < Xcorners1[j] && Xcorners2[i] > Xcorners1[jPair])
                            || (Xcorners2[i] > Xcorners1[j] && Xcorners2[i] < Xcorners1[jPair]);
            Yflag2 = Yflag2 || (Ycorners2[i] < Ycorners1[j] && Ycorners2[i] > Ycorners1[jPair])
                            || (Ycorners2[i] > Ycorners1[j] && Ycorners2[i] < Ycorners1[jPair]);
            // if (Xflag2) std::cout << "X";
            // if (Yflag2) std::cout << "Y";
            // std::cout << std::endl;
            // if (Xflag1 || Yflag1 || Xflag2 || Yflag2) std::cout << std::endl;

            if ((Xflag1 && Yflag1) || (Xflag2 && Yflag2))
            {
                //std::cout << "XY!" << std::endl;
                return true;//flag = true;
            }
        }
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////
/////// Primary Loop
/////////////////////////////////////////////////////////////////////////////
int CApp::Execute(const std::string& window_name)
{
    if (OnInit(window_name) == false)
        return -1;
    
    //SDL_Event event;
    std::chrono::steady_clock::time_point t1, t2;
    while (running)
    {
        t1 = std::chrono::steady_clock::now();

        OnEvent();
        OnLoop();
        OnRender();

        for (t2 = std::chrono::steady_clock::now();
             std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1).count() < (1.0/30.0);
             t2 = std::chrono::steady_clock::now())
        {}
        if (false)
            std::cout << "FPS: " << 1.0 / std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1).count() << std::endl;
    }
    OnCleanup();
    return 0;
}

bool CApp::OnInit(const std::string& window_name)
{
    // General SDL Initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    
    // Create the main window
    if ((Main_Window = SDL_CreateWindow(window_name.c_str(),
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        window_width, window_height, 0)) == nullptr)
    { return false; }
    
    // Primary renderer
    Renderer = SDL_CreateRenderer(Main_Window, -1, 0);
    
    return true;
}

void CApp::OnEvent()
{
    SDL_PumpEvents();
    const Uint8* boardState = SDL_GetKeyboardState(nullptr);
    for (int idx = 0; idx < KeyCode::MAX_KEYCODE; ++idx)
    {
        if (boardState[idx] && !keyStates[idx])
        {
            keyStates[idx] = 1;
            runKeyEvents(keydown_events[(KeyCode)idx]);
        }
        else if (!boardState[idx] && keyStates[idx])
        {
            keyStates[idx] = 0;
            runKeyEvents(keyup_events[(KeyCode)idx]);
        }
    }
}

void CApp::OnLoop()
{
    for (auto it : collision_events)
    {
        if (collisionOccurred(it.first))
            runKeyEvents(it.second);
    }
    // Check held key event list
    for (int i = 0; i < KeyCode::MAX_KEYCODE; ++i)
    {
        if (keyStates[i])
        {
            runKeyEvents(keyheld_events[(KeyCode)i]);
        }
    }
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        // Skip object if STATIC flag is set
        GameObject* GOptr = &obj_list[i];
        if (GOptr->checkFlag(ObjectFlag::STATIC)) continue;

        // Check event list
        checkObjectEvents(GOptr);

        // Update position and velocity
        GOptr->vel_x += GOptr->acc_x;
        GOptr->pos_x += GOptr->vel_x;

        GOptr->vel_y += GOptr->acc_y;
        GOptr->pos_y += GOptr->vel_y;

        GOptr->vel_ang += GOptr->acc_ang;
        //if (GOptr->vel_ang >= 360) GOptr->vel_ang -= 360;
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

                for (int y = (c_dim_y/2); y >= (c_dim_y/2) * -1; --y)
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