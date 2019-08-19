#include "triangle.hpp"
#include <cmath>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "hitpoint.hpp"

Triangle::Triangle() {
    p1_ = {0, 0, 0};
    p2_ = {1, 1, 1};
    p3_ = {-1, -1, -1};
}

Triangle::Triangle(glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3) {
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
}

Triangle::Triangle(glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3, std::string const &name,
                   std::shared_ptr<Material> const mat_ptr) {
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
    material_ = mat_ptr;
    name_ = name;
}

Triangle::~Triangle() {}

//TODO volume of a plane?
float Triangle::volume() const {
    return 0;
}

float Triangle::area() const {
    return fabsf((p1_.x * (p2_.y - p3_.y) +
                  p2_.x * (p3_.y - p1_.y) +
                  p3_.x * (p1_.y - p2_.y)) / 2.0f);
}

std::ostream &Triangle::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Triangle)" << std::endl
                  << "Material: " << "[" << material_->name_ << "]" << std::endl
                  << "Point 1: " << "[" << p1_.x << ", " << p1_.y << ", " << p1_.z << "]" << std::endl
                  << "Point 2: " << "[" << p2_.x << ", " << p2_.y << ", " << p2_.z << "]" << std::endl
                  << "Point 3: " << "[" << p3_.x << ", " << p3_.y << ", " << p3_.z << "]" << std::endl;
    } else {
        return os << "Name: " << name_ << " (Triangle)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Point 1: " << "[" << p1_.x << ", " << p1_.y << ", " << p1_.z << "]" << std::endl
                  << "Point 2: " << "[" << p2_.x << ", " << p2_.y << ", " << p2_.z << "]" << std::endl
                  << "Point 3: " << "[" << p3_.x << ", " << p3_.y << ", " << p3_.z << "]" << std::endl;
    }
}

// TODO implement intersect // not working
Hitpoint Triangle::intersect(Ray const &ray) const {
    glm::vec3 Position;
    float distance;
    bool hitted = glm::intersectRayTriangle(ray.origin_, ray.direction_, p1_, p2_, p3_, Position);
    Hitpoint hitp;
    hitp.hit_ = hitted;
    hitp.hitpoint_ = Position;
    hitp.material_ = material_;
    hitp.distance_ = glm::distance(Position, ray.origin_);
    hitp.direction_ = ray.direction_;
    hitp.name_ = name_;
    hitp.normal_ = glm::cross(p1_ - p2_, p3_ - p2_);
    return hitp;
}


