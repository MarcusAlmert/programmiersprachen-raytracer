#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <iostream>
#include "color.hpp"
#include <memory>

struct Material {
    std::string name_ = "No_name";
    Color ka_{1, 1, 1};
    Color kd_{1, 1, 1};
    Color ks_{1, 1, 1};
    float m_ = 0.0f;
    float glossy_ = 0.0f;
    float opacity_ = 0.0f;
    float refractive_index_ = 0.0f;
};

std::ostream &operator<<(std::ostream &os, Material const &mat);

bool operator<(std::shared_ptr<Material> const &lhs,
               std::shared_ptr<Material> const &rhs);

bool operator==(std::shared_ptr<Material> const &lhs,
                std::shared_ptr<Material> const &rhs);


#endif //RAYTRACER_MATERIAL_HPP
