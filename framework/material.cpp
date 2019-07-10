#include "material.hpp"
#include <memory>

std::ostream &operator<<(std::ostream &os, Material const &mat) {
    os << "Name: " << mat.name << std::endl;
    os << "Materialkoeffizient kd:  " << mat.kd;
    os << "Materialkoeffizient ks:  " << mat.ks;
    os << "Materialkoeffizient ka:  " << mat.ka;
    os << "M:  " << mat.m << std::endl;
    return os;
}

bool operator<(std::shared_ptr<Material> const &lhs,
               std::shared_ptr<Material> const &rhs) {
    return (lhs->name < rhs->name);
}

bool operator==(std::shared_ptr<Material> const &lhs,
                std::shared_ptr<Material> const &rhs) {
    return (lhs->name == rhs->name);
}

