#ifndef RAYTRACER_HITPOINT_HPP
#define RAYTRACER_HITPOINT_HPP

#include <glm/vec3.hpp>
#include <iostream>
#include "color.hpp"

struct Hitpoint {

    bool hit = false;
    float distance = MAXFLOAT;
    std::string name = "miss";
    std::shared_ptr<Material> material = nullptr;
    glm::vec3 direction;
    glm::vec3 hitpoint{MAXFLOAT, MAXFLOAT, MAXFLOAT};
    glm::vec3 normal{0, 0, 0};

    friend std::ostream& operator<<(std::ostream & os, Hitpoint const& hitpoint){
        os << "name:        " << hitpoint.name << "\nobject type: Hitpoint\n" << 
        "hit:         " << hitpoint.hit << std::endl;
        if (hitpoint.hit == false){
            os << "--------------------" << std::endl;
            return os;
        } else {
            os << "distance:    " << hitpoint.distance << "\ndirection:   x[" << 
            hitpoint.direction.x << "] y[" << hitpoint.direction.y <<"] z[" << 
            hitpoint.direction.z << "]\nhitpoint:    x[" << hitpoint.hitpoint.x <<
            "] y[" << hitpoint.hitpoint.y << "] z[" << hitpoint.hitpoint.z << 
            "]\nnormal:      x[" << hitpoint.normal.x << "] y[" << hitpoint.normal.y <<
            "] z[" << hitpoint.normal.z << "]\nmaterial:    " << hitpoint.material->name <<
            "\n--------------------" << std::endl;
            return os;  
        }

    }
};

#endif //RAYTRACER_HITPOINT_HPP
