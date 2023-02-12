#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <unordered_map>
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
        int dim_x;
        int dim_y;
        int pos_x;
        int pos_y;
        double angle;

        // Movement
        double vel_x;
        double vel_y;
        double acc_x;
        double acc_y;

        double vel_ang;
        double acc_ang;

    private:
        uint32_t flags; 

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

        std::unordered_map<GameEvent, std::vector<ActionList>> event_list;
        //std::unordered_map<string, std::vector<ActionList>> collision_event_list;
        //std::unordered_map<SDL_Keypress, std::vector<ActionList>> key_event_list;

        void addEvent(GameEvent event, GameAction action, const std::string& name);
        void addEvent(GameEvent event, GameAction action, double value);
        void addEvent(GameEvent event, GameAction action, const std::string& name, double value);
        //void addCollisionEvent()
        //void addKeyEvent()

        void runEventList();

};


#endif