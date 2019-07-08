#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <vector>
#include <map>
#include <set>

struct Scene {
    std::vector<std::shared_ptr<Material>> mat_vector;
    std::map<std::string, std::shared_ptr<Material>> mat_map;
    std::set<std::shared_ptr<Material>> mat_set;
};

Scene read_sdf(std::string const &path);

#endif //RAYTRACER_SCENE_HPP
