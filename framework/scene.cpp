#include "scene.hpp"
#include <iostream>
#include "material.hpp"
#include <set>
#include <vector>
#include <map>

std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name) {
    for (int i = 0; i < mat.size(); i++) {
        if (mat[i]->name == name) {
            return mat[i];
        }
    }
    return nullptr;
}

std::shared_ptr<Material> find(std::set<std::shared_ptr<Material>> const &mat, std::string const &name) {
    for (auto it : mat) {
        if (it->name == name)
            return it;
    }
    return nullptr;
}

std::shared_ptr<Material> find(std::map<std::string, std::shared_ptr<Material>> const &mat, std::string const &name) {
    auto result = mat.find(name);
    if (result == mat.end()) {
        return nullptr;
    }
    return result->second;
}