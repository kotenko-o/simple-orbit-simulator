#include "objects.hpp"
#include "physics.hpp"
#include <cmath>

void FreeObject::calculateAppliedForce(const SpaceObject& object) {
    SimpleVector distance = this->getPossition() - object.getPossition();
    double force = physics::calculateGravitationForce(this->getMass(), object.getMass(), distance.abs());
    this->appliedForce += distance.getUnitVector() * force;
}

void FreeObject::calculateAffect(const SpaceObject& object) {
    acceleration += this->appliedForce * this->mass;
}