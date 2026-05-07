#include "objects.hpp"
#include "test_framework.h"
#include "simple_vector.hpp"
#include "physics.hpp"
#include <cmath>

constexpr double SIGMA = 0.0001;

bool aproxCompare(double a, double b) {
    if (std::abs(a - b) < SIGMA) {
        return true;
    }
    return false;
}

void test_constructor_and_getters() {
    FixedObject o1 = FixedObject(1, 10000, SimpleVector(0.0, 0.0), SimpleVector(0.0, 0.0));
    FreeObject o2 = FreeObject(2, 100, SimpleVector(30.0, 40.0), SimpleVector(3000.0, 4000.0), SimpleVector(0.0, 0.0));

    N_ASSERT(o1.getPosition() == SimpleVector(0.0, 0.0));
    N_ASSERT(o2.getPosition() == SimpleVector(30.0, 40.0));

    N_ASSERT(o1.getMass() == 10000);
    N_ASSERT(o2.getMass() == 100);
}

void test_FixedObject() {
    FixedObject o1 = FixedObject(1, 10000, SimpleVector(100.0, 100.0), SimpleVector(0.0, 0.0));
    FixedObject o2 = FixedObject(1, 10000, SimpleVector(0.0, 0.0), SimpleVector(0.0, 0.0));
    
    o1.calculateAppliedForce(o2);
    o2.calculateAppliedForce(o1);

    o1.recalculatePos(1.0);
    o2.recalculatePos(1.0);

    N_ASSERT(o1.getPosition() == SimpleVector(100.0, 100.0));
    N_ASSERT(o2.getPosition() == SimpleVector(0.0, 0.0));

    N_ASSERT(o1.getAppliedForce() == SimpleVector(0.0, 0.0));
    N_ASSERT(o2.getAppliedForce() == SimpleVector(0.0, 0.0));
}

void test_gravitational_force() {
    FixedObject sun(0, 1000000.0, SimpleVector(0, 0), SimpleVector(0, 0));
    FreeObject planet(1, 10.0, SimpleVector(100, 0), SimpleVector(0, 0), SimpleVector(0.0, 0.0));

    planet.calculateAppliedForce(sun);
    
    // F = G * (1000000 * 10) / (100^2) 
    // F = G * (10000000 / 10000) = G * 1000
    
    double expected_force_x = -1.0 * physics::GRAVITATIONAL_CONSTANT * 1000; 
    
    N_ASSERT(aproxCompare(expected_force_x, planet.getAppliedForce().getX()));
    N_ASSERT(aproxCompare(0, planet.getAppliedForce().getY()));
}

void test_FreeObject() {}

int main() {
    TEST_HEADER;

    RUN_TEST(test_constructor_and_getters());
    RUN_TEST(test_FixedObject());
    RUN_TEST(test_gravitational_force());
    
    TEST_FOOTER;

    return (failed_tests == 0) ? 0 : 1;
}