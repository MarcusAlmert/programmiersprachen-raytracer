#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {

private:

    glm::vec3 middlePoint;
    float radius;

public:
    Sphere();

    Sphere(glm::vec3 const &mid, float rad);

    virtual float area() const override;

    virtual float volume() const override;
};

#endif //RAYTRACER_SPHERE_HPP
