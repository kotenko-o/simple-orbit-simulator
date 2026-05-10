#include "objects.hpp"
#include "physics.hpp"
#include <cmath>

// necessary for gravitational force calculation, to avoid "infinite" force on close fly-by
constexpr double MINIMAL_DISTANCE = 1e-9;

void FreeObject::calculateAppliedForce(const SpaceObject& object) {
    SimpleVector distance = this->getPosition() - object.getPosition();
    double r = distance.abs();
    double dist = (r < MINIMAL_DISTANCE) ? MINIMAL_DISTANCE : r;
    double force = physics::calculateGravitationalForce(this->getMass(), object.getMass(), dist);
    this->appliedForce += distance.getUnitVector() * force * (-1);
}


void FreeObject::recalculateVelocity(double dt) {
    this->acceleration = this->appliedForce * (1.0 / this->mass);
    this->velocity += this->acceleration * dt;
}

void FreeObject::recalculatePos(double dt) {
    this->recalculateVelocity(dt);
    this->position += this->velocity * dt;
}

void FreeObject::reset() {
    this->appliedForce = SimpleVector(0, 0);
    this->acceleration = SimpleVector(0, 0);
}

bool SpaceObject::collisionCheck(const SpaceObject* obj) const {
    return this->hitbox->checkCollision(obj->getHitbox());
}