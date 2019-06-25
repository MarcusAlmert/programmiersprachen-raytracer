//
// Created by marcus on 24.06.19.
//
#include "shape.hpp"

Shape::Shape() {
    name = "No_name";
    color = {0.5, 0.5, 0.5};
}

Shape::Shape(std::string const &name_, Color const &color_) {
    name = name_;
    color = color_;
}

Shape::~Shape() {
    std::cout << "Shape destructor used" << std::endl;
}

std::ostream &Shape::print(std::ostream &os) const {
    return os << name << " (Shape)" << std::endl
              << "[" << color.r << ", " << color.g << ", " << color.b << "]" << std::endl;
}

std::ostream &operator<<(std::ostream &os, Shape const &s) {
    return s.print(os);
}

