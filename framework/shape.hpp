//
// Created by marcus on 17.06.19.
//
#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP
class Shape{
    virtual float area() const = 0;

    virtual float volume() const = 0;
};
#endif //RAYTRACER_SHAPE_HPP
