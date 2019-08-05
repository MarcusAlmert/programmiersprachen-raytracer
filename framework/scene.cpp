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
