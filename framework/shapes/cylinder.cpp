#include "cylinder.hpp"

Cylinder::Cylinder() :
    pos1_{glm::vec3{0, 0, 0}}, pos2_{glm::vec3{0, 0, 0}}, radius_{0.0f} {
        name_ = "EmptyCylinder";
        material_ = nullptr;
    }

Cylinder::Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius) :
    pos1_{pos1}, pos2_{pos2}, radius_{radius}
    {
        name_ = "UnnamedCylinder";
        material_ = nullptr;
    }

Cylinder::Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius, std::string const &name,
                   std::shared_ptr<Material> const mat_ptr) :
    pos1_{pos1}, pos2_{pos2}, radius_{radius} {
        name_ = name;
        material_ = mat_ptr;
    }

Cylinder::~Cylinder() {}

float Cylinder::area() const {
    return 2 * M_PI * pow(radius_, 2) + 2 * M_PI * radius_ * glm::distance(pos1_, pos2_);
}

float Cylinder::volume() const {
    return M_PI * pow(radius_, 2) * glm::distance(pos1_, pos2_);
}

float Cylinder::get_height() const{
    return glm::distance(pos1_, pos2_);
}

std::ostream &Cylinder::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Cylinder)" << std::endl
                  << "Material:   " << "[" << material_->name_ << "]" << std::endl
                  << "CapCenter1: " << "[" << pos1_.x << ", " << pos1_.y << ", " << pos1_.z << "]" << std::endl
                  << "CapCenter2: " << "[" << pos2_.x << ", " << pos2_.y << ", " << pos2_.z << "]" << std::endl
                  << "Radius:     " << radius_ << std::endl
                  << "Height:     " << get_height() << std::endl
                  << "--------------------" << std::endl;
    } else {
        return os << "Name: " << name_ << " (Cylinder)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "CapCenter1: " << "[" << pos1_.x << ", " << pos1_.y << ", " << pos1_.z << "]" << std::endl
                  << "CapCenter2: " << "[" << pos2_.x << ", " << pos2_.y << ", " << pos2_.z << "]" << std::endl
                  << "Radius:     " << radius_ << std::endl
                  << "Height:     " << get_height() << std::endl
                  << "--------------------" << std::endl;
    }
}

// TODO implement intersect
Hitpoint Cylinder::intersect(Ray const &ray) const {

    


    return Hitpoint{};
}

