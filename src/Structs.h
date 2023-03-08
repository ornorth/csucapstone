#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL.h"
#include <string>
//#include "GameObject.h"
class GameObject;


struct Color {
    int r;
    int g;
    int b;
    int a;
};

enum Shape {
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
};

enum ObjectAttribute {
    WIDTH,
    HEIGHT,
    ANGLE,
    X_POSITION,
    Y_POSITION,
    X_VELOCITY,
    Y_VELOCITY,
    X_ACCELERATION,
    Y_ACCELERATION,
    ANG_VELOCITY,
    ANG_ACCELERATION,
    COLOR,

    USER_DOUBLE_1,
    USER_DOUBLE_2,
    USER_DOUBLE_3,
};

enum ObjectFlag {
    // User-relevant flags
    STATIC = 1,                 // Update loop ignores this game object

    // Internal use flags
    X_BORDER_COLLIDED = 256,    // Object collided with the X border on the previous frame
    Y_BORDER_COLLIDED = 512,    // Object collided with the Y border on the previous frame
};
/*  flags
 *  (1)  1          - 
 *  (2)  2          - 
 *  (3)  4          - 
 *  (4)  8          - 
 *  (5)  16         - 
 *  (6)  32         - 
 *  (7)  64         - 
 *  (8)  128        - 
 *  (9)  256        - 
 *  (10) 512        - 
 *  (11) 1024       - 
 *  (12) 2048       - 
 *  (13) 4096       - 
 *  (14) 8192       - 
 *  (15) 16384      - 
 *  (16) 32768      - 
*/ 

enum GameEvent {
    ALWAYS,
    X_BORDERCOLLISION,
    Y_BORDERCOLLISION,
    OBJ_VAR_EQUALS,
    OBJ_VAR_IS_LESS,
    OBJ_VAR_IS_GREATER,
};

enum KeyCode {
    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F,
    G = SDL_SCANCODE_G,
    H = SDL_SCANCODE_H,
    I = SDL_SCANCODE_I,
    J = SDL_SCANCODE_J,
    K = SDL_SCANCODE_K,
    L = SDL_SCANCODE_L,
    M = SDL_SCANCODE_M,
    N = SDL_SCANCODE_N,
    O = SDL_SCANCODE_O,
    P = SDL_SCANCODE_P,
    Q = SDL_SCANCODE_Q,
    R = SDL_SCANCODE_R,
    S = SDL_SCANCODE_S,
    T = SDL_SCANCODE_T,
    U = SDL_SCANCODE_U,
    V = SDL_SCANCODE_V,
    W = SDL_SCANCODE_W,
    X = SDL_SCANCODE_X,
    Y = SDL_SCANCODE_Y,
    Z = SDL_SCANCODE_Z,
    ONE = SDL_SCANCODE_1,
    TWO = SDL_SCANCODE_2,
    THREE = SDL_SCANCODE_3,
    FOUR = SDL_SCANCODE_4,
    FIVE = SDL_SCANCODE_5,
    SIX = SDL_SCANCODE_6,
    SEVEN = SDL_SCANCODE_7,
    EIGHT = SDL_SCANCODE_8,
    NINE = SDL_SCANCODE_9,
    ZERO = SDL_SCANCODE_0,
    ESCAPE = SDL_SCANCODE_ESCAPE,
    TAB = SDL_SCANCODE_TAB,
    CAPS = SDL_SCANCODE_CAPSLOCK,
    BACKTICK = SDL_SCANCODE_GRAVE,
    MINUS = SDL_SCANCODE_MINUS,
    EQUALS = SDL_SCANCODE_EQUALS,
    BACKSPACE = SDL_SCANCODE_BACKSPACE,
    LBRACKET = SDL_SCANCODE_LEFTBRACKET,
    RBRACKET = SDL_SCANCODE_RIGHTBRACKET,
    FSLASH = SDL_SCANCODE_SLASH,
    BSLASH = SDL_SCANCODE_BACKSLASH,
    SEMICOLON = SDL_SCANCODE_SEMICOLON,
    QUOTE = SDL_SCANCODE_APOSTROPHE,
    RETURN = SDL_SCANCODE_RETURN,
    COMMA = SDL_SCANCODE_COMMA,
    PERIOD = SDL_SCANCODE_PERIOD,
    UPARROW = SDL_SCANCODE_UP,
    DOWNARROW = SDL_SCANCODE_DOWN,
    LEFTARROW = SDL_SCANCODE_LEFT,
    RIGHTARROW = SDL_SCANCODE_RIGHT,
    SPACE = SDL_SCANCODE_SPACE,

    MAX_KEYCODE = 100,
};

enum KeyPressType {
    DOWN,
    UP,
    HELD,
    // SHIFT,
    // ALT,
    // CTRL,
};

enum GameAction {
    // Metagame Actions
    QUIT,

    // Object Actions
    SETVAR,         // set a variable
                    //  - variable name
                    //  - new value to set: name = var
    INCVAR,         // increment a variable
                    //  - variable name
                    //  - value by which to increment: name += var
    SCALEVAR,       // scale a variable
                    //  - variable name
                    //  - value by which to scale: name *= var
    TOGGLE,         // toggle a flag
                    //  - name of the flag
    BOUNCE_X,       // reverse X velocity, as if the object "bounced" off a surface
    BOUNCE_Y,       // reverse Y velocity, as if the object "bounced" off a surface
};

struct EventList {
    GameEvent event;
    ObjectAttribute attribute;
    double value;

    bool operator==(const EventList& e) const {
        return (e.event == event) && (e.attribute == attribute) && (e.value == value);
    }
    bool operator<(const EventList& e) const {
        if (event < e.event) return true;
        if (attribute < e.attribute) return true;
        return (value < e.value);
    }
};
struct EventListCompare {
    bool operator() (const EventList& lhs, const EventList& rhs) const
    {
        return lhs < rhs;
    }
};

struct StrPair {
    std::string first;
    std::string second;
};
struct StrPairComp
{
    template<typename T>
    bool operator()(const T &l, const T &r) const
    {
        if (l.first == r.first)
            return l.second > r.second;
        return l.first < r.first;
    }
};
// template <>
// struct std::hash<EventList>
// {
//     std::size_t operator()(const EventList& e) const
//     {
//         return ((std::hash<int>()(e.event)
//                     ^ (std::hash<int>()(e.attribute) << 1)) >> 1)
//                     ^ (std::hash<double>()(e.value) << 1);
//     }
// };

struct ActionList {
    GameAction type;
    std::string id;
    double value;
    ObjectAttribute attribute;
    Color color;
};

// Collision events also use this action list
// This will likely have to be changed at some point
struct KeyActionList {
    GameAction type;
    std::string object_name;
    std::string id;
    double value;
    ObjectAttribute attribute;
    Color color;
    bool ran_last_frame; // Used for Collision events to prevent multiple consecutive collisions
};

#endif