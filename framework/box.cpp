#include "box.hpp"
#include <cmath>

Box::Box() {
    max = {0, 0, 0};
    min = {0, 0, 0};
    std::cout << "Box Konstructor used\n";
}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_) {
    max = max_;
    min = min_;
    std::cout << "Box Konstructor used\n";

}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_, std::string const &name_,
         std::shared_ptr<Material> const mat_ptr) :
        Shape{name_, mat_ptr} {
    max = max_;
    min = min_;;
    std::cout << "Box Konstructor used\n";
}

Box::~Box() {
    std::cout << "Box destructor used" << std::endl;
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
    if (material != nullptr) {
        return os << "Name: " << name << " (Box)" << std::endl
                  << "Color: " << "[" << *material << "]" << std::endl
                  << "Min: " << "[" << min.x << ", " << min.y << "]" << std::endl
                  << "Max: " << "[" << max.x << ", " << max.y << "]" << std::endl;
    } else {
        return os << "Name: " << name << " (Box)" << std::endl
                  << "Color: " << "[" << "No Material" << "]" << std::endl
                  << "Min: " << "[" << min.x << ", " << min.y << "]" << std::endl
                  << "Max: " << "[" << max.x << ", " << max.y << "]" << std::endl;
    }
}

Hitpoint Box::intersect(Ray const &ray) const {

}