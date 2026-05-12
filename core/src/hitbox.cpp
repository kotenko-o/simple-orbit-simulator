#include <hitbox.hpp>

HitCircle::HitCircle(double r) : 
    radius(r > 0 ? r : DEF_RADIUS) {}

bool HitCircle::checkCollision(const Hitbox* other, 
                               const SimpleVector& myPos, 
                               const SimpleVector& otherPos) const {
    if (!other) return false;
    
    const HitCircle* hit2 = dynamic_cast<const HitCircle*>(other);
    
    if (hit2) {
        
        double dist = (myPos - otherPos).abs();
        double radius_sum = this->radius + hit2->getRadius();
        
        return (dist <= radius_sum);
    }
    return false;
}

double HitCircle::getRadius() const {
    return this->radius;
}