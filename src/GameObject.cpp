#include "GameObject.h"

GameObject::GameObject(const std::string& obj_name,
                       Shape obj_shape,
                       const Color& obj_color,
                       int dim_x, int dim_y,
                       int pos_x, int pos_y)
                     : obj_name(obj_name),
                       obj_shape(obj_shape),
                       obj_color(obj_color),
                       dim_x(dim_x), dim_y(dim_y),
                       pos_x(pos_x), pos_y(pos_y),
                       obj_flags(0)
{ }
