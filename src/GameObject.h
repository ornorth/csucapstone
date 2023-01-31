#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include "Structs.h"

/* The basic outline of a game object
 * Can be inherited by more specific objects
 */

class GameObject {
    public:
        std::string obj_name;
        Shape obj_shape;
        Color obj_color;
        int dim_x;
        int dim_y;
        int pos_x;
        int pos_y;
        uint32_t obj_flags;
    public:
        GameObject(const std::string& obj_name,
                   Shape obj_shape,
                   const Color& obj_color,
                   int dim_x, int dim_y,
                   int pos_x, int pos_y);

};

/*  obj_flags
 *  (1)  0          - 
 *  (2)  1          - 
 *  (3)  2          - 
 *  (4)  4          - 
 *  (5)  8          - 
 *  (6)  16         - 
 *  (7)  32         - 
 *  (8)  64         - 
 *  (9)  128        - 
 *  (10) 256        - 
 *  (11) 512        - 
 *  (12) 1024       - 
 *  (13) 2048       - 
 *  (14) 4096       - 
 *  (15) 8192       - 
 *  (16) 16384      - 
 *  (17) 32768      - 
 *  (18) 65536      - 
 *  (19) 131072     - 
 *  (20) 262144     - 
 *  (21) 524288     - 
 *  (22) 1048576    - 
 *  (23) 2097152    - 
 *  (24) 4194304    - 
 *  (25) 8388608    - 
 *  (26) 16777216   - 
 *  (27) 33554432   - 
 *  (28) 67108864   - 
 *  (29) 134217728  - 
 *  (30) 268435456  - 
 *  (31) 536870912  - 
 *  (32) 1073741824 - 
 */

#endif