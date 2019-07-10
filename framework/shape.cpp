//
// Created by marcus on 24.06.19.
//
#include "shape.hpp"

Shape::Shape() {
    name = "No_name";
    material = nullptr;
}

Shape::Shape(std::string const &name_, std::shared_ptr<Material> const mat_ptr) : name{name_}, material{mat_ptr} {
}

Shape::~Shape() {

}

std::ostream &Shape::print(std::ostream &os) const {
    return os << name << " (Shape)" << std::endl
              << "[" << *material << "]" << std::endl;
}

std::ostream &operator<<(std::ostream &os, Shape const &s) {
    return s.print(os);
}

