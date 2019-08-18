#include "cylinder.hpp"

Cylinder::Cylinder() {
    pos_ = {0, 0, 0};
    radius_ = 1;
    height_ = 1;
}

Cylinder::Cylinder(glm::vec3 const &pos, float radius, float height) {
    pos_ = pos;
    radius_ = radius;
    height_ = height;
}

Cylinder::Cylinder(glm::vec3 const &pos, float radius, float height, std::string const &name,
                   std::shared_ptr<Material> const mat_ptr) {
    pos_ = pos;
    radius_ = radius;
    height_ = height;
    name_ = name;
    material_ = mat_ptr;
}

Cylinder::~Cylinder() {}

float Cylinder::area() const {
    return 2 * M_PI * pow(radius_, 2) + 2 * M_PI * radius_ * height_;
}

float Cylinder::volume() const {
    return M_PI * pow(radius_, 2) * height_;
}

std::ostream &Cylinder::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Cylinder)" << std::endl
                  << "Material: " << "[" << material_->name_ << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    } else {
        return os << "Name: " << name_ << " (Cylinder)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    }
}

// TODO implement intersect
Hitpoint Cylinder::intersect(Ray const &ray) const {

}

