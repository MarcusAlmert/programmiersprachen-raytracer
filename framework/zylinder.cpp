#include "zylinder.hpp"

Zylinder::Zylinder() {
    pos_ = {0, 0, 0};
    radius_ = 1;
    height_ = 1;
}

Zylinder::Zylinder(glm::vec3 const &pos, float radius, float height) {
    pos_ = pos;
    radius_ = radius;
    height_ = height;
}

Zylinder::Zylinder(glm::vec3 const &pos, float radius, float height, std::string const &name,
                   std::shared_ptr<Material> const mat_ptr) {
    pos_ = pos;
    radius_ = radius;
    height_ = height;
    name_ = name;
    material_ = mat_ptr;
}

Zylinder::~Zylinder() {}

float Zylinder::area() const {
    return 2 * M_PI * pow(radius_, 2) + 2 * M_PI * radius_ * height_;
}

float Zylinder::volume() const {
    return M_PI * pow(radius_, 2) * height_;
}

std::ostream &Zylinder::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Sphere)" << std::endl
                  << "Material: " << "[" << material_->name_ << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    } else {
        return os << "Name: " << name_ << " (Sphere)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    }
}

Hitpoint Zylinder::intersect(Ray const &ray) const {

}

