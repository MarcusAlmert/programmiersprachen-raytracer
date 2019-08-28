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
    Ray transformedRay_ = transformRay(ray,world_transformation_inv);
    Hitpoint hitp;
    float distance;
    glm::vec3 cutpoint;
    glm::vec3 normal;
    glm::vec4 trans_middlePoint_ = glm::vec4{middlePoint_,1 } * world_transformation_;
   // bool hitted = glm::intersectRaySphere(transformedRay_.origin_,
     //                                     glm::normalize(transformedRay_.direction_), {trans_middlePoint_.x,trans_middlePoint_.y,trans_middlePoint_.z}, pow(radius_, 2), distance);

    bool hitted = glm::intersectRaySphere(transformedRay_.origin_,glm::normalize(transformedRay_.direction_),middlePoint_,radius_, cutpoint, normal);
    if (hitted) {
        float hitx = ray.origin_.x + distance * ray.direction_.x;
        float hity = ray.origin_.y + distance * ray.direction_.y;
        float hitz = ray.origin_.z + distance * ray.direction_.z;
        glm::vec4 trans_normal = glm::normalize(glm::transpose(world_transformation_inv) * glm::vec4(normal,0));
        glm::vec4 trans_cutpoint = world_transformation_ * glm::vec4(cutpoint,1);
        normal = {trans_normal.x, trans_normal.y, trans_normal.z};
        cutpoint = {trans_cutpoint.x, trans_cutpoint.y, trans_cutpoint.z};
        distance = glm::length(cutpoint-ray.origin_);
        hitp = {true, distance, name_, material_, ray.direction_, cutpoint, normal};
    }
    return hitp;
}