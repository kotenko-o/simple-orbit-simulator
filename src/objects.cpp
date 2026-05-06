#include "objects.hpp"
#include "physics.hpp"
#include <cmath>

void FreeObject::calculateAppliedForce(const SpaceObject& object) {
    SimpleVector distance = this->getPosition() - object.getPosition();
    double force = physics::calculateGravitationalForce(this->getMass(), object.getMass(), distance.abs());
    this->appliedForce += distance.getUnitVector() * force;
}

void FreeObject::calculateAffect(const SpaceObject& object) {
    this->acceleration += this->appliedForce * (1.0 / this->mass);
}

void FreeObject::recalculateVelocity() {
    this->velocity += this->acceleration;
}

void FreeObject::recalculatePos() {
    this->position += this->velocity;
    this->appliedForce = SimpleVector(0, 0);
}