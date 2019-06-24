#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

int main(int argc, char *argv[]) {
    Sphere s1 = Sphere();
    s1.print();

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

TEST_CASE("Sphere Constructor new", "[Sphere]") {
    Sphere sp1 = Sphere({1, 1, 1}, 10);
    REQUIRE(sp1.area() == Approx(1256.637));
    REQUIRE(sp1.volume() == Approx(4188.79));
    Sphere sp2 = Sphere({1, 1, 1}, 10, "sphere2", {1, 1, 1});
    REQUIRE(sp2.name == "sphere2");
    REQUIRE(sp2.color.r == 1);
    REQUIRE(sp2.color.g == 1);
    REQUIRE(sp2.color.b == 1);
}

TEST_CASE("Sphere area()", "[Sphere]") {
    Sphere sp1 = Sphere({3, 4, 10}, 13);
    REQUIRE(sp1.area() == Approx(2123.717));
    sp1 = Sphere({2, 3, 1}, 2);
    REQUIRE(sp1.area() == Approx(50.265));
    sp1 = Sphere({2, 3, 1}, 0);
    REQUIRE(sp1.area() == Approx(0));
}

TEST_CASE("Sphere volume()", "[Sphere]") {
    Sphere sp1 = Sphere({3, 4, 10}, 13);
    REQUIRE(sp1.volume() == Approx(9202.772));
    sp1 = Sphere({2, 3, 1}, 2);
    REQUIRE(sp1.volume() == Approx(33.51));
    sp1 = Sphere({2, 3, 1}, 0);
    REQUIRE(sp1.volume() == Approx(0));
}

TEST_CASE("Box standard Constructor", "[Box]") {
    Box b1 = Box();
    REQUIRE(b1.area() == 0);
    REQUIRE(b1.volume() == 0);
}

TEST_CASE("Box Constructor", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    REQUIRE(b1.area() == Approx(600));
    REQUIRE(b1.volume() == Approx(1000));
}

TEST_CASE("Box Constructor new", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    REQUIRE(b1.name == "No_Name");
    REQUIRE(b1.color.r == 0.5);
    REQUIRE(b1.color.g == 0.5);
    REQUIRE(b1.color.b == 0.5);
    Box b2 = Box({0, 0, 0}, {10, 10, 10}, "box2", {1, 1, 1});
    REQUIRE(b2.name == "box2");
    REQUIRE(b2.color.r == 1);
    REQUIRE(b2.color.g == 1);
    REQUIRE(b2.color.b == 1);
}
TEST_CASE("Box volume()", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    REQUIRE(b1.volume() == Approx(1000));
    b1 = Box({10, 10, 10}, {0, 0, 0});
    REQUIRE(b1.volume() == Approx(1000));
    b1 = Box({12, 11, 3}, {1, 10, 23});
    REQUIRE(b1.volume() == Approx(220));
}

TEST_CASE("Box area()", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    REQUIRE(b1.area() == Approx(600));
    b1 = Box({10, 10, 10}, {0, 0, 0});
    REQUIRE(b1.area() == Approx(600));
    b1 = Box({12, 11, 3}, {1, 10, 23});
    REQUIRE(b1.area() == Approx(502.0));
}



