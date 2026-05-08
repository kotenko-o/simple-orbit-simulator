#include "simulation.hpp"
#include "objects.hpp"
#include "test_framework.h"
#include  "simple_vector.hpp"

void test_simple_two_body_movement() {
    double mass = 1e12;
    FreeObject obj1(1, mass, SimpleVector(0, 0), SimpleVector(0, 0));
    FreeObject obj2(2, mass, SimpleVector(100, 0), SimpleVector(0, 0));

    Simulation sim(10, 0.1);
    sim.addObject(&obj1);
    sim.addObject(&obj2);

    sim.calculateSystem();

    N_ASSERT(obj1.getPosition().getX() > 0);
    N_ASSERT(obj2.getPosition().getX() < 100);
}

int main() {
    TEST_HEADER;
    RUN_TEST(test_simple_two_body_movement);
    TEST_FOOTER;
    return (failed_tests == 0) ? 0 : 1;
}