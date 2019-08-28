//
// Created by marcus on 24.06.19.
//
#include "shape.hpp"

Shape::Shape() {
    name_ = "No_name";
    material_ = nullptr;
}

Shape::Shape(std::string const &name_, std::shared_ptr<Material> const mat_ptr) : name_{name_}, material_{mat_ptr} {
}

Shape::~Shape() {

}

void Shape::transformation(float const rotate, glm::vec3 const &scale, glm::vec3 const& translate, Axis const& axis) {

    glm::mat4x4 scaleMat = glm::mat4x4{glm::vec4{scale.x, 0.0f, 0.0f, 0.0f},
                                       glm::vec4{0.0f, scale.y, 0.0f, 0.0f},
                                       glm::vec4{0.0f, 0.0f, scale.z, 0.0f},
                                       glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
    glm::mat4x4 xRotMat = glm::mat4x4{glm::vec4{1, 0.0f, 0.0f, 0.0f},
                                      glm::vec4{0.0f, glm::cos(rotate), glm::sin(rotate), 0.0f},
                                      glm::vec4{0.0f, -glm::sin(rotate), glm::cos(rotate), 0.0f},
                                      glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
    glm::mat4x4 yRotMat = glm::mat4x4{glm::vec4{glm::cos(rotate), 0.0f, -glm::sin(rotate), 0.0f},
                                      glm::vec4{0.0f, 1.0f, 0.0f, 0.0f},
                                      glm::vec4{glm::sin(rotate), 0.0f, glm::cos(rotate), 0.0f},
                                      glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
    glm::mat4x4 zRotMat = glm::mat4x4{glm::vec4{glm::cos(rotate), glm::sin(rotate), 0.0f, 0.0f},
                                      glm::vec4{-glm::sin(rotate), glm::cos(rotate), 0.0f, 0.0f},
                                      glm::vec4{0.0f, 0.0f, 1.0f, 0.0f},
                                      glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};
    glm::mat4x4 translationMat = glm::mat4x4{glm::vec4{1.0f, 0.0f, 0.0f, 0.0f},
                                             glm::vec4{0.0f, 1.0f, 0.0f, 0.0f},
                                             glm::vec4{0.0f, 0.0f, 1.0f, 0.0f},
                                             glm::vec4{translate.x, translate.y, translate.z, 1.0f}};
    if(axis == x_axis){
        world_transformation_ = world_transformation_ * translationMat * xRotMat * scaleMat;
    } else if(axis == y_axis){
        world_transformation_ = world_transformation_ * translationMat * yRotMat * scaleMat;
    } else if(axis == z_axis){
        world_transformation_ = world_transformation_ * translationMat * zRotMat * scaleMat;
    }
    world_transformation_inv = glm::inverse(world_transformation_);
}

std::ostream &Shape::print(std::ostream &os) const {
    return os << name_ << " (Shape)" << std::endl
              << "[" << *material_ << "]" << std::endl;
}

std::ostream &operator<<(std::ostream &os, Shape const &s) {
    return s.print(os);
}

