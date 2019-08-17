#include "cone.hpp"

Cone::Cone() {
    pos_ = {0, 0, 0};
    height_ = 1;
    radius_ = 1;
}

Cone::Cone(glm::vec3 const &pos, float radius, float height) {
    pos_ = pos;
    height_ = height;
    radius_ = radius;
}

Cone::Cone(glm::vec3 const &pos, float radius, float height, std::string const &name,
           std::shared_ptr<Material> const mat_ptr) {
    pos_ = pos;
    height_ = height;
    radius_ = radius;
    name_ = name;
    material_ = mat_ptr;
}

Cone::~Cone() {}

float Cone::volume() const {
    return 1.0f / 3.0f * M_PI * pow(radius_, 2) * height_;
}

float Cone::area() const {
    return M_PI * pow(radius_, 2) + M_PI * radius_ * sqrt(pow(radius_, 2) + pow(height_, 2));
}

std::ostream &Cone::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Cone)" << std::endl
                  << "Material: " << "[" << material_->name_ << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    } else {
        return os << "Name: " << name_ << " (Cone)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    }
}

// TODO implement intersect
Hitpoint Cone::intersect(Ray const &ray) const {

}