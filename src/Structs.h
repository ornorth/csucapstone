#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL.h"
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
    X_BORDERCOLLISION,
    Y_BORDERCOLLISION,
};

enum KeyCode {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    ZERO,
    ESCAPE,
    TAB,
    CAPS,
    BACKTICK, //SDLK_BACKQUOTE
    MINUS,
    EQUALS,
    BACKSPACE,
    LBRACKET,
    RBRACKET,
    FSLASH,
    BSLASH,
    SEMICOLON,
    QUOTE,
    RETURN,
    COMMA,
    PERIOD,
    UPARROW,
    DOWNARROW,
    LEFTARROW,
    RIGHTARROW,
    SPACE,          //IMPORTANT: Ensure SPACE is final in list (being used to determine size of enum)
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

struct ActionList {
    GameAction type;
    std::string id;
    double value;
    ObjectAttribute attribute;
};

struct KeyActionList {
    GameAction type;
    GameObject* object;
    std::string id;
    double value;
    ObjectAttribute attribute;
};

#endif