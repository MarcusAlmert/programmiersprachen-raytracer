#ifndef RAYTRACER_CYLINDER_HPP
#define RAYTRACER_CYLINDER_HPP

#include <glm/vec3.hpp>
#include <vector>
#include "shape.hpp"

class Cylinder : public Shape {

public:
    Cylinder();

    Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius);

    Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius, std::string const &name,
             std::shared_ptr<Material> const &mat_ptr);

    ~Cylinder();

    float area() const override;

    float volume() const override;

    std::ostream &print(std::ostream &os) const override;

    Hitpoint intersect(Ray const &ray) const override;

    float get_height() const;

private:
    glm::vec3 pos1_;
    glm::vec3 pos2_;
    float radius_;
    glm::vec3 calc_normal_corpus(glm::vec3 const& hitpoint) const;
};


#endif //RAYTRACER_CYLINDER_HPP
