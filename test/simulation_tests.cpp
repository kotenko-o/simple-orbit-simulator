#include <catch2/catch_test_macros.hpp>
#include <simulation.hpp>
#include <objects.hpp>
#include <simple_vector.hpp>

TEST_CASE("two bodys movement", "[simulation]") {
    double mass = 1e12;
    Simulation sim(10, 1.0);

    SpaceObject* p1 = sim.createFreeObject(mass, SimpleVector(0, 0), SimpleVector(0, 0));
    SpaceObject* p2 = sim.createFreeObject(mass, SimpleVector(100, 0), SimpleVector(0, 0));

    sim.calculateSystem();

    REQUIRE(p1->getPosition().getX() > 0);
    REQUIRE(p2->getPosition().getX() < 100);
}