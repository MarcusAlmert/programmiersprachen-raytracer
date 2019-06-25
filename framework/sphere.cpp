#include <math.h>
#include <iostream>
#include <glm-0.9.5.3/glm/gtx/intersect.hpp>
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

Sphere::~Sphere() {
    std::cout << "Sphere destructor used" << std::endl;
}

float Sphere::area() const {
    return (M_PI * 4 * pow(radius, 2));
}

float Sphere::volume() const {
    return (4.0f / 3.0f) * M_PI * pow(radius, 3);
}

std::ostream &Sphere::print(std::ostream &os) const {
    return os << "Name: " << name << " (Sphere)" << std::endl
              << "Color: " << "[" << color.r << ", " << color.g << ", " << color.b << "]" << std::endl
              << "Middle Point: " << "[" << middlePoint.x << ", " << middlePoint.y << "]" << std::endl
              << "Radius: " << radius << std::endl;
}

Hitpoint Sphere::intersect(Ray const &r) const {
    Ray ray_ = r;
    Hitpoint hitp;
    float distance;
    bool hitted = glm::intersectRaySphere(ray_.origin,
                                          glm::normalize(ray_.direction), middlePoint, pow(radius, 2), distance);
    if (hitted) {
        hitp = {true, distance, name, color, ray_.direction};
    }
    return hitp;
}