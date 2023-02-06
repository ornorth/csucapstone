#include <cmath>
#include "GameObject.h"

#define PI 3.14159265

GameObject::GameObject(const std::string& obj_name,
                       Shape obj_shape,
                       const Color& obj_color,
                       int dim_x, int dim_y,
                       int pos_x, int pos_y,
                       int angle)
                     : obj_name(obj_name),
                       obj_shape(obj_shape),
                       obj_color(obj_color),
                       dim_x(dim_x), dim_y(dim_y),
                       pos_x(pos_x), pos_y(pos_y),
                       angle(angle), obj_flags(0)
{ }

void GameObject::drawPixel(SDL_Renderer *Renderer, int x, int y)
{
    double convAngle = ((double)angle) * PI / 180.0;
    SDL_RenderDrawPoint(Renderer, 
                        pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle)),
                        pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle)));
    if (x < dim_x/2 + 1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle)) + 1,
                            pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle)));
    }
    if (x > dim_x/2 * -1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle)) - 1,
                            pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle)));
    }
    if (y < dim_y/2 + 1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle)),
                            pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle)) + 1);
    }
    if (y > dim_y/2 * -1)
    {
        SDL_RenderDrawPoint(Renderer, 
                            pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle)),
                            pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle)) - 1);
    }
}
