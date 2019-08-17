//
// Created by marcus on 24.06.19.
//
#include "shape.hpp"

Shape::Shape() {
    name_ = "No_name";
    material_ = nullptr;
}

Shape::Shape(std::string const &name_, std::shared_ptr<Material> const mat_ptr) : name_{name_}, material_{mat_ptr} {
}

Shape::~Shape() {

}

std::ostream &Shape::print(std::ostream &os) const {
    return os << name_ << " (Shape)" << std::endl
              << "[" << *material_ << "]" << std::endl;
}

std::ostream &operator<<(std::ostream &os, Shape const &s) {
    return s.print(os);
}

