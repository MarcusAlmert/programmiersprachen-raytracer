//
// Created by marcus on 24.06.19.
//
#include "shape.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

Shape::Shape() {
    name_ = "No_name";
    material_ = nullptr;
}

Shape::Shape(std::string const &name_, std::shared_ptr<Material> const mat_ptr) : name_{name_}, material_{mat_ptr} {
}

Shape::~Shape() {

}

void Shape::transformation(float const rotateAngle, glm::vec3 const& rotateAxis, glm::vec3 const &scale, glm::vec3 const& translate) {

    glm::mat4x4 scaleMat = glm::mat4x4{glm::vec4{scale.x, 0.0f, 0.0f, 0.0f},
                                       glm::vec4{0.0f, scale.y, 0.0f, 0.0f},
                                       glm::vec4{0.0f, 0.0f, scale.z, 0.0f},
                                       glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}};

    glm::mat4x4 translationMat = glm::mat4x4{glm::vec4{1.0f, 0.0f, 0.0f, 0.0f},
                                             glm::vec4{0.0f, 1.0f, 0.0f, 0.0f},
                                             glm::vec4{0.0f, 0.0f, 1.0f, 0.0f},
                                             glm::vec4{translate.x, translate.y, translate.z, 1.0f}};

    if(rotateAngle != 0){
        glm::mat4x4 RotMat = glm::rotate(glm::radians(rotateAngle), rotateAxis);
        world_transformation_ = world_transformation_ * translationMat * RotMat * scaleMat;

    } else{
        world_transformation_ = world_transformation_ * translationMat *  scaleMat;
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

