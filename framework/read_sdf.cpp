#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include "material.hpp"
#include "scene.hpp"


Scene read_sdf(std::string const &path) {
    std::string linebuffer;
    std::ifstream in_scene_file(path);
    Scene scene1;
    while (std::getline(in_scene_file, linebuffer)) {
        std::istringstream line_string_stream(linebuffer);

        std::string identifier;
        line_string_stream >> identifier;

        if ("define" == identifier) {
            line_string_stream >> identifier;
            if ("material" == identifier) {
                std::string mat_name;
                line_string_stream >> mat_name;
                float ka_r;
                float ka_g;
                float ka_b;
                float kd_r;
                float kd_g;
                float kd_b;
                float ks_r;
                float ks_g;
                float ks_b;
                float m;
                line_string_stream >> ka_r;
                line_string_stream >> ka_g;
                line_string_stream >> ka_b;
                line_string_stream >> kd_r;
                line_string_stream >> kd_g;
                line_string_stream >> kd_b;
                line_string_stream >> ks_r;
                line_string_stream >> ks_g;
                line_string_stream >> ks_b;
                line_string_stream >> m;
                std::shared_ptr<Material> mat_ = std::make_shared<Material>(Material{mat_name, {ka_r, ka_g, ka_b},
                                                                                     {kd_r, kd_g, kd_b},
                                                                                     {ks_r, ks_g, ks_b}, m});
                scene1.mat_vector.push_back(mat_);
                scene1.mat_map.emplace(mat_name, mat_);
                scene1.mat_set.emplace(mat_);
            }
        }
    }
    return scene1;
}