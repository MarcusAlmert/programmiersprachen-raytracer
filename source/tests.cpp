#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

int main(int argc, char *argv[]) {
    return Catch::Session().run(argc, argv);
}

/* Tests for Shapes */

TEST_CASE("Sphere standard Constructor", "[Sphere]") {
    Sphere sp1 = Sphere();
    REQUIRE(sp1.area() == 0);
    REQUIRE(sp1.volume() == 0);
}

TEST_CASE("Sphere Constructor", "[Sphere]") {
    Sphere sp1 = Sphere({1, 1, 1}, 10);
    REQUIRE(sp1.area() == Approx(1256.637));
    REQUIRE(sp1.volume() == Approx(4188.79));
}

TEST_CASE("Sphere area()", "[Sphere]") {
    Sphere sp1 = Sphere({3, 4, 10}, 13);
    REQUIRE(sp1.area() == Approx(2123.717));
    sp1 = Sphere({2, 3, 1}, 2);
    REQUIRE(sp1.area() == Approx(50.265));
    sp1 = Sphere({2, 3, 1}, 0);
    REQUIRE(sp1.area() == Approx(0));

}