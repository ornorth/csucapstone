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
    SIZE,
    ANGLE,
    POSITION,
    VELOCITY,
    ACCELERATION,
    ANG_VELOCITY,
    ANG_ACCELERATION,
};

enum ObjectFlag {
    STATIC = 1, // Update loop ignores this game object
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
 *  (17) 65536      - 
 *  (18) 131072     - 
 *  (19) 262144     - 
 *  (20) 524288     - 
 *  (21) 1048576    - 
 *  (22) 2097152    - 
 *  (23) 4194304    - 
 *  (24) 8388608    - 
 *  (25) 16777216   - 
 *  (26) 33554432   - 
 *  (27) 67108864   - 
 *  (28) 134217728  - 
 *  (29) 268435456  - 
 *  (30) 536870912  - 
 *  (31) 1073741824 - 
 */

enum GameEvent {
    X_BORDERCOLLISION,
    Y_BORDERCOLLISION,
};

enum GameAction {
    SETVAR,         // set a variable
                    //  - variable name
                    //  - new value to set
    INCVAR,         // increment a variable
                    //  - variable name
                    //  - value by which to increment
    TOGGLE,         // toggle a flag
                    //  - name of the flag
    BOUNCE_X,       // reverse X velocity, as if the object "bounced" off a surface
    BOUNCE_Y,       // reverse Y velocity, as if the object "bounced" off a surface
};

struct ActionList {
    GameAction type;
    std::string id;
    double value;
};

#endif