#ifndef RAYTRACER_HITPOINT_HPP
#define RAYTRACER_HITPOINT_HPP

#include <glm/vec3.hpp>
#include <iostream>
#include "color.hpp"

struct Hitpoint {

    bool hit_ = false;
    float distance_ = MAXFLOAT;
    std::string name_ = "miss";
    std::shared_ptr<Material> material_ = nullptr;
    glm::vec3 direction_;
    glm::vec3 hitpoint_{MAXFLOAT, MAXFLOAT, MAXFLOAT};
    glm::vec3 normal_{0, 0, 0};

    friend std::ostream &operator<<(std::ostream &os, Hitpoint const &hitpoint) {
        os << "name:        " << hitpoint.name_ << "\nobject type: Hitpoint\n" <<
           "hit:         " << hitpoint.hit_ << std::endl;
        if (hitpoint.hit_ == false) {
            os << "--------------------" << std::endl;
            return os;
        } else {
            std::shared_ptr<Material> check = nullptr;
            os << "distance:    " << hitpoint.distance_ << "\ndirection:   x[" <<
               hitpoint.direction_.x << "] y[" << hitpoint.direction_.y << "] z[" <<
               hitpoint.direction_.z << "]\nhitpoint:    x[" << hitpoint.hitpoint_.x <<
               "] y[" << hitpoint.hitpoint_.y << "] z[" << hitpoint.hitpoint_.z <<
               "]\nnormal:      x[" << hitpoint.normal_.x << "] y[" << hitpoint.normal_.y <<
               "] z[" << hitpoint.normal_.z << "]\nmaterial:    ";
            if (hitpoint.material_ == nullptr){
                os << "NoMaterial";
            } else {
                os << hitpoint.material_->name_;
            }
            os  << "\n--------------------" << std::endl;
            return os;
        }

    }
};

#endif //RAYTRACER_HITPOINT_HPP
