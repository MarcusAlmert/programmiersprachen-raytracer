#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP

#include <memory>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

enum Axis{x_axis,y_axis, z_axis};

class Shape {

public:
    Shape();

    Shape(std::string const &name_, std::shared_ptr<Material> const mat_ptr);

    virtual float area() const = 0;

    virtual float volume() const = 0;

    virtual std::ostream &print(std::ostream &os) const;

    virtual Hitpoint intersect(Ray const &ray) const = 0;

    virtual ~Shape();

    void transformation(float rotateAngle, glm::vec3 const& rotateAxis, glm::vec3 const &scale, glm::vec3 const& translate);

    std::shared_ptr<Material> material_;
    std::string name_ = "No_name";
    glm::mat4 world_transformation_ = glm::mat4x4{glm::vec4{1.0f,0.0f,0.0f,0.0f},
                                                  glm::vec4{0.0f,1.0f,0.0f,0.0f},
                                                  glm::vec4{0.0f,0.0f,1.0f,0.0f},
                                                  glm::vec4{0.0f,0.0f,0.0f,1.0f}};
    glm::mat4 world_transformation_inv = glm::inverse(world_transformation_);
};

std::ostream &operator<<(std::ostream &os, Shape const &s);

#endif //RAYTRACER_SHAPE_HPP
