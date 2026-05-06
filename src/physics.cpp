#include "physics.hpp"

double physics::calculateGravitationalForce(double m1, double m2, double dist) {
        return physics::GRAVITATIONAL_CONSTANT * (m1 * m2) / dist;
}