#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <memory>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "material.hpp"
#include "scene.hpp"

int main(int argc, char *argv[]) {

    return Catch::Session().run(argc, argv);

}

/* Tests for Shapes */

TEST_CASE("Material print", "Material") {
    Material red{"Red", Color{1, 1, 1}, Color{0, 0, 0}, Color{0.5, 0.5, 0.5}, 1.0f};
    std::cout << red << std::endl;
}

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

TEST_CASE("Print", "[Shapes]") {
    Box b1{{1, 1, 1},
           {0, 0, 0}};
    Sphere sp1;
    std::cout << " --------- test ------------\n";
    sp1.print(std::cout) << std::endl;
    b1.print(std::cout);
    std::cout << " ---------------------------\n";
}


TEST_CASE ("intersect_ray_sphere", "[intersect]") {
// Ray
    glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
// ray direction has to be normalized !
// you can use :
// v = glm :: normalize ( some_vector )
    glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
// Sphere
    glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
    float sphere_radius{1.0f};
    float distance = 0.0f;
    auto result = glm::intersectRaySphere(
            ray_origin, ray_direction,
            sphere_center,
            sphere_radius * sphere_radius, // squared radius !!!
            distance);
    REQUIRE (distance == Approx(4.0f));


    Sphere s1{glm::vec3{5.0f, 5.0f, 5.0f}, 1.0f};
    Sphere s2{glm::vec3{10.0f, 10.0f, 10.0f}, 1.0f};
    Ray ray{{0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f}};
    Ray raymissed{{0.0f, 0.0f,  0.0f},
                  {0.0f, -1.0f, 0.0f}};
    Hitpoint hit = s1.intersect(ray);
    Hitpoint missed = s2.intersect(raymissed);

    REQUIRE(hit.hit);
    REQUIRE(hit.name == "No_name");
    REQUIRE(!missed.hit);
    REQUIRE(missed.name == "miss");
}

TEST_CASE("Aufgabe 5.8", "Shape") {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    Sphere *s1 = new Sphere{position, 1.2f};
    Shape *s2 = new Sphere{position, 1.2f};
    s1->print(std::cout);
    s2->print(std::cout);
    std::cout << "----------here------------\n";
    delete s1;
    std::cout << "--------------------------\n";
    delete s2;
    std::cout << "--------------------------\n";
}

TEST_CASE("Aufgabe 6.3 intersect ray-box", "Box") {
    Box b1{{0,  0,  0},
           {10, 10, 10}};
    Ray orig{{20, 5, 5},
             {-1, 0, 0}};
    Hitpoint hitp = b1.intersect(orig);
    REQUIRE(hitp.hit);
    REQUIRE(hitp.hitpoint.x == 10);
    REQUIRE(hitp.hitpoint.y == 5);
    REQUIRE(hitp.hitpoint.z == 5);
}

TEST_CASE("read sdf", "SDF") {
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    auto vec = scene1.mat_vector;
    auto map = scene1.mat_map;
    auto set = scene1.mat_set;

    for (int i = 0; i < scene1.mat_vector.size(); i++) {
        std::cout << scene1.mat_vector[i]->name << std::endl;
    }
}

TEST_CASE("find() vec", "vec") {
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    auto vec = scene1.mat_vector;
    auto map = scene1.mat_map;
    auto set = scene1.mat_set;

    REQUIRE(find(vec, "red")->name == "red");
    REQUIRE(find(map, "red")->name == "red");
    //REQUIRE(find(set, "red")->name == "red");
    find(set, "red");
}