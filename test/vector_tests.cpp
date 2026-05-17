#include <simple_vector.hpp>
#include <cmath>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("constuctors and getters", "[vectors]") {
    SimpleVector v1 = SimpleVector(1.0, 2.0);
    REQUIRE(v1.getX() == 1.0);
    REQUIRE(v1.getY() == 2.0);
    v1.setX(-1.25);
    REQUIRE(v1.getX() == -1.25);
}

TEST_CASE("vector addition", "[vectors]") {
    SimpleVector v1 = SimpleVector(1.0, 2.0);
    SimpleVector v2 = SimpleVector(0.5, 1.5);
    SimpleVector res = v1 + v2;
    
    REQUIRE(res.getX() == 1.5);
    REQUIRE(res.getY() == 3.5);
}

TEST_CASE("vector length", "[vectors]") {
    SimpleVector v = SimpleVector(3.0, 4.0);
    REQUIRE(v.abs() == std::hypot(3.0, 4.0));
}

TEST_CASE("method chaining", "[vectors]") {
    SimpleVector v(0, 0);
    v.setX(10).setY(20);
    
    REQUIRE(v.getX() == 10.0);
    REQUIRE(v.getY() == 20.0);
}

TEST_CASE("unit vector", "[vectors]") {
    double sigma = 0.001;
    SimpleVector v(3.0, 0.0);
    v = v.getUnitVector();
    REQUIRE(v == SimpleVector(1.0, 0.0));
}