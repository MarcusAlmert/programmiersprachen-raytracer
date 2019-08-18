#ifndef RAYTRACER_TRIANGLE_HPP
#define RAYTRACER_TRIANGLE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Triangle : public Shape {

public:
    Triangle();

    Triangle(glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3);

    Triangle(glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3, std::string const &name,
             std::shared_ptr<Material> const mat_ptr);

    ~Triangle();

    virtual float area() const override;

    virtual float volume() const override;

    virtual std::ostream &print(std::ostream &os) const override;

    virtual Hitpoint intersect(Ray const &ray) const override;

private:
    glm::vec3 p1_;
    glm::vec3 p2_;
    glm::vec3 p3_;
};


#endif //RAYTRACER_TRIANGLE_HPP
