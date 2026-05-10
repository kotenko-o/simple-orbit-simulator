#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "simple_vector.hpp"
class SpaceObject;

/// @brief Default radius if none or invalid radius is given.
constexpr double DEF_RADIUS = 1.0;

/**
 * @class   Basic class, which represents hitbox (form) of the object
 */
class Hitbox {
    public:
        Hitbox() {}
        virtual ~Hitbox() {}
        /**
         * @brief   Calculates, if a collision occired between this hitbox and another
         * @param[in]   other       Pointer to the Hitbox of the second body
         * @param[in]   myPos       Position vector of this hitbox's owner
         * @param[in]   otherPos    Position vector of the second body
         * @return      bool        True if they collide; False if they do not collide or
         *                          if the hitbox shape cannot be handled.
         */
        virtual bool checkCollision(const Hitbox* other, 
                                const SimpleVector& myPos, 
                                const SimpleVector& otherPos) const = 0;
};

/**
 * @brief   A circular hitbox defined by a radius.
 */
class HitCircle : public Hitbox {
    private:
        double radius;
    public:
        /**
         * @brief       Constructor of HitCircle.
         * @param[in]   r   The radius of the circle; must be greater than 0.
         */
        HitCircle(double r);
        bool checkCollision(const Hitbox* other, 
                            const SimpleVector& myPos, 
                            const SimpleVector& otherPos) const override;
        double getRadius() const; 
        SimpleVector getPosition() const;
};

#endif
