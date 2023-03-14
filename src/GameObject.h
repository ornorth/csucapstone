#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include "Structs.h"

/* The basic outline of a game object
 * Can be inherited by more specific objects
 */

class GameObject {
    private:
        std::string name;
        Shape shape;
    public:
        Color color;

        // Position
        double dim_x;
        double dim_y;
        double pos_x;
        double pos_y;
        double angle;

        // Movement
        double vel_x;
        double vel_y;
        double acc_x;
        double acc_y;

        double vel_ang;
        double acc_ang;

        // User-Defined Variables
        double user_double1;
        double user_double2;
        double user_double3;

    private:
        uint16_t flags; 

    public:
        GameObject(const std::string& name,
                   Shape shape,
                   const Color& color,
                   int dim_x, int dim_y,
                   int pos_x, int pos_y,
                   double angle);
        
        // Getters for private values
        std::string getName() { return name; }
        Shape getShape() { return shape; }

        void drawPixel(SDL_Renderer *Renderer, int x, int y);
    
    public:
        // Update flags
        void setFlag(ObjectFlag flag);
        void clearFlag(ObjectFlag flag);
        bool checkFlag(ObjectFlag flag);
};


#endif