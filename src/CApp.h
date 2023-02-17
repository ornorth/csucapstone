#ifndef CAPP_H
#define CAPP_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "Structs.h"
#include "GameObject.h"

/* This class handles the game loop
 * All info about the game ends up here
 */

class CApp {
    private:
        // Major SDL objects
        SDL_Window* Main_Window;
        SDL_Renderer* Renderer;
        
        // Metadata
        bool running;
        int window_width;
        int window_height;
        std::vector<GameObject> obj_list;

        // Colors
        Color bg_color;

    public:
        CApp(int window_width, int window_height, const Color& color);
        int Execute();

        bool addGameObject(const std::string& name,
                           Shape shape=Shape::RECTANGLE,
                           const Color& color = {255, 0, 0, 255},
                           int dim_x = 50, int dim_y = 50,
                           int pos_x = 100, int pos_y = 100,
                           double angle = 0);

        // Update Game Object attributes directly
        bool setObjectValue(const std::string& obj_name, ObjectAttribute attribute, double value);

        // EVENTS
        bool addEvent(const std::string& obj_name, GameEvent event, GameAction action);
        bool addEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& name);
        bool addEvent(const std::string& obj_name, GameEvent event, GameAction action, double value);
        bool addEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& name, double value);
        bool addEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute att, double value);

    private:
        int getGameObject(const std::string& name);
        double* getObjectAttribute(GameObject* GOptr, ObjectAttribute attribute);

        void runGeneralEvents(GameObject* GOptr);
        
        bool OnInit();
        void OnEvent(SDL_Event& event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
};

// void addEvent(GameObject, event, action)




#endif