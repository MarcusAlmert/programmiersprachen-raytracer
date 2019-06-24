#ifndef RAYTRACER_HITPOINT_HPP
#define RAYTRACER_HITPOINT_HPP

#include "color.hpp"
#include <glm/vec3.hpp>

struct Hitpoint {
    bool hit = false;
    float distance = MAXFLOAT;
    std::string name = "miss";
    Color color = {0, 0, 0};
    glm::vec3 direction;

    Hitpoint() {
        hit = false;
        distance = MAXFLOAT;
        name = "miss";
        color = {0, 0, 0};
        direction = {0, 0, 0};
    }

    Hitpoint(bool hit_, float d, std::string const &name_, Color const &color_, glm::vec3 const &dir) {
        hit = hit_;
        distance = d;
        name = name_;
        color = color_;
        direction = dir;
    }
};

#endif //RAYTRACER_HITPOINT_HPP
