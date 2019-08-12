#ifndef RAYTRACER_HITPOINT_HPP
#define RAYTRACER_HITPOINT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Hitpoint {
    bool hit = false;
    float distance = MAXFLOAT;
    std::string name = "miss";
    std::shared_ptr<Material> material = nullptr;
    glm::vec3 direction;
    glm::vec3 hitpoint{MAXFLOAT, MAXFLOAT, MAXFLOAT};
    glm::vec3 normal{0, 0, 0};
};

#endif //RAYTRACER_HITPOINT_HPP
