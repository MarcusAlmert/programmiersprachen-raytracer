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
#include "shape.hpp"
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

    Color calc_color(Hitpoint hitpoint, Scene const &scene);
    Color calc_ambient(std::shared_ptr<Material> material, Scene const& scene);

    Color calc_diffuse(Hitpoint hitpoint, Scene const &scene);

    Color calc_reflect(std::shared_ptr<Material> material, Scene const &scene);
    void tone_mapping(Color & color);
};

#endif // #ifndef BUW_RENDERER_HPP
