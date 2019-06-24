#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP

#include "color.hpp"

class Shape{
public:
    virtual float area() const = 0;

    virtual float volume() const = 0;

    Color color = {0.5, 0.5, 0.5};

    std::string name = "No_Name";

    virtual std::ostream &print(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, Shape const &s);



#endif //RAYTRACER_SHAPE_HPP
