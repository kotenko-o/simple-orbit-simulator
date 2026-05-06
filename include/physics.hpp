#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "simple_vector.hpp"

namespace physics {
    constexpr double G = 6.674e-11;
    /**
     * @brief       Calculates gravitational force
     * @param[in]   m1      Mass of 1. Object
     * @param[in]   m2      Mass of 2. object
     * @param[in]   r       Distance between objects
     * @return      double  Force 1 to 2
     */
    double calculateGravitationForce(double m1, double m2, double dist) {
        return G * (m1 * m2) / dist;
    }
}

#endif