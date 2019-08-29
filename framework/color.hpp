// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color {
    Color(float red, float green, float blue) : r(red), g(green), b(blue) {}

    friend std::ostream &operator<<(std::ostream &os, Color const &c) {
        os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
        return os;
    }

    friend void boundary_check(Color & color){
        if (color.r > 1){
            color.r = 1;
        } else if (color.r < 0){
            color.r = 0;
        }
        if (color.g > 1){
            color.g = 1;
        } else if (color.g < 0){
            color.g = 0;
        }
        if (color.b > 1){
            color.b = 1;
        } else if (color.b < 0){
            color.b = 0;
        }
    }

    Color &operator+=(Color const &other) {
        r += other.r;
        g += other.g;
        b += other.b;
        boundary_check(*this);
        return *this;
    }

    Color &operator-=(Color const &other) {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        boundary_check(*this);
        return *this;
    }

    Color &operator*=(Color const& other){
        r *= other.r;
        g *= other.g;
        b *= other.b;
        boundary_check(*this);
        return *this;
    }

    Color &operator*=(float a){
        r *= a;
        g *= a;
        b *= a;
        boundary_check(*this);
        return *this;
    }

    friend Color operator+(Color const &a, Color const &b) {
        auto tmp(a);
        tmp += b;
        return tmp;
    }

    friend Color operator-(Color const &a, Color const &b) {
        auto tmp(a);
        tmp -= b;
        return tmp;
    }

    friend Color operator*(Color const& a, Color const& b){
        auto tmp(a);
        tmp *= b;
        return tmp;
    }

    friend Color operator*(Color const& color, float a){
        auto tmp(color);
        tmp *= a;
        return tmp;
    }

    friend Color operator*(float a, Color const& color){
        auto tmp(color);
        tmp *= a;
        return tmp;
    }

    friend Color operator/(float a, Color const &color) {
        auto tmp(color);
        tmp.r = tmp.r / a;
        tmp.g = tmp.g / a;
        tmp.b = tmp.b / a;
        return tmp;
    }

    friend Color operator/(Color const &color, float a) {
        auto tmp(color);
        tmp.r = tmp.r / a;
        tmp.g = tmp.g / a;
        tmp.b = tmp.b / a;
        return tmp;
    }

    float r = 0;
    float g = 0;
    float b = 0;
};

#endif //#define BUW_COLOR_HPP
