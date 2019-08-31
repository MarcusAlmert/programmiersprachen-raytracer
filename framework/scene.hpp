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
#include "color.hpp"
#include "shapes/composite.hpp"


struct Scene {
    std::vector<std::shared_ptr<Material>> mat_vector_;
    std::shared_ptr<Shape> composite;
    Camera camera_;
    std::vector<Light> lights_;
    float ambient_;
    Color backgroundcolor_ = Color{0.0f, 0.0f, 0.0f};
    unsigned int height = 500;
    unsigned int width = 500;
    std::string filename = "./Test.ppm";
    unsigned int antialiasing_ = 4;
    unsigned int frames = 1;
};


Scene read_sdf(std::string const &path);

std::shared_ptr<Material> find(std::vector<std::shared_ptr<Material>> const &mat, std::string const &name);

std::shared_ptr<Shape> find(std::vector<std::shared_ptr<Shape>> const &shapes, std::string const &searching);

std::shared_ptr<Shape> find(std::shared_ptr<Composite> const &composite, std::string const &name);


#endif //RAYTRACER_SCENE_HPP
