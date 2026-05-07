#include "objects.hpp"
#include "physics.hpp"
#include <cmath>

void FreeObject::calculateAppliedForce(const SpaceObject& object) {
    SimpleVector distance = this->getPosition() - object.getPosition();
    double force = physics::calculateGravitationalForce(this->getMass(), object.getMass(), distance.abs());
    this->appliedForce += distance.getUnitVector() * force * (-1);
}


void FreeObject::recalculateVelocity() {
    this->acceleration += this->appliedForce * (1.0 / this->mass);
    this->velocity += this->acceleration;
}

void FreeObject::recalculatePos(double dt) {
    this->position += this->velocity * dt;
    this->appliedForce = SimpleVector(0, 0);
    this->acceleration = SimpleVector(0, 0);
}