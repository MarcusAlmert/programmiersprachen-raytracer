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

    virtual float area() const override;
    virtual float volume() const override;
    virtual std::ostream &print(std::ostream &os) const override;
    virtual Hitpoint intersect(Ray const &ray) const override;
};

#endif //RAYTRACER_BOX_HPP
