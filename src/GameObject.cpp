#include <cmath>
#include "GameObject.h"

#define PI 3.14159265

GameObject::GameObject(const std::string& name, Shape shape, const Color& color,
                       int dim_x, int dim_y, int pos_x, int pos_y, double angle)
                     : name(name), shape(shape), color(color),
                       dim_x(dim_x), dim_y(dim_y), pos_x(pos_x), pos_y(pos_y), angle(angle), 

                       vel_x(0), vel_y(0), acc_x(0), acc_y(0),
                       vel_ang(0), acc_ang(0),
                       
                       flags(0)
{
    // FOR DEBUGGING PURPOSES: REMOVE LATER
    if (name[0] == 'l') setFlag(ObjectFlag::STATIC);
}

void GameObject::drawPixel(SDL_Renderer *Renderer, int x, int y)
{
    double convAngle = ((double)angle) * PI / 180.0;
    int convX = pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle));
    int convY = pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle));

    SDL_RenderDrawPoint(Renderer, convX, convY);
    if ((int)angle % 90 != 0)
    {
        if (x < dim_x/2 + 1)
            SDL_RenderDrawPoint(Renderer, convX + 1, convY    );
        if (x > dim_x/2 * -1)
            SDL_RenderDrawPoint(Renderer, convX - 1, convY    );
        if (y < dim_y/2 + 1)
            SDL_RenderDrawPoint(Renderer, convX,     convY + 1);
        if (y > dim_y/2 * -1)
            SDL_RenderDrawPoint(Renderer, convX,     convY - 1);
    }
}

void GameObject::setFlag(ObjectFlag flag)
{
    flags = flags | flag;
}

void GameObject::clearFlag(ObjectFlag flag)
{
    flags = flags & (0xFFFFFFFF-flag);
}

bool GameObject::checkFlag(ObjectFlag flag)
{
    return flags & flag;
}