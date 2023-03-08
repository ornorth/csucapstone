#include <ratio>
#include <chrono>
#include <random>
#include "CApp.h"

#define PI 3.14159265

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
        // Doesn't work like this
        // case ObjectAttribute::COLOR:
        //     return &GOptr->color;
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
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute att, Color value)
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
bool CApp::addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute att, Color value)
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
bool CApp::addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute att, Color value)
{
    int idx = getGameObject(obj_name);
    if (idx == -1) return false;

    switch(type)
    {
        case KeyPressType::DOWN:
            keydown_events[key].push_back({action, obj_name, "NULL", 0.0, att, value});
            break;
        case KeyPressType::UP:
            keyup_events[key].push_back({action, obj_name, "NULL", 0.0, att, value});
            break;
        case KeyPressType::HELD:
            keyheld_events[key].push_back({action, obj_name, "NULL", 0.0, att, value});
            break;
    }
    return true;
}

bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2);
    if (idx == -1 || jdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, "NULL", "NULL", 0.0, ObjectAttribute::WIDTH, {0, 0, 0, 0}, false});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2), kdx = getGameObject(obj_name);
    if (idx == -1 || jdx == -1 || kdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, obj_name, "NULL", 0.0, ObjectAttribute::WIDTH, {0, 0, 0, 0}, false});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, const std::string& name)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2), kdx = getGameObject(obj_name);
    if (idx == -1 || jdx == -1 || kdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, obj_name, name, 0.0, ObjectAttribute::WIDTH, {0, 0, 0, 0}, false});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, double value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2), kdx = getGameObject(obj_name);
    if (idx == -1 || jdx == -1 || kdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, obj_name, "NULL", value, ObjectAttribute::WIDTH, {0, 0, 0, 0}, false});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, const std::string& name, double value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2), kdx = getGameObject(obj_name);
    if (idx == -1 || jdx == -1 || kdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, obj_name, name, value, ObjectAttribute::WIDTH, {0, 0, 0, 0}, false});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute att, double value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2), kdx = getGameObject(obj_name);
    if (idx == -1 || jdx == -1 || kdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, obj_name, "NULL", value, att, {0, 0, 0, 0}, false});
    return true;
}
bool CApp::addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute att, Color value)
{
    int idx = getGameObject(obj_1), jdx = getGameObject(obj_2), kdx = getGameObject(obj_name);
    if (idx == -1 || jdx == -1 || kdx == -1) return false;

    collision_events[{obj_1, obj_2}].push_back({action, obj_name, "NULL", 0.0, att, value, false});
    return true;
}

