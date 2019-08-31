#include <algorithm>
#include "composite.hpp"
#include "iostream"

Composite::Composite() {
}

Composite::Composite(std::shared_ptr<Shape> const shape, std::string name) {
    shapes_.push_back(shape);
    name_ = name;
}

Composite::Composite(std::vector<std::shared_ptr<Shape>> const &shapes, std::string name) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes_.push_back(shapes[i]);
    }
    name_ = name;
}

Composite::~Composite() {
    shapes_.clear();
}

void Composite::add_shape(std::shared_ptr<Shape> const shape) {
    shapes_.push_back(shape);
}

float Composite::volume() const {
    float result = 0;
    for (int i = 0; i < shapes_.size(); i++) {
        result += shapes_[i]->volume();
    }
    return result;
}

float Composite::area() const {
    float result = 0;
    for (int i = 0; i < shapes_.size(); i++) {
        result += shapes_[i]->area();
    }
    return result;
}

std::ostream &Composite::print(std::ostream &os) const {
    for (int i = 0; i < shapes_.size(); i++) {
        os << shapes_[i] << std::endl;
    }
    return os;
}

//outputs the hitpoint which is closest to ray.origin (first hit of the ray)
Hitpoint Composite::intersect(Ray const &ray) const {
    std::vector<Hitpoint> hitpoints;
    for (int i = 0; i < shapes_.size(); i++) {
        Hitpoint temp = shapes_[i]->intersect(ray);
        if (temp.hit_) {
            hitpoints.push_back(temp);
        }
    }
    if (hitpoints.empty()) {
        return Hitpoint{false};
    }
    std::sort(std::begin(hitpoints),
              std::end(hitpoints), [ray](Hitpoint const &lhs, Hitpoint const &rhs) {
                return glm::distance(lhs.hitpoint_, ray.origin_) < glm::distance(rhs.hitpoint_, ray.origin_);
            });
    return *hitpoints.begin();
}

std::vector<std::shared_ptr<Shape>> Composite::getShapes() const {
    return shapes_;
}

std::shared_ptr<Shape> find(std::shared_ptr<Composite> const composite, std::string const &name) {

}
