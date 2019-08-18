#ifndef RAYTRACER_COMPOSITE_HPP
#define RAYTRACER_COMPOSITE_HPP

#include <vector>
#include "shape.hpp"

class Composite : public Shape {
public:
    Composite();

    Composite(std::vector<std::shared_ptr<Shape>> const &shapes, std::string name);

    Composite(std::shared_ptr<Shape> const shape, std::string name);

    ~Composite();

    void add_shape(std::shared_ptr<Shape> const shape);


    virtual float area() const override;

    virtual float volume() const override;

    virtual std::ostream &print(std::ostream &os) const override;

    virtual Hitpoint intersect(Ray const &ray) const override;

private:
    std::vector<std::shared_ptr<Shape>> shapes_;
};

#endif //RAYTRACER_COMPOSITE_HPP
