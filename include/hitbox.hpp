#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "simple_vector.hpp"
class SpaceObject;

constexpr double DEF_RADIUS = 1.0;

/**
 * @class   Contains hitbox (form) of the object
 */
class Hitbox {
    public:
        Hitbox() {}
        virtual ~Hitbox() {}
        /**
         * @brief   Calculates, if a collision occired
         * @param[in]   hit     Hitbox of the second body
         * @return      bool    True if collide; False if not collide or 
         *                      hitbox can't be handeld yet
         */
        virtual bool checkCollision(const Hitbox* other, 
                                const SimpleVector& myPos, 
                                const SimpleVector& otherPos) const = 0;
};

class HitCircle : public Hitbox {
    private:
        double radius;
    public:
        HitCircle(double r);
        bool checkCollision(const Hitbox* other, 
                            const SimpleVector& myPos, 
                            const SimpleVector& otherPos) const override;
        double getRadius() const; 
        SimpleVector getPosition() const;
};

#endif
