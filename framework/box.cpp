#include "box.hpp"
#include <cmath>

Box::Box() {
    max = {0, 0, 0};
    min = {0, 0, 0};
}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_) {
    max = max_;
    min = min_;
}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_, std::string const &name_, Color const &color_) {
    max = max_;
    min = min_;
    name = name_;
    color = color_;
}

float Box::area() const {
    return (2 * abs(max.x - min.x) * abs(max.y - min.y) +
            2 * abs(max.x - min.x) * abs(max.z - min.z) +
            2 * abs(max.z - min.z) * abs(max.y - min.y));
}

float Box::volume() const {
    return (abs(max.x - min.x) * abs(max.y - min.y) * abs(max.z - min.z));
}