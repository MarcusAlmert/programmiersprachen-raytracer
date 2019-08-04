#include "box.hpp"
#include <cmath>
#include <vector>
#include "plane.hpp"

Box::Box() {
    max = {0, 0, 0};
    min = {0, 0, 0};
}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_) {
    max = max_;
    min = min_;

}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_, std::string const &name_,
         std::shared_ptr<Material> const mat_ptr) :
        Shape{name_, mat_ptr} {
    max = max_;
    min = min_;;
}

Box::~Box() {
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
    Ray r = ray;
    Hitpoint hit;

    float tmaxx = (max.x - r.origin.x) / glm::normalize(r.direction).x;
    float tminx = (min.x - r.origin.x) / glm::normalize(r.direction).x;
    float tminy = (min.y - r.origin.x) / glm::normalize(r.direction).x;
    float tmaxy = (max.y - r.origin.x) / glm::normalize(r.direction).x;
    float tminz = (min.z - r.origin.x) / glm::normalize(r.direction).x;
    float tmaxz = (max.z - r.origin.x) / glm::normalize(r.direction).x;

    //das war glaube was adrian meint ist egal
    std::vector<float> inBox;
    if (tmaxx >= min.x && tmaxx <= max.x) { inBox.push_back(tmaxx); }
    if (tminx >= min.x && tmaxx <= max.x) { inBox.push_back(tminx); }
    if (tmaxy >= min.y && tmaxx <= max.y) { inBox.push_back(tmaxy); }
    if (tminy >= min.y && tmaxx <= max.y) { inBox.push_back(tminy); }
    if (tminz >= min.z && tmaxx <= max.z) { inBox.push_back(tminz); }
    if (tmaxz >= min.z && tmaxx <= max.z) { inBox.push_back(tmaxz); }


    float minimal = std::min(inBox[0], inBox[1]);
    minimal = std::min(minimal, inBox[2]);
    minimal = std::min(minimal, inBox[3]);
    minimal = std::min(minimal, inBox[4]);
    minimal = std::min(minimal, inBox[5]);

    glm::vec3 intersection_point = r.origin + minimal * glm::normalize(r.direction);
    if (intersection_point.x >= min.x && intersection_point.x <= max.x &&
        intersection_point.y >= min.y && intersection_point.y <= max.y &&
        intersection_point.z >= min.z && intersection_point.z <= max.z) {
        hit.material = material;
        hit.name = name;
        hit.distance = minimal;
        hit.hit = true;
        hit.direction = r.direction;
        float hitx = ray.origin.x + minimal * ray.direction.x;
        float hity = ray.origin.y + minimal * ray.direction.y;
        float hitz = ray.origin.z + minimal * ray.direction.z;
        hit.hitpoint = {hitx, hity, hitz};
        return hit;
    } else {
        return hit;
    }

}