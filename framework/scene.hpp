#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <vector>
#include <map>
#include <set>
#include <memory>
#include "material.hpp"
#include "shapes/shape.hpp"
#include "camera.hpp"
#include "light.hpp"


struct Scene {
    std::vector<std::shared_ptr<Material>> mat_vector_;
    std::vector<std::shared_ptr<Shape>> shape_vector_;
    Camera camera_;
    std::vector<Light> lights_;
    float ambient_;
};


Scene read_sdf(std::string const &path);

std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name);


#endif //RAYTRACER_SCENE_HPP
