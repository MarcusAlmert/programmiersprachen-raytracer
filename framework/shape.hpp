#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP

#include <memory>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

class Shape {
public:
    Shape();
    Shape(std::string const &name_, std::shared_ptr<Material> const mat_ptr);

    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual std::ostream &print(std::ostream &os) const;
    virtual Hitpoint intersect(Ray const &ray) const = 0;
    virtual ~Shape();

    std::shared_ptr<Material> material_;
    std::string name_ = "No_name";

};

std::ostream &operator<<(std::ostream &os, Shape const &s);


#endif //RAYTRACER_SHAPE_HPP
