#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "simple_vector.hpp"

/**
 * @class   Basic class for all space objects
 */
class SpaceObject {
    protected:
        int id;
        SimpleVector position;
        double mass;
    public:
        /**
         * @brief       Updating the position in relation to the object
         * @param[in]   object      The object
         */
        void virtual recalculatePos(const SpaceObject& object) = 0;        
};

/**
 * @brief   Class for "static" space objects
 * Non-moving static object. Applicable to systems such as Earth - Spaceship.
 * Used to avoid unnecessary calculations of extrem small moving of huge objects 
 */
class FixedObject : public SpaceObject {};

/**
 * @brief   Class for moving space objects 
 */
class FreeObject : public SpaceObject {
    protected:
        SimpleVector acceleration;
        /**
         * @brief Calculates affect on acceleration of one object
         * @param[in]   object      The object
         */
        void calculateAffect(const SpaceObject& object);
        void virtual recalculatePos(const SpaceObject& object) override;
    public:
        /**
         * @brief Calculate the momental speed
         */
        double calculateSpeed();
};

#endif