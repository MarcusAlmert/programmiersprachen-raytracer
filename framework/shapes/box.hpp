#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
private:
    glm::vec3 min_;
    glm::vec3 max_;

public:
    Box();
    Box(glm::vec3 const &min, glm::vec3 const &max);
    Box(glm::vec3 const &min, glm::vec3 const &max, std::string const &name, std::shared_ptr<Material> const& mat_ptr);
    ~Box();//override ;

    float area() const override;

    float volume() const override;

    std::ostream &print(std::ostream &os) const override;

    Hitpoint intersect(Ray const &ray) const override;
};

void autocorrection(glm::vec3 &min, glm::vec3 &max);

#endif //RAYTRACER_BOX_HPP
