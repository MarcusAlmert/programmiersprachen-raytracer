#include "scene.hpp"
#include <iostream>
#include "material.hpp"

bool operator<(std::shared_ptr<Material> const &lhs,
               std::shared_ptr<Material> const &rhs) {
    return lhs->name < rhs->name;
}

bool operator==(std::shared_ptr<Material> const &lhs,
                std::shared_ptr<Material> const &rhs) {
    if (lhs->name == rhs->name) {
        return true;
    } else {
        return false;
    }
}


std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name) {
    for (int i = 0; i < mat.size(); i++) {
        if (mat[i]->name == name) {
            return mat[i];
        }
    }
    return nullptr;
}

std::shared_ptr<Material> find(std::set<std::shared_ptr<Material>> const &mat, std::string const &name) {
    auto dummy = std::make_shared<Material>(Material(name, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, 20));
    std::set<std::shared_ptr<Material>>::iterator result = mat.find(dummy);
    std::cout << *result << "  " << *mat.end();
    if (result == mat.end()) {
        return nullptr;
    }
    return *result;
}

std::shared_ptr<Material> find(std::map<std::string, std::shared_ptr<Material>> const &mat, std::string const &name) {
    auto result = mat.find(name);
    if (result == mat.end()) {
        return nullptr;
    }
    return result->second;
}