#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <vector>
#include <map>
#include <set>
#include <memory>
#include "material.hpp"
#include "shape.hpp"
#include "camera.hpp"
#include "light.hpp"


struct Scene {
    std::vector<std::shared_ptr<Material>> mat_vector;
    std::vector<std::shared_ptr<Shape>> shape_vector;
    Camera cam;
    std::vector<Light> lights;
    float ambient;
};


Scene read_sdf(std::string const &path);

std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name);


#endif //RAYTRACER_SCENE_HPP
