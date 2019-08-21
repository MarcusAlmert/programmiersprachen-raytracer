#ifndef RAYTRACER_CYLINDER_HPP
#define RAYTRACER_CYLINDER_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Cylinder : public Shape {

public:
    Cylinder();

    Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius);

    Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius, std::string const &name,
             std::shared_ptr<Material> const mat_ptr);

    ~Cylinder();

    virtual float area() const override;

    virtual float volume() const override;

    virtual std::ostream &print(std::ostream &os) const override;

    virtual Hitpoint intersect(Ray const &ray) const override;

    float get_height() const;

private:
    glm::vec3 pos1_;
    glm::vec3 pos2_;
    float radius_;
};


#endif //RAYTRACER_CYLINDER_HPP
