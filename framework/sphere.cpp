#include <math.h>
#include <iostream>
#include "sphere.hpp"

Sphere::Sphere() {
    middlePoint = {0, 0, 0};
    radius = 0;
}

Sphere::Sphere(glm::vec3 const &mid, float rad) {
    middlePoint = mid;
    if (rad < 0) {
        std::cout << "radius was made positive" << std::endl;
    }
    radius = abs(rad);
}

Sphere::Sphere(glm::vec3 const &mid, float rad, std::string const &name_, Color const &color_) {
    middlePoint = mid;
    if (rad < 0) {
        std::cout << "radius was made positive" << std::endl;
    }
    radius = abs(rad);
    name = name_;
    color = color_;
}

float Sphere::area() const {
    return (M_PI * 4 * pow(radius, 2));
}

float Sphere::volume() const {
    return (4.0f / 3.0f) * M_PI * pow(radius, 3);
}

std::ostream &Sphere::print(std::ostream &os) const {
    return std::cout << ""
}