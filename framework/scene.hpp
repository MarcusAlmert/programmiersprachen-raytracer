#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <vector>
#include <map>
#include <set>
#include <memory>
#include "material.hpp"


struct Scene {
    std::vector<std::shared_ptr<Material>> mat_vector;
    std::map<std::string, std::shared_ptr<Material>> mat_map;
    std::set<std::shared_ptr<Material>> mat_set;
};


Scene read_sdf(std::string const &path);

std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name);

std::shared_ptr<Material> find(std::set<std::shared_ptr<Material>> const &mat, std::string const &name);

std::shared_ptr<Material> find(std::map<std::string, std::shared_ptr<Material>> const &mat, std::string const &name);


#endif //RAYTRACER_SCENE_HPP
