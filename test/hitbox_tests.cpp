#include "objects.hpp"
#include "hitbox.hpp"
#include "test_framework.h"
#include "simple_vector.hpp"
#include "physics.hpp"
#include <cmath>
#include <memory>

void test_default_hitbox_collision() {
    FixedObject o1(1, 100, SimpleVector(0.0, 0.0));
    FixedObject o2(2, 100, SimpleVector(1.5, 0.0)); // Dist 1.5 < 2.0 -> Collision
    FixedObject o3(3, 100, SimpleVector(2.1, 0.0)); // Dist 2.1 > 2.0 -> No Collision

    N_ASSERT(o1.collisionCheck(&o2) == true);
    N_ASSERT(o2.collisionCheck(&o1) == true); // Verify symmetry
    N_ASSERT(o1.collisionCheck(&o3) == false);
}

void test_custom_hitbox_collision() {
    FixedObject o1(1, 100, SimpleVector(0.0, 0.0), std::make_unique<HitCircle>(5.0));
    
    FreeObject o2(2, 100, SimpleVector(14.0, 0.0), SimpleVector(0, 0), std::make_unique<HitCircle>(10.0));
    
    FixedObject o3(3, 100, SimpleVector(16.0, 0.0), std::make_unique<HitCircle>(10.0));

    N_ASSERT(o1.collisionCheck(&o2) == true);

    N_ASSERT(o1.collisionCheck(&o3) == false);
}

void test_collision_edge_cases() {
    FixedObject o1(1, 100, SimpleVector(0.0, 0.0), std::make_unique<HitCircle>(2.0));
    FixedObject o2(2, 100, SimpleVector(5.0, 0.0), std::make_unique<HitCircle>(3.0));

    N_ASSERT(o1.collisionCheck(&o2) == true);

    FixedObject o3(3, 100, SimpleVector(0.0, 0.0), std::make_unique<HitCircle>(2.0));
    N_ASSERT(o1.collisionCheck(&o3) == true);
}

int main() {
    TEST_HEADER;
    
    RUN_TEST(test_default_hitbox_collision());
    RUN_TEST(test_custom_hitbox_collision());
    RUN_TEST(test_collision_edge_cases());
    
    TEST_FOOTER;

    return (failed_tests == 0) ? 0 : 1;
}