#include "box.hpp"
#include <cmath>

Box::Box() {
    max = {0, 0, 0};
    min = {0, 0, 0};
    name = "No_name";
    color = {0.5, 0.5, 0.5};
}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_) {
    max = max_;
    min = min_;
    name = "No_name";
    color = {0.5, 0.5, 0.5};
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

std::ostream &Box::print(std::ostream &os) const {
    return os << "Name: " << name << " (Box)" << std::endl
              << "Color: " << "[" << color.r << ", " << color.g << ", " << color.b << "]" << std::endl
              << "Min: " << "[" << min.x << ", " << min.y << "]" << std::endl
              << "Max: " << "[" << max.x << ", " << max.y << "]" << std::endl;

}