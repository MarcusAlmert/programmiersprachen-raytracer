#include <math.h>
#include <iostream>
#include <glm-0.9.5.3/glm/gtx/intersect.hpp>
#include "sphere.hpp"


Sphere::Sphere() {
    radius = 0;
}

Sphere::Sphere(glm::vec3 const &mid, float rad) {
    middlePoint = mid;
    if (rad < 0) {
    }
    radius = abs(rad);
}

Sphere::Sphere(glm::vec3 const &mid, float rad, std::string const &name_, std::shared_ptr<Material> const mat_ptr) :
        middlePoint{mid}, Shape{name_, mat_ptr}, radius{rad} {
}

Sphere::~Sphere() {
}

float Sphere::area() const {
    return (M_PI * 4 * pow(radius, 2));
}

float Sphere::volume() const {
    return (4.0f / 3.0f) * M_PI * pow(radius, 3);
}

std::ostream &Sphere::print(std::ostream &os) const {
    if (material != nullptr) {
        return os << "Name: " << name << " (Sphere)" << std::endl
                  << "Material: " << "[" << material->name  << "]" << std::endl
                  << "Middle Point: " << "[" << middlePoint.x << ", " << middlePoint.y << ", " << middlePoint.z << "]" << std::endl
                  << "Radius: " << radius << std::endl << "--------------------" << std::endl;
    } else {
        return os << "Name: " << name << " (Sphere)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Middle Point: " << "[" << middlePoint.x << ", " << middlePoint.y << ", " << middlePoint.z << "]" << std::endl
                  << "Radius: " << radius << std::endl << "--------------------" << std::endl;
    }

}

Hitpoint Sphere::intersect(Ray const &ray) const {
    Ray ray_ = ray;
    Hitpoint hitp;
    float distance;
    bool hitted = glm::intersectRaySphere(ray_.origin,
                                          glm::normalize(ray_.direction), middlePoint, pow(radius, 2), distance);
    if (hitted) {
        float hitx = ray.origin.x + distance * ray.direction.x;
        float hity = ray.origin.y + distance * ray.direction.y;
        float hitz = ray.origin.z + distance * ray.direction.z;
        glm::vec3 normal = glm::normalize(glm::vec3{hitx, hity, hitz} - middlePoint);
        hitp = {true, distance, name, material, ray_.direction, {hitx, hity, hitz}, normal};
    }
    return hitp;
}