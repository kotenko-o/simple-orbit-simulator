#include "hitbox.hpp"
#include "physics.hpp"
#include "objects.hpp"

bool HitCircle::checkCollision(const Hitbox* hit) const {
    if (!hit) return false;
    const HitCircle* hit2 = dynamic_cast<const HitCircle*>(hit);
    if (hit2) {
        double dist = (this->getPosition() - hit2->getPosition()).abs();
        double radius_sum = this->getRadius() + hit2->getRadius();
        return (dist <= radius_sum);
    }
    return false;
}

HitCircle::HitCircle(double r, SpaceObject* obj) : 
    radius(r > 0 ? r : DEF_RADIUS), object(obj) {}

double HitCircle::getRadius() const {
            return this->radius;
    }

SimpleVector HitCircle::getPosition() const {
            return this->object->getPosition();
    }