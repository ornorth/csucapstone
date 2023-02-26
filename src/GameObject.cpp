#include <cmath>
#include "GameObject.h"

#define PI 3.14159265

GameObject::GameObject(const std::string& name, Shape shape, const Color& color,
                       int dim_x, int dim_y, int pos_x, int pos_y, double angle)
                     : name(name), shape(shape), color(color),
                       dim_x(dim_x), dim_y(dim_y), pos_x(pos_x), pos_y(pos_y), angle(angle), 

                       vel_x(0), vel_y(0), acc_x(0), acc_y(0),
                       vel_ang(0), acc_ang(0),

                       user_double1(0), user_double2(0), user_double3(0),
                       
                       flags(0)
{ }

void GameObject::drawPixel(SDL_Renderer *Renderer, int x, int y)
{
    double convAngle = ((double)angle) * PI / 180.0;
    int convX = pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle));
    int convY = pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle));

    SDL_Point points[5];
    int count = 0;
    
    points[count++] = {convX, convY};
    if (x < dim_x/2      - 1)
        points[count++] = {convX + 1, convY};
    if (x > dim_x/2 * -1 + 1)
        points[count++] = {convX - 1, convY};
    if (y < dim_y/2      - 1)
        points[count++] = {convX, convY + 1};
    if (y > dim_y/2 * -1 + 1)
        points[count++] = {convX, convY - 1};
    
    SDL_RenderDrawPoints(Renderer, points, count);
}

void GameObject::setFlag(ObjectFlag flag)
{
    flags = flags | flag;
}
void GameObject::clearFlag(ObjectFlag flag)
{
    //flags -= flag;
    flags = flags & (0xFFFF-flag);
}
bool GameObject::checkFlag(ObjectFlag flag)
{
    return flags & flag;
}
void GameObject::addEvent(EventList event, GameAction action, const std::string& name, double value)
{
    event_list[event].push_back({action, name, value});
}
void GameObject::addEvent(EventList event, GameAction action, ObjectAttribute att, double value)
{
    event_list[event].push_back({action, "NULL", value, att});
}

void GameObject::getCorners(double* Xcorners, double* Ycorners)
{
    double convAngle = ((double)angle) * PI / 180.0;
    double x = dim_x/2;
    double y = dim_y/2;

    switch(shape)
    {
    // int convX = pos_x + (x*std::cos(convAngle)) - (y*std::sin(convAngle));
    // int convY = pos_y + (x*std::sin(convAngle)) + (y*std::cos(convAngle));
        case Shape::RECTANGLE:
        {
            Xcorners[0] = pos_x + ( x*std::cos(convAngle)) - ( y*std::sin(convAngle));
            Ycorners[0] = pos_y + ( x*std::sin(convAngle)) - ((y*-1)*std::cos(convAngle));

            Xcorners[1] = pos_x + ( x*std::cos(convAngle)) - ((y*-1)*std::sin(convAngle));
            Ycorners[1] = pos_y + ( x*std::sin(convAngle)) - ( y*std::cos(convAngle));

            Xcorners[2] = pos_x + ((x*-1)*std::cos(convAngle)) - ((y*-1)*std::sin(convAngle));
            Ycorners[2] = pos_y + ((x*-1)*std::sin(convAngle)) - ( y*std::cos(convAngle));

            Xcorners[3] = pos_x + ((x*-1)*std::cos(convAngle)) - ( y*std::sin(convAngle));
            Ycorners[3] = pos_y + ((x*-1)*std::sin(convAngle)) - ((y*-1)*std::cos(convAngle));
            break;
        }
        case Shape::CIRCLE:
        {
            // For now, just pretend a circle is a rectangle
            Xcorners[0] = pos_x + ( x*std::cos(convAngle)) - ( y*std::sin(convAngle));
            Ycorners[0] = pos_y + ( x*std::sin(convAngle)) - ((y*-1)*std::cos(convAngle));

            Xcorners[1] = pos_x + ( x*std::cos(convAngle)) - ((y*-1)*std::sin(convAngle));
            Ycorners[1] = pos_y + ( x*std::sin(convAngle)) - ( y*std::cos(convAngle));

            Xcorners[2] = pos_x + ((x*-1)*std::cos(convAngle)) - ((y*-1)*std::sin(convAngle));
            Ycorners[2] = pos_y + ((x*-1)*std::sin(convAngle)) - ( y*std::cos(convAngle));

            Xcorners[3] = pos_x + ((x*-1)*std::cos(convAngle)) - ( y*std::sin(convAngle));
            Ycorners[3] = pos_y + ((x*-1)*std::sin(convAngle)) - ((y*-1)*std::cos(convAngle));
            break;
        }
        case Shape::TRIANGLE:
        {
            Xcorners[0] = pos_x + ( x*std::cos(convAngle)) - ( y*std::sin(convAngle));
            Ycorners[0] = pos_y + ( x*std::sin(convAngle)) - ((y*-1)*std::cos(convAngle));

            Xcorners[1] = pos_x - ((y*-1)*std::sin(convAngle));
            Ycorners[1] = pos_y - ( y*std::cos(convAngle));

            Xcorners[2] = Xcorners[1];//pos_x + ((x*-1)*std::cos(convAngle)) - ((y*-1)*std::sin(convAngle));
            Ycorners[2] = Ycorners[1];//pos_y + ((x*-1)*std::sin(convAngle)) - ( y*std::cos(convAngle));

            Xcorners[3] = pos_x + ((x*-1)*std::cos(convAngle)) - ( y*std::sin(convAngle));
            Ycorners[3] = pos_y + ((x*-1)*std::sin(convAngle)) - ((y*-1)*std::cos(convAngle));



            // Xcorners[0] = pos_x + ( x*std::cos(convAngle)) - ( y*std::sin(convAngle));
            // Ycorners[0] = pos_y + ( x*std::sin(convAngle)) - ( y*std::cos(convAngle));
            
            // Xcorners[1] = pos_x + ( 0 ) - (-y*std::sin(convAngle));
            // Ycorners[1] = pos_y + ( 0 ) - (-y*std::cos(convAngle));
            
            // Xcorners[2] = pos_x + (-x*std::cos(convAngle)) - ( y*std::sin(convAngle));
            // Ycorners[2] = pos_y + (-x*std::sin(convAngle)) - ( y*std::cos(convAngle));
            
            // Xcorners[3] = Xcorners[1];
            // Ycorners[3] = Ycorners[1];
            break;
        }
    }
}