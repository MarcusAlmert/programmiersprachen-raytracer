#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include <glm/gtx/transform.hpp>
#include <shapes/plane.hpp>
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
            if ("resolution" == identifier) {
                unsigned int h, w;
                line_string_stream >> scene1.width;
                line_string_stream >> scene1.height;
            } else if ("filename" == identifier) {
                line_string_stream >> scene1.filename;
            } else if ("material" == identifier) {
                std::string mat_name;
                line_string_stream >> mat_name;
                float ka_r, ka_g, ka_b, kd_r, kd_g, kd_b, ks_r, ks_g, ks_b, m, g, o, ref;
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
                    float centerx, centery, centerz, radius;
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
                    float p1x, p2x, p1y, p2y, p1z, p2z;
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
                    float p1x, p1y, p1z, p2x, p2y, p2z, r;
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
                    float px, py, pz, r;
                    line_string_stream >> shape_name;
                    line_string_stream >> px;
                    line_string_stream >> py;
                    line_string_stream >> pz;
                    glm::vec3 base{px, py, pz};
                    line_string_stream >> px;
                    line_string_stream >> py;
                    line_string_stream >> pz;
                    line_string_stream >> r;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> cone = std::make_shared<Cone>(Cone(glm::vec3{px, py, pz}, base, r, shape_name, matptr));
                    scene1.shape_vector_.push_back(cone);

                } else if (type == "triangle") {
                    std::string shape_name;
                    std::string shape_mat_name;
                    float p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;
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

                } else if (type == "plane") {
                    std::string shape_name;
                    std::string shape_mat_name;
                    float p1x, p1y, p1z, p2x, p2y, p2z;
                    line_string_stream >> shape_name;
                    line_string_stream >> p1x;
                    line_string_stream >> p1y;
                    line_string_stream >> p1z;
                    line_string_stream >> p2x;
                    line_string_stream >> p2y;
                    line_string_stream >> p2z;
                    line_string_stream >> shape_mat_name;
                    auto matptr = find(scene1.mat_vector_, shape_mat_name);
                    std::shared_ptr<Shape> plane = std::make_shared<Plane>(
                            Plane({p1x, p1y, p1z}, {p2x, p2y, p2z}, shape_name, matptr));
                    scene1.shape_vector_.push_back(plane);

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
                float px, py, pz, r, g, b, brightness;
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
                float x, y, z, fov;
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
            } else if (identifier == "backgroundcolor") {
                float r, g, b;
                line_string_stream >> r;
                line_string_stream >> g;
                line_string_stream >> b;
                Color back_col = Color(r, g, b);
                scene1.backgroundcolor_ = back_col;
            }
        } else if (identifier == "transform") {
            std::string name;
            line_string_stream >> name;

            if (find(scene1.shape_vector_, name) != nullptr) {
                std::shared_ptr<Shape> shape_ptr = find(scene1.shape_vector_, name);
                std::string transType;
                line_string_stream >> transType;
                if (transType == "translate") {
                    float x, y, z;
                    line_string_stream >> x;
                    line_string_stream >> y;
                    line_string_stream >> z;
                    shape_ptr->transformation(0, {0, 0, 0}, {1, 1, 1}, {x, y, z});
                } else if (transType == "rotate") {
                    float angle, x, y, z;
                    line_string_stream >> angle;
                    line_string_stream >> x;
                    line_string_stream >> y;
                    line_string_stream >> z;
                    shape_ptr->transformation(angle, {x, y, z}, {1, 1, 1}, {0, 0, 0});
                } else if (transType == "scale") {
                    float x, y, z;
                    line_string_stream >> x;
                    line_string_stream >> y;
                    line_string_stream >> z;
                    shape_ptr->transformation(0, {0, 0, 0}, {x, y, z}, {0, 0, 0});
                }

            } else if (name == "camera") {
                std::string transType;
                line_string_stream >> transType;
                if (transType == "rotate") {
                    float angle, x, y, z;
                    line_string_stream >> angle;
                    line_string_stream >> x;
                    line_string_stream >> y;
                    line_string_stream >> z;
                    glm::mat4x4 rotate = glm::rotate(angle, glm::vec3(x, y, z));
                    glm::vec4 dir4 = glm::vec4(scene1.camera_.direction, 0) * rotate;
                    glm::vec4 up4 = glm::vec4(scene1.camera_.upVector, 0) * rotate;
                    glm::vec3 dir = glm::normalize(glm::vec3(dir4.x, dir4.y, dir4.z));
                    glm::vec3 up = glm::vec3(up4.x, up4.y, up4.z);
                    glm::vec3 u = glm::normalize(glm::cross(dir, up));
                    glm::vec3 v = glm::normalize(glm::cross(u, dir));
                    scene1.camera_.transformation_ += glm::mat4{
                            glm::vec4{u, 0.0f},
                            glm::vec4{v, 0.0f},
                            glm::vec4{-dir, 0.0f},
                            glm::vec4{0.0f}};
                } else if (transType == "translate") {
                    float x, y, z;
                    line_string_stream >> x;
                    line_string_stream >> y;
                    line_string_stream >> z;
                    scene1.camera_.transformation_ += glm::mat4{
                            glm::vec4{0.0f},
                            glm::vec4{0.0f},
                            glm::vec4{0.0f},
                            glm::vec4{x, y, z, 1.0f}};
                }
                // apply transformation to position
                glm::vec4 trans_pos = scene1.camera_.transformation_ * glm::vec4{scene1.camera_.position, 1};
                scene1.camera_.position = {trans_pos.x, trans_pos.y, trans_pos.z};
            }
        }
    }
    return scene1;
}