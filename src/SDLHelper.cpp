#include <cmath>
#include "SDLHelper.h"

#define PI 3.14159265

void drawPixel(SDL_Renderer *Renderer,
               int x_center, int y_center,
               int x_offset, int y_offset,
               int x_limit, int y_limit,
               int angle)
{
    double convAngle = ((double)angle) * PI / 180.0;
    SDL_RenderDrawPoint(Renderer, 
                        x_center + (x_offset*std::cos(convAngle)) - (y_offset*std::sin(convAngle)),
                        y_center + (x_offset*std::sin(convAngle)) + (y_offset*std::cos(convAngle)));
    if (x_offset < x_limit + 1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            x_center + (x_offset*std::cos(convAngle)) - (y_offset*std::sin(convAngle)) + 1,
                            y_center + (x_offset*std::sin(convAngle)) + (y_offset*std::cos(convAngle)));
    }
    if (x_offset > x_limit * -1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            x_center + (x_offset*std::cos(convAngle)) - (y_offset*std::sin(convAngle)) - 1,
                            y_center + (x_offset*std::sin(convAngle)) + (y_offset*std::cos(convAngle)));
    }
    if (y_offset < y_limit + 1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            x_center + (x_offset*std::cos(convAngle)) - (y_offset*std::sin(convAngle)),
                            y_center + (x_offset*std::sin(convAngle)) + (y_offset*std::cos(convAngle)) + 1);
    }
    if (y_offset > y_limit * -1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            x_center + (x_offset*std::cos(convAngle)) - (y_offset*std::sin(convAngle)),
                            y_center + (x_offset*std::sin(convAngle)) + (y_offset*std::cos(convAngle)) - 1);
    }
}