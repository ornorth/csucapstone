#include <ratio>
#include <chrono>
#include <random>
#include "CApp.h"


CApp::CApp(int window_width, int window_height, const Color& color)
         : Main_Window(nullptr), Renderer(nullptr), running(true),
           window_width(window_width), window_height(window_height),
           bg_color(color)
{
    for (int i = 0; i < KeyCode::SPACE+1; ++i)
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
            keydown_events[key].push_back({action, nullptr, "NULL", 0.0, ObjectAttribute::WIDTH});
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
bool CApp::addKeyEvent(const std::string& obj_name, KeyCode key, KeyPressType type, GameAction action)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;
    GameObject* GOptr = &obj_list[idx];

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, GOptr, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, GOptr, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, GOptr, "NULL", 0.0, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(const std::string& obj_name, KeyCode key, KeyPressType type, GameAction action, const std::string& name)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;
    GameObject* GOptr = &obj_list[idx];

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, GOptr, name, 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, GOptr, name, 0.0, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, GOptr, name, 0.0, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(const std::string& obj_name, KeyCode key, KeyPressType type, GameAction action, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;
    GameObject* GOptr = &obj_list[idx];

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, GOptr, "NULL", value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, GOptr, "NULL", value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, GOptr, "NULL", value, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(const std::string& obj_name, KeyCode key, KeyPressType type, GameAction action, const std::string& name, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;
    GameObject* GOptr = &obj_list[idx];

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, GOptr, name, value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, GOptr, name, value, ObjectAttribute::WIDTH});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, GOptr, name, value, ObjectAttribute::WIDTH});
            break;
    }
    return true;
}
bool CApp::addKeyEvent(const std::string& obj_name, KeyCode key, KeyPressType type, GameAction action, ObjectAttribute att, double value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;
    GameObject* GOptr = &obj_list[idx];

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, GOptr, "NULL", value, att});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, GOptr, "NULL", value, att});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, GOptr, "NULL", value, att});
            break;
    }
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

        if (flag) runObjectEvent(GOptr, it.second);
    }
}
void CApp::runObjectEvent(GameObject* GOptr, std::vector<ActionList>& events)
{
    std::cout << "------" << std::endl;
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
                std::cout << events[idx].attribute << ": " << *att_ptr << "->" << events[idx].value << std::endl;
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
void CApp::runKeyEvent(std::vector<KeyActionList>& events)
{
    // Step 2: take the actions listed
    for (unsigned idx = 0; idx < events.size(); ++idx)
    {
        KeyActionList* action = &events[idx];
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
                action->object->vel_x *= -1;
                break;
            }
            case GameAction::BOUNCE_Y:
            {
                // Swap the velocity
                action->object->vel_y *= -1;
                break;
            }
            case GameAction::SETVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(action->object, events[idx].attribute);
                *att_ptr = events[idx].value;
                break;
            }
            case GameAction::INCVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(action->object, events[idx].attribute);
                *att_ptr += events[idx].value;
                break;
            }
            case GameAction::SCALEVAR:
            {
                double* att_ptr = (double*)getObjectAttribute(action->object, events[idx].attribute);
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

/////////////////////////////////////////////////////////////////////////////
/////// Primary Loop
/////////////////////////////////////////////////////////////////////////////
int CApp::Execute(const std::string& window_name)
{
    if (OnInit(window_name) == false)
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

void CApp::OnEvent(SDL_Event& event)
{
    // Handle press & release events
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_a:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::A] = 1;
                    runKeyEvent(keydown_events[KeyCode::A]);
                }
                else
                {
                    keyStates[KeyCode::A] = 0;
                    runKeyEvent(keyup_events[KeyCode::A]);
                }
                break;
            case SDLK_b:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::B] = 1;
                    runKeyEvent(keydown_events[KeyCode::B]);
                }
                else
                {
                    keyStates[KeyCode::B] = 0;
                    runKeyEvent(keyup_events[KeyCode::B]);
                }
                break;
            case SDLK_c:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::C] = 1;
                    runKeyEvent(keydown_events[KeyCode::C]);
                }
                else
                {
                    keyStates[KeyCode::C] = 0;
                    runKeyEvent(keyup_events[KeyCode::C]);
                }
                break;
            case SDLK_d:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::D] = 1;
                    runKeyEvent(keydown_events[KeyCode::D]);
                }
                else
                {
                    keyStates[KeyCode::D] = 0;
                    runKeyEvent(keyup_events[KeyCode::D]);
                }
                break;
            case SDLK_e:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::E] = 1;
                    runKeyEvent(keydown_events[KeyCode::E]);
                }
                else
                {
                    keyStates[KeyCode::E] = 0;
                    runKeyEvent(keyup_events[KeyCode::E]);
                }
                break;
            case SDLK_f:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::F] = 1;
                    runKeyEvent(keydown_events[KeyCode::F]);
                }
                else
                {
                    keyStates[KeyCode::R] = 0;
                    runKeyEvent(keyup_events[KeyCode::R]);
                }
                break;
            case SDLK_g:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::G] = 1;
                    runKeyEvent(keydown_events[KeyCode::G]);
                }
                else
                {
                    keyStates[KeyCode::G] = 0;
                    runKeyEvent(keyup_events[KeyCode::G]);
                }
                break;
            case SDLK_h:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::H] = 1;
                    runKeyEvent(keydown_events[KeyCode::H]);
                }
                else
                {
                    keyStates[KeyCode::H] = 0;
                    runKeyEvent(keyup_events[KeyCode::H]);
                }
                break;
            case SDLK_i:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::I] = 1;
                    runKeyEvent(keydown_events[KeyCode::I]);
                }
                else
                {
                    keyStates[KeyCode::I] = 0;
                    runKeyEvent(keyup_events[KeyCode::I]);
                }
                break;
            case SDLK_j:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::J] = 1;
                    runKeyEvent(keydown_events[KeyCode::J]);
                }
                else
                {
                    keyStates[KeyCode::J] = 0;
                    runKeyEvent(keyup_events[KeyCode::J]);
                }
                break;
            case SDLK_k:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::K] = 1;
                    runKeyEvent(keydown_events[KeyCode::K]);
                }
                else
                {
                    keyStates[KeyCode::K] = 0;
                    runKeyEvent(keyup_events[KeyCode::K]);
                }
                break;
            case SDLK_l:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::L] = 1;
                    runKeyEvent(keydown_events[KeyCode::L]);
                }
                else
                {
                    keyStates[KeyCode::L] = 0;
                    runKeyEvent(keyup_events[KeyCode::L]);
                }
                break;
            case SDLK_m:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::M] = 1;
                    runKeyEvent(keydown_events[KeyCode::M]);
                }
                else
                {
                    keyStates[KeyCode::M] = 0;
                    runKeyEvent(keyup_events[KeyCode::M]);
                }
                break;
            case SDLK_n:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::N] = 1;
                    runKeyEvent(keydown_events[KeyCode::N]);
                }
                else
                {
                    keyStates[KeyCode::N] = 0;
                    runKeyEvent(keyup_events[KeyCode::N]);
                }
                break;
            case SDLK_o:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::O] = 1;
                    runKeyEvent(keydown_events[KeyCode::O]);
                }
                else
                {
                    keyStates[KeyCode::O] = 0;
                    runKeyEvent(keyup_events[KeyCode::O]);
                }
                break;
            case SDLK_p:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::P] = 1;
                    runKeyEvent(keydown_events[KeyCode::P]);
                }
                else
                {
                    keyStates[KeyCode::P] = 0;
                    runKeyEvent(keyup_events[KeyCode::P]);
                }
                break;
            case SDLK_q:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::Q] = 1;
                    runKeyEvent(keydown_events[KeyCode::Q]);
                }
                else
                {
                    keyStates[KeyCode::Q] = 0;
                    runKeyEvent(keyup_events[KeyCode::Q]);
                }
                break;
            case SDLK_r:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::R] = 1;
                    runKeyEvent(keydown_events[KeyCode::R]);
                }
                else
                {
                    keyStates[KeyCode::R] = 0;
                    runKeyEvent(keyup_events[KeyCode::R]);
                }
                break;
            case SDLK_s:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::S] = 1;
                    runKeyEvent(keydown_events[KeyCode::S]);
                }
                else
                {
                    keyStates[KeyCode::S] = 0;
                    runKeyEvent(keyup_events[KeyCode::S]);
                }
                break;
            case SDLK_t:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::T] = 1;
                    runKeyEvent(keydown_events[KeyCode::T]);
                }
                else
                {
                    keyStates[KeyCode::T] = 0;
                    runKeyEvent(keyup_events[KeyCode::T]);
                }
                break;
            case SDLK_u:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::U] = 1;
                    runKeyEvent(keydown_events[KeyCode::U]);
                }
                else
                {
                    keyStates[KeyCode::U] = 0;
                    runKeyEvent(keyup_events[KeyCode::U]);
                }
                break;
            case SDLK_v:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::V] = 1;
                    runKeyEvent(keydown_events[KeyCode::V]);
                }
                else
                {
                    keyStates[KeyCode::V] = 0;
                    runKeyEvent(keyup_events[KeyCode::V]);
                }
                break;
            case SDLK_w:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::W] = 1;
                    runKeyEvent(keydown_events[KeyCode::W]);
                }
                else
                {
                    keyStates[KeyCode::W] = 0;
                    runKeyEvent(keyup_events[KeyCode::W]);
                }
                break;
            case SDLK_x:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::X] = 1;
                    runKeyEvent(keydown_events[KeyCode::X]);
                }
                else
                {
                    keyStates[KeyCode::X] = 0;
                    runKeyEvent(keyup_events[KeyCode::X]);
                }
                break;
            case SDLK_y:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::Y] = 1;
                    runKeyEvent(keydown_events[KeyCode::Y]);
                }
                else
                {
                    keyStates[KeyCode::Y] = 0;
                    runKeyEvent(keyup_events[KeyCode::Y]);
                }
                break;
            case SDLK_z:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::Z] = 1;
                    runKeyEvent(keydown_events[KeyCode::Z]);
                }
                else
                {
                    keyStates[KeyCode::Z] = 0;
                    runKeyEvent(keyup_events[KeyCode::Z]);
                }
                break;
            case SDLK_1:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::ONE] = 1;
                    runKeyEvent(keydown_events[KeyCode::ONE]);
                }
                else
                {
                    keyStates[KeyCode::ONE] = 0;
                    runKeyEvent(keyup_events[KeyCode::ONE]);
                }
                break;
            case SDLK_2:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::TWO] = 1;
                    runKeyEvent(keydown_events[KeyCode::TWO]);
                }
                else
                {
                    keyStates[KeyCode::TWO] = 0;
                    runKeyEvent(keyup_events[KeyCode::TWO]);
                }
                break;
            case SDLK_3:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::THREE] = 1;
                    runKeyEvent(keydown_events[KeyCode::THREE]);
                }
                else
                {
                    keyStates[KeyCode::THREE] = 0;
                    runKeyEvent(keyup_events[KeyCode::THREE]);
                }
                break;
            case SDLK_4:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::FOUR] = 1;
                    runKeyEvent(keydown_events[KeyCode::FOUR]);
                }
                else
                {
                    keyStates[KeyCode::FOUR] = 0;
                    runKeyEvent(keyup_events[KeyCode::FOUR]);
                }
                break;
            case SDLK_5:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::FIVE] = 1;
                    runKeyEvent(keydown_events[KeyCode::FIVE]);
                }
                else
                {
                    keyStates[KeyCode::FIVE] = 0;
                    runKeyEvent(keyup_events[KeyCode::FIVE]);
                }
                break;
            case SDLK_6:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::SIX] = 1;
                    runKeyEvent(keydown_events[KeyCode::SIX]);
                }
                else
                {
                    keyStates[KeyCode::SIX] = 0;
                    runKeyEvent(keyup_events[KeyCode::SIX]);
                }
                break;
            case SDLK_7:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::SEVEN] = 1;
                    runKeyEvent(keydown_events[KeyCode::SEVEN]);
                }
                else
                {
                    keyStates[KeyCode::SEVEN] = 0;
                    runKeyEvent(keyup_events[KeyCode::SEVEN]);
                }
                break;
            case SDLK_8:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::EIGHT] = 1;
                    runKeyEvent(keydown_events[KeyCode::EIGHT]);
                }
                else
                {
                    keyStates[KeyCode::EIGHT] = 0;
                    runKeyEvent(keyup_events[KeyCode::EIGHT]);
                }
                break;
            case SDLK_9:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::NINE] = 1;
                    runKeyEvent(keydown_events[KeyCode::NINE]);
                }
                else
                {
                    keyStates[KeyCode::NINE] = 0;
                    runKeyEvent(keyup_events[KeyCode::NINE]);
                }
                break;
            case SDLK_0:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::ZERO] = 1;
                    runKeyEvent(keydown_events[KeyCode::ZERO]);
                }
                else
                {
                    keyStates[KeyCode::ZERO] = 0;
                    runKeyEvent(keyup_events[KeyCode::ZERO]);
                }
                break;
            case SDLK_ESCAPE:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::ESCAPE] = 1;
                    runKeyEvent(keydown_events[KeyCode::ESCAPE]);
                }
                else
                {
                    keyStates[KeyCode::ESCAPE] = 0;
                    runKeyEvent(keyup_events[KeyCode::ESCAPE]);
                }
                break;
            case SDLK_TAB:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::TAB] = 1;
                    runKeyEvent(keydown_events[KeyCode::TAB]);
                }
                else
                {
                    keyStates[KeyCode::TAB] = 0;
                    runKeyEvent(keyup_events[KeyCode::TAB]);
                }
                break;
            case SDLK_CAPSLOCK:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::CAPS] = 1;
                    runKeyEvent(keydown_events[KeyCode::CAPS]);
                }
                else
                {
                    keyStates[KeyCode::CAPS] = 0;
                    runKeyEvent(keyup_events[KeyCode::CAPS]);
                }
                break;
            case SDLK_BACKQUOTE:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::BACKTICK] = 1;
                    runKeyEvent(keydown_events[KeyCode::BACKTICK]);
                }
                else
                {
                    keyStates[KeyCode::BACKTICK] = 0;
                    runKeyEvent(keyup_events[KeyCode::BACKTICK]);
                }
                break;
            case SDLK_MINUS:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::MINUS] = 1;
                    runKeyEvent(keydown_events[KeyCode::MINUS]);
                }
                else
                {
                    keyStates[KeyCode::MINUS] = 0;
                    runKeyEvent(keyup_events[KeyCode::MINUS]);
                }
                break;
            case SDLK_EQUALS:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::EQUALS] = 1;
                    runKeyEvent(keydown_events[KeyCode::EQUALS]);
                }
                else
                {
                    keyStates[KeyCode::EQUALS] = 0;
                    runKeyEvent(keyup_events[KeyCode::EQUALS]);
                }
                break;
            case SDLK_BACKSPACE:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::BACKSPACE] = 1;
                    runKeyEvent(keydown_events[KeyCode::BACKSPACE]);
                }
                else
                {
                    keyStates[KeyCode::BACKSPACE] = 0;
                    runKeyEvent(keyup_events[KeyCode::BACKSPACE]);
                }
                break;
            case SDLK_LEFTBRACKET:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::LBRACKET] = 1;
                    runKeyEvent(keydown_events[KeyCode::LBRACKET]);
                }
                else
                {
                    keyStates[KeyCode::LBRACKET] = 0;
                    runKeyEvent(keyup_events[KeyCode::LBRACKET]);
                }
                break;
            case SDLK_RIGHTBRACKET:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::RBRACKET] = 1;
                    runKeyEvent(keydown_events[KeyCode::RBRACKET]);
                }
                else
                {
                    keyStates[KeyCode::RBRACKET] = 0;
                    runKeyEvent(keyup_events[KeyCode::RBRACKET]);
                }
                break;
            case SDLK_SLASH:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::FSLASH] = 1;
                    runKeyEvent(keydown_events[KeyCode::FSLASH]);
                }
                else
                {
                    keyStates[KeyCode::FSLASH] = 0;
                    runKeyEvent(keyup_events[KeyCode::FSLASH]);
                }
                break;
            case SDLK_BACKSLASH:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::BSLASH] = 1;
                    runKeyEvent(keydown_events[KeyCode::BSLASH]);
                }
                else
                {
                    keyStates[KeyCode::BSLASH] = 0;
                    runKeyEvent(keyup_events[KeyCode::BSLASH]);
                }
                break;
            case SDLK_SEMICOLON:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::SEMICOLON] = 1;
                    runKeyEvent(keydown_events[KeyCode::SEMICOLON]);
                }
                else
                {
                    keyStates[KeyCode::SEMICOLON] = 0;
                    runKeyEvent(keyup_events[KeyCode::SEMICOLON]);
                }
                break;
            case SDLK_QUOTE:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::QUOTE] = 1;
                    runKeyEvent(keydown_events[KeyCode::QUOTE]);
                }
                else
                {
                    keyStates[KeyCode::QUOTE] = 0;
                    runKeyEvent(keyup_events[KeyCode::QUOTE]);
                }
                break;
            case SDLK_RETURN:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::RETURN] = 1;
                    runKeyEvent(keydown_events[KeyCode::RETURN]);
                }
                else
                {
                    keyStates[KeyCode::RETURN] = 0;
                    runKeyEvent(keyup_events[KeyCode::RETURN]);
                }
                break;
            case SDLK_COMMA:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::COMMA] = 1;
                    runKeyEvent(keydown_events[KeyCode::COMMA]);
                }
                else
                {
                    keyStates[KeyCode::COMMA] = 0;
                    runKeyEvent(keyup_events[KeyCode::COMMA]);
                }
                break;
            case SDLK_PERIOD:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::PERIOD] = 1;
                    runKeyEvent(keydown_events[KeyCode::PERIOD]);
                }
                else
                {
                    keyStates[KeyCode::PERIOD] = 0;
                    runKeyEvent(keyup_events[KeyCode::PERIOD]);
                }
                break;
            case SDLK_UP:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::UPARROW] = 1;
                    runKeyEvent(keydown_events[KeyCode::UPARROW]);
                }
                else
                {
                    keyStates[KeyCode::UPARROW] = 0;
                    runKeyEvent(keyup_events[KeyCode::UPARROW]);
                }
                break;
            case SDLK_DOWN:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::DOWNARROW] = 1;
                    runKeyEvent(keydown_events[KeyCode::DOWNARROW]);
                }
                else
                {
                    keyStates[KeyCode::DOWNARROW] = 0;
                    runKeyEvent(keyup_events[KeyCode::DOWNARROW]);
                }
                break;
            case SDLK_LEFT:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::LEFTARROW] = 1;
                    runKeyEvent(keydown_events[KeyCode::LEFTARROW]);
                }
                else
                {
                    keyStates[KeyCode::LEFTARROW] = 0;
                    runKeyEvent(keyup_events[KeyCode::LEFTARROW]);
                }
                break;
            case SDLK_RIGHT:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::RIGHTARROW] = 1;
                    runKeyEvent(keydown_events[KeyCode::RIGHTARROW]);
                }
                else
                {
                    keyStates[KeyCode::RIGHTARROW] = 0;
                    runKeyEvent(keyup_events[KeyCode::RIGHTARROW]);
                }
                break;
            case SDLK_SPACE:
                if (event.type == SDL_KEYDOWN)
                {
                    keyStates[KeyCode::SPACE] = 1;
                    runKeyEvent(keydown_events[KeyCode::SPACE]);
                }
                else
                {
                    keyStates[KeyCode::SPACE] = 0;
                    runKeyEvent(keyup_events[KeyCode::SPACE]);
                }
                break;
        }
    }
    
    /*
    // Handle held events
    int numkeys;
    const Uint8* boardState = SDL_GetKeyboardState(&numkeys);
    if (boardState[SDL_SCANCODE_A] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::A]);
    }
    if (boardState[SDL_SCANCODE_B] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::B]);
    }
    if (boardState[SDL_SCANCODE_C] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::C]);
    }
    if (boardState[SDL_SCANCODE_D] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::D]);
    }
    if (boardState[SDL_SCANCODE_E] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::E]);
    }
    if (boardState[SDL_SCANCODE_F] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::F]);
    }
    if (boardState[SDL_SCANCODE_G] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::G]);
    }
    if (boardState[SDL_SCANCODE_H] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::H]);
    }
    if (boardState[SDL_SCANCODE_I] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::I]);
    }
    if (boardState[SDL_SCANCODE_J] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::J]);
    }
    if (boardState[SDL_SCANCODE_K] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::K]);
    }
    if (boardState[SDL_SCANCODE_L] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::L]);
    }
    if (boardState[SDL_SCANCODE_M] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::M]);
    }
    if (boardState[SDL_SCANCODE_N] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::N]);
    }
    if (boardState[SDL_SCANCODE_O] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::O]);
    }
    if (boardState[SDL_SCANCODE_P] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::P]);
    }
    if (boardState[SDL_SCANCODE_Q] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::Q]);
    }
    if (boardState[SDL_SCANCODE_R] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::R]);
    }
    if (boardState[SDL_SCANCODE_S] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::S]);
    }
    if (boardState[SDL_SCANCODE_T] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::T]);
    }
    if (boardState[SDL_SCANCODE_U] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::U]);
    }
    if (boardState[SDL_SCANCODE_V] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::V]);
    }
    if (boardState[SDL_SCANCODE_W] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::W]);
    }
    if (boardState[SDL_SCANCODE_X] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::X]);
    }
    if (boardState[SDL_SCANCODE_Y] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::Y]);
    }
    if (boardState[SDL_SCANCODE_Z] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::Z]);
    }
    if (boardState[SDL_SCANCODE_1] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::ONE]);
    }
    if (boardState[SDL_SCANCODE_2] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::TWO]);
    }
    if (boardState[SDL_SCANCODE_3] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::THREE]);
    }
    if (boardState[SDL_SCANCODE_4] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::FOUR]);
    }
    if (boardState[SDL_SCANCODE_5] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::FIVE]);
    }
    if (boardState[SDL_SCANCODE_6] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::SIX]);
    }
    if (boardState[SDL_SCANCODE_7] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::SEVEN]);
    }
    if (boardState[SDL_SCANCODE_8] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::EIGHT]);
    }
    if (boardState[SDL_SCANCODE_9] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::NINE]);
    }
    if (boardState[SDL_SCANCODE_0] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::ZERO]);
    }
    if (boardState[SDL_SCANCODE_ESCAPE] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::ESCAPE]);
    }
    if (boardState[SDL_SCANCODE_TAB] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::TAB]);
    }
    if (boardState[SDL_SCANCODE_CAPSLOCK] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::CAPS]);
    }
    if (boardState[SDL_SCANCODE_GRAVE] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::BACKTICK]);
    }
    if (boardState[SDL_SCANCODE_MINUS] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::MINUS]);
    }
    if (boardState[SDL_SCANCODE_EQUALS] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::EQUALS]);
    }
    if (boardState[SDL_SCANCODE_BACKSPACE] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::BACKSPACE]);
    }
    if (boardState[SDL_SCANCODE_LEFTBRACKET] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::LBRACKET]);
    }
    if (boardState[SDL_SCANCODE_RIGHTBRACKET] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::RBRACKET]);
    }
    if (boardState[SDL_SCANCODE_SLASH] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::FSLASH]);
    }
    if (boardState[SDL_SCANCODE_BACKSLASH] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::BSLASH]);
    }
    if (boardState[SDL_SCANCODE_SEMICOLON] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::SEMICOLON]);
    }
    if (boardState[SDL_SCANCODE_APOSTROPHE] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::QUOTE]);
    }
    if (boardState[SDL_SCANCODE_RETURN] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::RETURN]);
    }
    if (boardState[SDL_SCANCODE_COMMA] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::COMMA]);
    }
    if (boardState[SDL_SCANCODE_PERIOD] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::PERIOD]);
    }
    if (boardState[SDL_SCANCODE_UP] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::UPARROW]);
    }
    if (boardState[SDL_SCANCODE_DOWN] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::DOWNARROW]);
    }
    if (boardState[SDL_SCANCODE_LEFT] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::LEFTARROW]);
    }
    if (boardState[SDL_SCANCODE_RIGHT] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::RIGHTARROW]);
    }
    if (boardState[SDL_SCANCODE_SPACE] == 1)
    {
        runKeyEvent(keyheld_events[KeyCode::SPACE]);
    }
    */
}

void CApp::OnLoop()
{
    for (unsigned i = 0; i < obj_list.size(); ++i)
    {
        // Skip object if STATIC flag is set
        GameObject* GOptr = &obj_list[i];
        if (GOptr->checkFlag(ObjectFlag::STATIC)) continue;

        // Check event list
        checkObjectEvents(GOptr);

        // Check held key event list
        for (int i = 0; i < KeyCode::SPACE+1; ++i)
        {
            if (keyStates[i])
                runKeyEvent(keyheld_events[(KeyCode)i]);
        }
        
        // Update position and velocity
        GOptr->vel_x += GOptr->acc_x;
        GOptr->pos_x += GOptr->vel_x;

        GOptr->vel_y += GOptr->acc_y;
        GOptr->pos_y += GOptr->vel_y;

        GOptr->vel_ang += GOptr->acc_ang;
        //if (GOptr->vel_ang >= 360) GOptr->vel_ang -= 360;
        GOptr->angle += GOptr->vel_ang;
        while (GOptr->angle >= 360) GOptr->angle -= 360;

        //std::cout << "ACC= [" << GOptr->acc_x << "," << GOptr->acc_y << "] | VEL = [" << GOptr->vel_x << "," << GOptr->vel_y << "]\n";
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