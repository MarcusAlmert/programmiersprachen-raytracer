#ifndef RAYTRACER_PLANE_HPP
#define RAYTRACER_PLANE_HPP

#include <glm-0.9.5.3/glm/vec3.hpp>
#include "shape.hpp"

class Plane : public Shape {
public:
    Plane();

    Plane(glm::vec3 const &p1, glm::vec3 const &normal);

    Plane(glm::vec3 const &p, glm::vec3 const &normal, std::string const &name,
            std::shared_ptr<Material> const mat_ptr);

    ~Plane();

    virtual float area() const override;

    virtual float volume() const override;

    virtual std::ostream &print(std::ostream &os) const override;

    virtual Hitpoint intersect(Ray const &ray) const override;

private:
    glm::vec3 point_;
    glm::vec3 normal_;
};


#endif //RAYTRACER_PLANE_HPP
