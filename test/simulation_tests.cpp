#include <simulation.hpp>
#include <objects.hpp>
#include <test_framework.h>
#include <simple_vector.hpp>

void test_simple_two_body_movement() {
    double mass = 1e12;
    Simulation sim(10, 0.0);

    SpaceObject* p1 = sim.createFreeObject(mass, SimpleVector(0, 0), SimpleVector(0, 0));
    SpaceObject* p2 = sim.createFreeObject(mass, SimpleVector(100, 0), SimpleVector(0, 0));

    sim.calculateSystem();

    N_ASSERT(p1->getPosition().getX() > 0);
    N_ASSERT(p2->getPosition().getX() < 100);
}

int main() {
    TEST_HEADER;
    RUN_TEST(test_simple_two_body_movement);
    TEST_FOOTER;
    return (failed_tests == 0) ? 0 : 1;
}