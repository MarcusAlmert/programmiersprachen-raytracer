//
// Created by marcus on 24.06.19.
//
#include "shape.hpp"

std::ostream &operator<<(std::ostream &os, Shape const &s) {
    os << "Name: " << s.name << std::endl
       << "Color: " << "[" << s.color.r << ", " << s.color.g << ", " << s.color.b << "]" << std::endl;
}

std::ostream &Shape::print(std::ostream &os) const {
    return std::cout << this << std::endl;
}

