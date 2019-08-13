#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>
struct Camera{

    std::string name = "NoName";
    glm::vec3 direction = {0,0,-1};
    glm::vec3 position = {0,0,0};
    glm::vec3 upVector = {0,1,0};
    unsigned int fov = 60;
    glm::mat4x4 transformation =  glm::mat4x4{
            glm::vec4{1.0f,0.0f,0.0f,0.0f},
            glm::vec4{0.0f,1.0f,0.0f,0.0f},
            glm::vec4{0.0f,0.0f,1.0f,0.0f},
            glm::vec4{0.0f,0.0f,0.0f,1.0f}};
};

#endif //RAYTRACER_CAMERA_HPP
