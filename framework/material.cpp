#include "material.hpp"
#include <memory>

std::ostream &operator<<(std::ostream &os, Material const &mat) {
    os << "Name: " << mat.name_ << std::endl;
    os << "Materialkoeffizient kd:  " << mat.kd_;
    os << "Materialkoeffizient ks:  " << mat.ks_;
    os << "Materialkoeffizient ka:  " << mat.ka_;
    os << "M:  " << mat.m_ << std::endl;
    return os;
}

bool operator<(std::shared_ptr<Material> const &lhs,
               std::shared_ptr<Material> const &rhs) {
    return (lhs->name_ < rhs->name_);
}

bool operator==(std::shared_ptr<Material> const &lhs,
                std::shared_ptr<Material> const &rhs) {
    return (lhs->name_ == rhs->name_);
}

