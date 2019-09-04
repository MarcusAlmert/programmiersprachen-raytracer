#ifndef RAYTRACER_CONE_HPP
#define RAYTRACER_CONE_HPP

#include <glm/vec3.hpp>
#include <vector>
#include "shape.hpp"


class Cone : public Shape {

public:
    Cone();

    Cone(glm::vec3 const &base_pos, glm::vec3 const &tip_pos, float radius);

    Cone(glm::vec3 const &base_pos, glm::vec3 const &tip_pos, float radius, std::string const &name,
         std::shared_ptr<Material> const &mat_ptr);

    ~Cone();

    float area() const override;

    float volume() const override;

    std::ostream &print(std::ostream &os) const override;

    Hitpoint intersect(Ray const &ray) const override;

    float get_height() const;

private:
    glm::vec3 base_center_pos_;
    glm::vec3 tip_pos_;
    float radius_;

    glm::vec3 calc_normal_corpus(glm::vec3 const &hitpoint) const;

};

#endif //RAYTRACER_CONE_HPP
