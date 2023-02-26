#ifndef CAPP_H
#define CAPP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
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

        std::unordered_map<KeyCode, std::vector<KeyActionList>> keydown_events;
        std::unordered_map<KeyCode, std::vector<KeyActionList>> keyup_events;
        std::unordered_map<KeyCode, std::vector<KeyActionList>> keyheld_events;
        //index using enum KeyCode: true=pressed, false=not
        bool keyStates[KeyCode::MAX_KEYCODE];

        // Collision stuff (oh boy)
        std::map<std::pair<std::string, std::string>, std::vector<KeyActionList>, StrPairComp> collision_events;

        // Colors
        Color bg_color;

    public:
        CApp(int window_width, int window_height, const Color& color);
        int Execute(const std::string& window_name);

        bool addGameObject(const std::string& name,
                           Shape shape=Shape::RECTANGLE,
                           const Color& color = {255, 0, 0, 255},
                           int dim_x = 50, int dim_y = 50,
                           int pos_x = 100, int pos_y = 100,
                           double angle = 0);

        // Update Game Object attributes directly
        bool setObjectValue(const std::string& obj_name, ObjectAttribute attribute, double value);

        // EVENTS
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& name);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& name, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute att, double value);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& name);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& name, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute att, double value);

        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action); // for generic events: quit, pause(?)
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, const std::string& name);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, double value);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, const std::string& name, double value);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute att, double value);

        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, const std::string& name);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, double value);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, const std::string& name, double value);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute att, double value);

    private:
        int getGameObject(const std::string& name);
        double* getObjectAttribute(GameObject* GOptr, ObjectAttribute attribute);

        void checkObjectEvents(GameObject* GOptr);
        void runObjectEvent(GameObject* GOptr, std::vector<ActionList>& events);
        
        void runKeyEvents(std::vector<KeyActionList>& events);

        bool collisionOccurred(const std::pair<std::string, std::string>& colliders);
        //void runCollisionEvents(std::vector<KeyActionList>& events);
        
        bool OnInit(const std::string& window_name);
        void OnEvent();
        void OnLoop();
        void OnRender();
        void OnCleanup();
};

#endif