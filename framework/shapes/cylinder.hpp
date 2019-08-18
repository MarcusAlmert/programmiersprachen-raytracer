//
// Created by marcus on 17.08.19.
//

#ifndef RAYTRACER_CYLINDER_HPP
#define RAYTRACER_CYLINDER_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Zylinder : public Shape {

public:
    Zylinder();

    Zylinder(glm::vec3 const &pos, float radius, float height);

    Zylinder(glm::vec3 const &pos, float radius, float height, std::string const &name,
             std::shared_ptr<Material> const mat_ptr);

    ~Zylinder();

    virtual float area() const override;

    virtual float volume() const override;

    virtual std::ostream &print(std::ostream &os) const override;

    virtual Hitpoint intersect(Ray const &ray) const override;

private:
    glm::vec3 pos_;
    float radius_;
    float height_;
};


#endif //RAYTRACER_CYLINDER_HPP
