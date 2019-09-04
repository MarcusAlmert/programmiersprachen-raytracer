#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

class Sphere : public Shape {

private:
    glm::vec3 middlePoint_;
    float radius_;

public:
    Sphere();
    Sphere(glm::vec3 const &mid, float rad);

    Sphere(glm::vec3 const &mid, float rad, std::string const &name, std::shared_ptr<Material> const &mat_ptr);
    ~Sphere();//override ;

    float area() const override;

    float volume() const override;

    std::ostream &print(std::ostream &os) const override;

    Hitpoint intersect(Ray const &ray) const override;
};

#endif //RAYTRACER_SPHERE_HPP
