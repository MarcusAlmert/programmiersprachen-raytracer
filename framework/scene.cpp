#include "material.hpp"
#include <vector>
#include <shapes/shape.hpp>
#include "shapes/composite.hpp"

std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name) {
    for (int i = 0; i < mat.size(); i++) {
        if (mat[i]->name_ == name) {
            return mat[i];
        }
    }
    return nullptr;
}

std::shared_ptr<Shape> find(std::vector<std::shared_ptr<Shape>> const &shapes, std::string const &searching) {
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i]->name_ == searching) {
            return shapes[i];
        }
    }
    return nullptr;
}

std::shared_ptr<Shape> find(std::shared_ptr<Composite> const &composite, std::string const &name) {
    auto shapes = composite->getShapes();
    for (int i = 0; i < shapes.size(); i++) {
        if (shapes[i]->name_ == name) {
            return shapes[i];
        }
    }
    return nullptr;
}