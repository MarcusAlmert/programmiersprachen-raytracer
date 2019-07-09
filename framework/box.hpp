#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP

#include <glm-0.9.5.3/glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
private:
    glm::vec3 min;
    glm::vec3 max;

public:
    Box();

    Box(glm::vec3 const &min_, glm::vec3 const &max_);

    Box(glm::vec3 const &min_, glm::vec3 const &max_, std::string const &name, std::shared_ptr<Material> const mat_ptr);

    ~Box();//override ;

    virtual float area() const override;

    virtual float volume() const override;

    virtual std::ostream &print(std::ostream &os) const override;

    virtual Hitpoint intersect(Ray const &ray) const override;
};

#endif //RAYTRACER_BOX_HPP
