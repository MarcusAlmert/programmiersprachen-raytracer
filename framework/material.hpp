#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <iostream>
#include "color.hpp"
#include <memory>

struct Material {
    std::string name = "No_name";
    Color ka{1, 1, 1};
    Color kd{1, 1, 1};
    Color ks{1, 1, 1};
    float m = 0.0f;
};

std::ostream &operator<<(std::ostream &os, Material const &mat);

bool operator<(std::shared_ptr<Material> const &lhs,
               std::shared_ptr<Material> const &rhs);

bool operator==(std::shared_ptr<Material> const &lhs,
                std::shared_ptr<Material> const &rhs);


#endif //RAYTRACER_MATERIAL_HPP
