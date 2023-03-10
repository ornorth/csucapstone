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

        std::map<EventList, std::vector<ActionList>, EventListComp> object_events;

        std::unordered_map<KeyCode, std::vector<ActionList>> keydown_events;
        std::unordered_map<KeyCode, std::vector<ActionList>> keyup_events;
        std::unordered_map<KeyCode, std::vector<ActionList>> keyheld_events;
        //index using enum KeyCode: true=pressed, false=not
        bool keyStates[KeyCode::MAX_KEYCODE];

        // Collision stuff (oh boy)
        std::map<StrPair, std::vector<ActionList>, StrPairComp> collision_events;

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

        // OBJECT EVENTS
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute source_att, const std::string& source_obj);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, ObjectAttribute source_att, const std::string& source_obj);
        
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute affected_att, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute affected_att, ObjectAttribute source_att, const std::string& source_obj);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, ObjectAttribute affected_att, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, ObjectAttribute affected_att, ObjectAttribute source_att, const std::string& source_obj);
        
        // The functions that modify color based on another object's color are implicit in the functions above
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectAttribute affected_att, Color color);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, ObjectAttribute affected_att, Color color);
        
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectFlag flag);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, ObjectFlag flag);
        
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, ObjectFlag flag, bool value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, GameAction action, const std::string& affected_obj, ObjectFlag flag, bool value);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute source_att, const std::string& source_obj);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, ObjectAttribute source_att, const std::string& source_obj);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute affected_att, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute affected_att, ObjectAttribute source_att, const std::string& source_obj);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, ObjectAttribute affected_att, double value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, ObjectAttribute affected_att, ObjectAttribute source_att, const std::string& source_obj);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectAttribute affected_att, Color color);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, ObjectAttribute affected_att, Color color);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectFlag flag);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, ObjectFlag flag);

        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, ObjectFlag flag, bool value);
        bool addObjectEvent(const std::string& obj_name, GameEvent event, ObjectAttribute effector_att, double effector_value, GameAction action, const std::string& affected_obj, ObjectFlag flag, bool value);

        // KEY EVENTS
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name);

        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, double value);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute source_att, const std::string& source_obj);

        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute affected_att, double value);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute affected_att, ObjectAttribute source_att, const std::string& source_obj);

        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectAttribute affected_att, Color color);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectFlag flag);
        bool addKeyEvent(KeyCode key, KeyPressType type, GameAction action, const std::string& obj_name, ObjectFlag flag, bool value);

        // COLLISION EVENTS
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name);

        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, double value);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute source_att, const std::string& source_obj);

        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute affected_att, double value);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute affected_att, ObjectAttribute source_att, const std::string& source_obj);

        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectAttribute affected_att, Color color);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectFlag flag);
        bool addCollisionEvent(const std::string& obj_1, const std::string& obj_2, GameAction action, const std::string& obj_name, ObjectFlag flag, bool value);

    private:
        GameObject* getGameObject(const std::string& name);
        int getGameObjectIndex(const std::string& name);
        double* getObjectAttribute(GameObject* GOptr, ObjectAttribute attribute);

        void checkObjectEvents();
        bool collisionOccurred(const StrPair& colliders);

        void runEvents(std::vector<ActionList>& events, GameObject* GOptr = nullptr);

        
        bool OnInit(const std::string& window_name);
        void OnEvent();
        void OnLoop();
        void OnRender();
        void OnCleanup();
};

#endif