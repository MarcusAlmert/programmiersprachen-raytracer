#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP

#include <glm-0.9.5.3/glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
private:
    glm::vec3 min;
    glm::vec3 max;

public:

};

#endif //RAYTRACER_BOX_HPP
