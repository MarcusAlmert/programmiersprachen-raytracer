#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <iostream>
#include "color.hpp"

struct Material {
    std::string name = "No_name";
    Color ka{1, 1, 1};
    Color kd{1, 1, 1};
    Color ks{1, 1, 1};
    float m = 0.0f;

    Material(std::string const &nn, Color const &ka_, Color const &kd_, Color const &ks_, float const m_) {
        name = nn;
        ka = ka_;
        kd = kd_;
        ks = ks_;
        m = m_;
    }

    Material() {}
};

std::ostream &operator<<(std::ostream &os, Material const &mat);


#endif //RAYTRACER_MATERIAL_HPP
