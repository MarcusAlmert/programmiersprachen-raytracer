#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include <glm/glm.hpp>

struct Ray {
    glm::vec3 origin_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction_ = {0.0f, 0.0f, -1.0f};

    friend Ray transformRay(Ray const &ray, glm::mat4 const &mat);
};

#endif //RAYTRACER_RAY_HPP
