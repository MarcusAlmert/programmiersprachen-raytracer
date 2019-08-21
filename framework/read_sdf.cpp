#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include "material.hpp"
#include "scene.hpp"
#include "shapes/sphere.hpp"
#include "shapes/box.hpp"
#include "shapes/cylinder.hpp"
#include "shapes/composite.hpp"
#include "shapes/cone.hpp"
#include "shapes/triangle.hpp"


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
                float g;
                float o;
                float ref;
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
                line_string_stream >> g;
                line_string_stream >> o;
                line_string_stream >> ref;
                std::shared_ptr<Material> mat_ = std::make_shared<Material>(Material{mat_name, {ka_r, ka_g, ka_b},
                                                                                     {kd_r, kd_g, kd_b},
                                                                                     {ks_r, ks_g, ks_b},
                                                                                     m, g, o, ref});
                scene1.mat_vector_.push_back(mat_);

            } else if ("shape" == identifier) {
                std::string type;
                line_string_stream >> type;

                if (type == "sphere") {
                    std::string shape_name;
                    float centerx;
                    float centery;
                    float centerz;
                    float radius;
                    std::string shape_mat_name;
                    line_string_stream >> shape_name;
                    line_string_stream >> centerx;
                    line_string_stream >> centery;
                    line_string_stream >> centerz;
                    line_string_stream >> radius;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> sp = std::make_shared<Sphere>(
                            Sphere({centerx, centery, centerz}, radius, shape_name, matptr));
                    scene1.shape_vector_.push_back(sp);

                } else if (type == "box") {
                    std::string shape_name;
                    float p1x;
                    float p2x;
                    float p1y;
                    float p2y;
                    float p1z;
                    float p2z;
                    std::string shape_mat_name;
                    line_string_stream >> shape_name;
                    line_string_stream >> p1x;
                    line_string_stream >> p1y;
                    line_string_stream >> p1z;
                    line_string_stream >> p2x;
                    line_string_stream >> p2y;
                    line_string_stream >> p2z;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> box = std::make_shared<Box>(
                            Box({p1x, p1y, p1z}, {p2x, p2y, p2z}, shape_name, matptr));
                    scene1.shape_vector_.push_back(box);

                } else if (type == "cylinder") {
                    std::string shape_name;
                    std::string shape_mat_name;
                    float p1x;
                    float p1y;
                    float p1z;
                    float p2x;
                    float p2y;
                    float p2z;
                    float r;
                    line_string_stream >> shape_name;
                    line_string_stream >> p1x;
                    line_string_stream >> p1y;
                    line_string_stream >> p1z;
                    line_string_stream >> p2x;
                    line_string_stream >> p2y;
                    line_string_stream >> p2z;
                    line_string_stream >> r;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> cylinder = std::make_shared<Cylinder>(
                            Cylinder(glm::vec3{p1x, p1y, p1z}, glm::vec3{p2x, p2y, p2z}, r, shape_name, matptr));
                    scene1.shape_vector_.push_back(cylinder);

                } else if (type == "cone") {
                    std::string shape_name;
                    std::string shape_mat_name;
                    float px;
                    float py;
                    float pz;
                    float r;
                    float h;
                    line_string_stream >> shape_name;
                    line_string_stream >> px;
                    line_string_stream >> py;
                    line_string_stream >> pz;
                    line_string_stream >> r;
                    line_string_stream >> h;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> cone = std::make_shared<Cone>(Cone({px, py, pz}, r, h, shape_name, matptr));
                    scene1.shape_vector_.push_back(cone);

                } else if (type == "triangle") {
                    std::string shape_name;
                    std::string shape_mat_name;
                    float p1x;
                    float p1y;
                    float p1z;
                    float p2x;
                    float p2y;
                    float p2z;
                    float p3x;
                    float p3y;
                    float p3z;
                    line_string_stream >> shape_name;
                    line_string_stream >> p1x;
                    line_string_stream >> p1y;
                    line_string_stream >> p1z;
                    line_string_stream >> p2x;
                    line_string_stream >> p2y;
                    line_string_stream >> p2z;
                    line_string_stream >> p3x;
                    line_string_stream >> p3y;
                    line_string_stream >> p3z;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> triangle = std::make_shared<Triangle>(
                            Triangle({p1x, p1y, p1z}, {p2x, p2y, p2z}, {p3x, p3y, p3z}, shape_name, matptr));
                    scene1.shape_vector_.push_back(triangle);

                } else if (type == "composite") {
                    std::string shape_name;
                    line_string_stream >> shape_name;
                    std::string next_shape_name;
                    bool valid = true;
                    Composite composite;
                    composite.name_ = shape_name;
                    line_string_stream >> next_shape_name;
                    while (valid) {
                        std::string last = next_shape_name;
                        std::shared_ptr<Shape> found = find(scene1.shape_vector_, next_shape_name);
                        if (last == next_shape_name) {
                            break;
                        }
                        if (found != nullptr) {
                            composite.add_shape(found);
                        } else {
                            valid = false;
                        }
                        line_string_stream >> next_shape_name;
                    }
                    scene1.shape_vector_.push_back(std::make_shared<Composite>(composite));
                }

            } else if (identifier == "light") {
                std::string l_name;
                line_string_stream >> l_name;
                float px;
                float py;
                float pz;
                float r;
                float g;
                float b;
                float brightness;
                line_string_stream >> px;
                line_string_stream >> py;
                line_string_stream >> pz;
                line_string_stream >> r;
                line_string_stream >> g;
                line_string_stream >> b;
                line_string_stream >> brightness;
                Light light{l_name, {px, py, pz}, {r, g, b}, brightness};
                scene1.lights_.push_back(light);

            } else if (identifier == "camera") {
                std::string c_name;
                line_string_stream >> c_name;
                float x;
                float y;
                float z;
                float fov;
                line_string_stream >> fov;
                line_string_stream >> x;
                line_string_stream >> y;
                line_string_stream >> z;
                scene1.camera_.name = c_name;
                scene1.camera_.fov = fov;
                scene1.camera_.position = {x, y, z};
                line_string_stream >> x;
                line_string_stream >> y;
                line_string_stream >> z;
                scene1.camera_.direction = {x, y, z};
                line_string_stream >> x;
                line_string_stream >> y;
                line_string_stream >> z;
                scene1.camera_.upVector = {x, y, z};

            } else if (identifier == "ambient") {
                float amb;
                line_string_stream >> amb;
                scene1.ambient_ = amb;
            }
        }
    }
    return scene1;
}