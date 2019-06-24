#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP

#include "color.hpp"

class Shape{
public:
    Shape();

    Shape(std::string const &name_, Color const &color_);

    virtual float area() const = 0;

    virtual float volume() const = 0;

    virtual std::ostream &print(std::ostream &os) const = 0;

protected:
    Color color = {0.5, 0.5, 0.5};

    std::string name = "No_name";

};

std::ostream &operator<<(std::ostream &os, Shape const &s);



#endif //RAYTRACER_SHAPE_HPP
