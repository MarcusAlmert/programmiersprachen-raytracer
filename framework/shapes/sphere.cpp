#include <math.h>
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include "sphere.hpp"


Sphere::Sphere() {
    radius_ = 0;
}

Sphere::Sphere(glm::vec3 const &mid, float rad) {
    middlePoint_ = mid;
    if (rad < 0) {
    }
    radius_ = abs(rad);
}

Sphere::Sphere(glm::vec3 const &mid, float rad, std::string const &name, std::shared_ptr<Material> const mat_ptr) :
        middlePoint_{mid}, Shape{name, mat_ptr}, radius_{rad} {
}

Sphere::~Sphere() {
}

float Sphere::area() const {
    return (M_PI * 4 * pow(radius_, 2));
}

float Sphere::volume() const {
    return (4.0f / 3.0f) * M_PI * pow(radius_, 3);
}

std::ostream &Sphere::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name:         " << name_ << " (Sphere)" << std::endl
                  << "Material:     " << "[" << material_->name_ << "]" << std::endl
                  << "Middle Point: " << "[" << middlePoint_.x << ", " << middlePoint_.y << ", " << middlePoint_.z
                  << "]" << std::endl
                  << "Radius:       " << radius_ << std::endl << "--------------------" << std::endl;
    } else {
        return os << "Name:         " << name_ << " (Sphere)" << std::endl
                  << "Material:     " << "[" << "No Material" << "]" << std::endl
                  << "Middle Point: " << "[" << middlePoint_.x << ", " << middlePoint_.y << ", " << middlePoint_.z
                  << "]" << std::endl
                  << "Radius:       " << radius_ << std::endl << "--------------------" << std::endl;
    }

}

Hitpoint Sphere::intersect(Ray const &ray) const {
    Ray ray_ = ray;
    Hitpoint hitp;
    float distance;
    bool hitted = glm::intersectRaySphere(ray_.origin_,
                                          glm::normalize(ray_.direction_), middlePoint_, pow(radius_, 2), distance);
    if (hitted) {
        float hitx = ray.origin_.x + distance * ray.direction_.x;
        float hity = ray.origin_.y + distance * ray.direction_.y;
        float hitz = ray.origin_.z + distance * ray.direction_.z;
        glm::vec3 normal = glm::normalize(glm::vec3{hitx, hity, hitz} - middlePoint_);
        hitp = {true, distance, name_, material_, ray_.direction_, {hitx, hity, hitz}, normal};
    }
    return hitp;
}