#include <catch2/catch_test_macros.hpp>
#include <objects.hpp>
#include <hitbox.hpp>
#include <simple_vector.hpp>
#include <physics.hpp>
#include <cmath>
#include <memory>

TEST_CASE ("default_hitbox_collision", "[hitbox]") {
    FixedObject o1(1, 100, SimpleVector(0.0, 0.0));
    FixedObject o2(2, 100, SimpleVector(1.5, 0.0)); // Dist 1.5 < 2.0 -> Collision
    FixedObject o3(3, 100, SimpleVector(2.1, 0.0)); // Dist 2.1 > 2.0 -> No Collision

    REQUIRE(o1.collisionCheck(&o2) == true);
    REQUIRE(o2.collisionCheck(&o1) == true); // Verify symmetry
    REQUIRE(o1.collisionCheck(&o3) == false);
}

TEST_CASE ("custom_hitbox_collision", "[hitbox]") {
    FixedObject o1(1, 100, SimpleVector(0.0, 0.0), std::make_unique<HitCircle>(5.0));
    
    FreeObject o2(2, 100, SimpleVector(14.0, 0.0), SimpleVector(0, 0), std::make_unique<HitCircle>(10.0));
    
    FixedObject o3(3, 100, SimpleVector(16.0, 0.0), std::make_unique<HitCircle>(10.0));

    REQUIRE(o1.collisionCheck(&o2) == true);

    REQUIRE(o1.collisionCheck(&o3) == false);
}

TEST_CASE ("collision_edge_cases", "[hitbox]") {
    FixedObject o1(1, 100, SimpleVector(0.0, 0.0), std::make_unique<HitCircle>(2.0));
    FixedObject o2(2, 100, SimpleVector(5.0, 0.0), std::make_unique<HitCircle>(3.0));

    REQUIRE(o1.collisionCheck(&o2) == true);

    FixedObject o3(3, 100, SimpleVector(0.0, 0.0), std::make_unique<HitCircle>(2.0));
    REQUIRE(o1.collisionCheck(&o3) == true);
}