void CApp::checkObjectEvents(GameObject* GOptr)
{
    for (auto& it: GOptr->event_list)
    {
        bool flag = false;
        switch(it.first.event)
        {
            case GameEvent::ALWAYS:
            {
                flag = true;
                break;
            }
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
            // FIX: These do NOT work with Color attribute or any other non-double
            // find a better solution than this
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
                if (events[idx].attribute == ObjectAttribute::COLOR)
                {
                    GOptr->color = events[idx].color;
                    break;
                }
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
                if (events[idx].attribute == ObjectAttribute::COLOR)
                {
                    GOptr->color = events[idx].color;
                    break;
                }
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
void CApp::runCollisionEvents(std::vector<KeyActionList>& events)
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
                if (events[idx].attribute == ObjectAttribute::COLOR)
                {
                    GOptr->color = events[idx].color;
                    break;
                }
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

bool CApp::collisionOccurred(const StrPair& colliders)
{
    // explore this idea in the actual rendering phase
    bool edges[window_width][window_height];
    for (int i = 0; i < window_width; ++i)
    {
        for (int j = 0; j < window_height; ++j)
            edges[i][j] = false;
    }

    GameObject* GOptr = &obj_list[getGameObject(colliders.first)];
    switch(GOptr->getShape())
    {
        case Shape::RECTANGLE:
        {
            double convAngle = GOptr->angle * PI / 180.0;
            int convX, convY;
            
            for (int x = (GOptr->dim_x / 2) * -1; x < GOptr->dim_x / 2; x++)
            {
                convX = GOptr->pos_x + (x*std::cos(convAngle)) - ((GOptr->dim_y/2-1)*std::sin(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle)) + ((GOptr->dim_y/2-1)*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;

                convX = GOptr->pos_x + (x*std::cos(convAngle)) - (-(GOptr->dim_y/2)*std::sin(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle)) + (-(GOptr->dim_y/2)*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;

                // Test adding another line in the center (to prevent small objects from hiding inside big ones)
                convX = GOptr->pos_x + (x*std::cos(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;
            }
            for (int y = (GOptr->dim_y / 2) * -1; y < GOptr->dim_y / 2; y++)
            {
                convX = GOptr->pos_x + ((GOptr->dim_x/2-1)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + ((GOptr->dim_x/2-1)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;

                convX = GOptr->pos_x + (-(GOptr->dim_x/2)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (-(GOptr->dim_x/2)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;

                // Test adding another line in the center (to prevent small objects from hiding inside big ones)
                convX = GOptr->pos_x - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;
            }
            break;
        }
        case Shape::CIRCLE:
        {
            int c_dim_x = GOptr->dim_x / 2;
            int c_dim_y = GOptr->dim_y / 2;

            // Be careful of overflow here
            long hh = c_dim_y*c_dim_y;
            long ww = c_dim_x*c_dim_x;
            long hhww = hh*ww;
            int x0 = c_dim_x;
            int dx = 0;
            double convAngle = GOptr->angle * PI / 180.0;

            int convX, convY;
            // Test adding lines in the center (to prevent small objects from hiding inside big ones)
            for (int x = -c_dim_x/2; x < c_dim_x/2; ++x)
            {
                convX = GOptr->pos_x + (x*std::cos(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;
            }
            for (int y = -c_dim_y/2; y < c_dim_y/2; ++y)
            {
                convX = GOptr->pos_x - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;
            }

            for (int y = 1; y <= c_dim_y; ++y)
            {
                int x1 = x0 - (dx - 1);
                for ( ; x1 > 0; --x1)
                    if (x1*x1*hh + y*y*ww <= hhww) break;
                
                dx = x0 - x1;
                x0 = x1;

                for (int x = -x0; x <= x0; ++x)
                {
                    convX = GOptr->pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle));
                    convY = GOptr->pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle));
                    if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                        edges[convX][convY] = true;

                    convX = GOptr->pos_x + (x*std::cos(convAngle)) - (-y*std::sin(convAngle));
                    convY = GOptr->pos_y + (x*std::sin(convAngle)) + (-y*std::cos(convAngle));
                    if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                        edges[convX][convY] = true;
                }
            }
            break;
        }
        case Shape::TRIANGLE:
        {
            int c_dim_x = GOptr->dim_x;
            int c_dim_y = GOptr->dim_y;
            double convAngle = GOptr->angle * PI / 180.0;

            double aspectRatio = (double)c_dim_x / c_dim_y;
            double x_width = c_dim_x;

            int convX, convY;
            for (int y = (c_dim_y/2); y >= (c_dim_y/2) * -1; --y)
            {
                convX = GOptr->pos_x + ((x_width/2*-1)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + ((x_width/2*-1)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;

                convX = GOptr->pos_x + ((x_width/2)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + ((x_width/2)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;

                // Test adding another line in the center (to prevent small objects from hiding inside big ones)
                convX = GOptr->pos_x - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width && convY >= 0 && convY < window_height)
                    edges[convX][convY] = true;
                
                x_width -= aspectRatio;
            }
            break;
        }
        default:
        {
            std::cerr << "YOU FOOL! YOU'VE DOOMED US ALL!!!n";
            exit(1);
        }
    }

    GOptr = &obj_list[getGameObject(colliders.second)];
    switch(GOptr->getShape())
    {
        case Shape::RECTANGLE:
        {
            double convAngle = GOptr->angle * PI / 180.0;
            int convX, convY;
            
            for (int x = (GOptr->dim_x / 2) * -1; x < GOptr->dim_x / 2; x++)
            {
                convX = GOptr->pos_x + (x*std::cos(convAngle)) - ((GOptr->dim_y/2-1)*std::sin(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle)) + ((GOptr->dim_y/2-1)*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }

                convX = GOptr->pos_x + (x*std::cos(convAngle)) - (-(GOptr->dim_y/2)*std::sin(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle)) + (-(GOptr->dim_y/2)*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }

                // Test adding another line in the center (to prevent small objects from hiding inside big ones)
                convX = GOptr->pos_x + (x*std::cos(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }
            }
            for (int y = (GOptr->dim_y / 2) * -1; y < GOptr->dim_y / 2; y++)
            {
                convX = GOptr->pos_x + ((GOptr->dim_x/2-1)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + ((GOptr->dim_x/2-1)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }

                convX = GOptr->pos_x + (-(GOptr->dim_x/2)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (-(GOptr->dim_x/2)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }

                // Test adding another line in the center (to prevent small objects from hiding inside big ones)
                convX = GOptr->pos_x - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }
            }
            break;
        }
        case Shape::CIRCLE:
        {
            int c_dim_x = GOptr->dim_x / 2;
            int c_dim_y = GOptr->dim_y / 2;

            // Be careful of overflow here
            long hh = c_dim_y*c_dim_y;
            long ww = c_dim_x*c_dim_x;
            long hhww = hh*ww;
            int x0 = c_dim_x;
            int dx = 0;
            double convAngle = GOptr->angle * PI / 180.0;

            int convX, convY;
            // Test adding lines in the center (to prevent small objects from hiding inside big ones)
            for (int x = -c_dim_x/2; x < c_dim_x/2; ++x)
            {
                convX = GOptr->pos_x + (x*std::cos(convAngle));
                convY = GOptr->pos_y + (x*std::sin(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }
            }
            for (int y = -c_dim_y/2; y < c_dim_y/2; ++y)
            {
                convX = GOptr->pos_x - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }
            }

            for (int y = 1; y <= c_dim_y; ++y)
            {
                int x1 = x0 - (dx - 1);
                for ( ; x1 > 0; --x1)
                    if (x1*x1*hh + y*y*ww <= hhww) break;
                
                dx = x0 - x1;
                x0 = x1;

                for (int x = -x0; x <= x0; ++x)
                {
                    convX = GOptr->pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle));
                    convY = GOptr->pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle));
                    if (convX >= 0 && convX < window_width
                        && convY >= 0 && convY < window_height
                        && edges[convX][convY])
                    {
                        return true;
                    }

                    convX = GOptr->pos_x + (x*std::cos(convAngle)) - (-y*std::sin(convAngle));
                    convY = GOptr->pos_y + (x*std::sin(convAngle)) + (-y*std::cos(convAngle));
                    if (convX >= 0 && convX < window_width
                        && convY >= 0 && convY < window_height
                        && edges[convX][convY])
                    {
                        return true;
                    }
                }
            }
            break;
        }
        case Shape::TRIANGLE:
        {
            int c_dim_x = GOptr->dim_x;
            int c_dim_y = GOptr->dim_y;
            double convAngle = GOptr->angle * PI / 180.0;

            double aspectRatio = (double)c_dim_x / c_dim_y;
            double x_width = c_dim_x;

            int convX, convY;
            for (int y = (c_dim_y/2); y >= (c_dim_y/2) * -1; --y)
            {
                convX = GOptr->pos_x + ((x_width/2*-1)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + ((x_width/2*-1)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }

                convX = GOptr->pos_x + ((x_width/2)*std::cos(convAngle)) - (y*std::sin(convAngle));
                convY = GOptr->pos_y + ((x_width/2)*std::sin(convAngle)) + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }

                // Test adding another line in the center (to prevent small objects from hiding inside big ones)
                convX = GOptr->pos_x - (y*std::sin(convAngle));
                convY = GOptr->pos_y + (y*std::cos(convAngle));
                if (convX >= 0 && convX < window_width
                    && convY >= 0 && convY < window_height
                    && edges[convX][convY])
                {
                    return true;
                }
                
                x_width -= aspectRatio;
            }
            break;
        }
        default:
        {
            std::cerr << "YOU FOOL! YOU'VE DOOMED US ALL!!!n";
            exit(1);
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
             //std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1).count() < 1.0;
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
        // Key was just pressed
        if (boardState[idx] && !keyStates[idx])
        {
            keyStates[idx] = 1;
            runKeyEvents(keydown_events[(KeyCode)idx]);
        }
        // Key was just released
        else if (!boardState[idx] && keyStates[idx])
        {
            keyStates[idx] = 0;
            runKeyEvents(keyup_events[(KeyCode)idx]);
        }
        // Key is being held ()
        if (keyStates[idx])
        {
            runKeyEvents(keyheld_events[(KeyCode)idx]);
        }
    }
}

/*  Open question on which order to do things
 *  This function does 3 things:
     - Check Object events
     - Update object variables (position based on velocity, etc.)
     - Check collision events
 *  The order in which these things are processed can matter. For instance:
 *   - The ALWAYS event should run first, because it has a lower precedence than other events
 *   - This is so you can use ALWAYS to program default behavior that another event can overwrite
 *   - (Ex: in ex8.cpp, ALWAYS set an object's color to black, then set it to red on a collision event)
 *  In order to keep this behavior, Collisions events should be run after Object events,
 *  But running Collisions first makes more sense intuitively
 *  
 *  What I see as a 'proper' fix to this is allowing the user to define an event's priority
 *  This would require further complicating the event maps, changing them to a list or vector of maps
 *    such that index=priority desc. - 0 is highest, so we run events starting at X and working down to 0
 *  There are many obvious advantages to such a system, but it is a lower priority addition,
 *  So it may not happen soon, but if/when it is added:
 *   - for i from max_prio->0:
 *   -   runCollision(collision_events[i])
 *   -   runObject(object_events[i])_
 *   - update object variables (position, vel, etc.)
 *   - // this is outside of the loop as it needs no priority
 */
void CApp::OnLoop()
{
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
    // Using auto here makes the object immutable. Use an iterator instead
    for (std::map<StrPair, std::vector<KeyActionList>, StrPairComp>::iterator it = collision_events.begin(); it != collision_events.end(); ++it)
    {
        if (collisionOccurred(it->first))
            runCollisionEvents(it->second);
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