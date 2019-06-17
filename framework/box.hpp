#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP

#include <glm-0.9.5.3/glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
private:
    glm::vec3 min;
    glm::vec3 max;

public:
    Box();

    Box(glm::vec3 const &min_, glm::vec3 const &max_);

    virtual float area() const override;

    virtual float volume() const override;
};

#endif //RAYTRACER_BOX_HPP
