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
         * @return      True if they collide; False if they do not collide or
         *              if the hitbox shape cannot be handled.
         */
        virtual bool checkCollision(const Hitbox* other, 
                                const SimpleVector& myPos, 
                                const SimpleVector& otherPos) const = 0;
};

/**
 * @class   HitCircle
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

        /**
         * @brief   Check, if collision occured
         * @param[in]   other   Pointer to the hitbox of the second body
         * @param[in]   myPos   Vector to the possition of this body
         * @param[in]   otherPos    Vector to the possition of the 2nd body
         */
        bool checkCollision(const Hitbox* other, 
                            const SimpleVector& myPos, 
                            const SimpleVector& otherPos) const override;
        
        /**
         * @brief   Getter-Fucttion of the radium
         * @return  Radius of the circle
         */
        double getRadius() const;
};

#endif
