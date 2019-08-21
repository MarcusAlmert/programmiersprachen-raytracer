// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include <string>
#include <glm/glm.hpp>
#include <memory>
#include <math.h>
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "shapes/shape.hpp"
#include "scene.hpp"

class Renderer {
public:
    Renderer(unsigned w, unsigned h, std::string const &file);

    void render(Scene const& scene);

    void write(Pixel const &p);

    inline std::vector<Color> const &color_buffer() const {
        return color_buffer_;
    }

private:
    unsigned width_;
    unsigned height_;
    std::vector<Color> color_buffer_;
    std::string filename_;
    PpmWriter ppm_;

    Color calc_color(Hitpoint const& hitpoint, Scene const &scene, unsigned int reflaction_steps);

    Color calc_ambient(std::shared_ptr<Material> material, Scene const& scene);
    Color calc_diffuse(Hitpoint const& hitpoint, Scene const &scene);
    Color calc_specular(Hitpoint const& hitpoint, Scene const &scene);
    Color calc_reflection(Hitpoint const& hitpoint, Scene const& scene, unsigned int recursive_boundary);
    Color calc_refraction(Hitpoint const& hitpoint, Scene const& scene, bool inside, unsigned int recursive_boundary);
    float calc_fresnel_reflection_ratio(Hitpoint const& hitpoint, Scene const& scene);

    Hitpoint fire_ray(Scene const& scene, Ray const& ray);

    void invert_direction(glm::vec3 & dir);
    void tone_mapping(Color & color);
};

#endif // #ifndef BUW_RENDERER_HPP
