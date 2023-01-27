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
        CApp(int window_width, int window_height, int r = 255, int g = 255, int b = 255, int a = 255);
        int Execute();

    private:
        bool OnInit();
        void OnEvent(SDL_Event& event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
};

#endif