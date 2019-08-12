#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>
#include "color.hpp"
#include "iostream"

struct Light{

    std::string name_ = "NoName";
    glm::vec3 position_ = {0,0,0};
    Color color_ = {0,0,0};
    float brightness_ = 1;

    friend std::ostream& operator<<(std::ostream& os, Light const& light){
        os << "name: " << light.name_ << "\nobject type: Light\n" <<
        "brightness: " << light.brightness_ << "\nposition:   x[" << 
        light.position_.x << "] y[" << light.position_.y <<"] z[" 
        << light.position_.z << "]\n" << "color:      r[" << light.color_.r <<
        "] g[" << light.color_.g << "] b[" << light.color_.b << "]\n" << 
        "--------------------" << std::endl;
    return os;
}

};
#endif