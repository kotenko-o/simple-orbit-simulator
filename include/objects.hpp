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
        SimpleVector appliedForce;
    public:
        SpaceObject(int id, double mass, SimpleVector pos, SimpleVector appliedForce) 
            : id(id), position(pos), mass(mass), appliedForce(appliedForce) {}
        virtual ~SpaceObject() {}
        /**
         * @brief       Updating the position with the applied force
         */
        virtual void recalculatePos() = 0;
        virtual void calculateAppliedForce(const SpaceObject& object) = 0;
        SimpleVector getPosition() const {
            return this->position;
        }
        double getMass() const {
            return this->mass;
        }
        SimpleVector getAppliedForce() const {
            return this->appliedForce;
        }
        int getId() const {
            return this->id;
        }
};

/**
 * @brief   Class for "static" space objects
 * Non-moving static object. Applicable to systems such as Earth - Spaceship.
 * Used to avoid unnecessary calculations of extrem small moving of huge objects 
 */
class FixedObject : public SpaceObject {
    public:
        using SpaceObject::SpaceObject;
        virtual void recalculatePos() override {};
        virtual void calculateAppliedForce(const SpaceObject& object) override {};
};

/**
 * @brief   Class for moving space objects 
 */
class FreeObject : public SpaceObject {
    protected:
        SimpleVector acceleration;
        SimpleVector velocity;
        /**
         * @brief Calculates affect on acceleration of one object
         * @param[in]   object      The object
         */
        void calculateAffect(const SpaceObject& object);
    public:
        FreeObject(int id, double mass, SimpleVector pos, SimpleVector velocity) 
            : SpaceObject(id, mass, pos, SimpleVector(0, 0)), acceleration(SimpleVector(0, 0)), velocity(velocity) {}
        /**
         * @brief Calculate the momental speed
         */
        void recalculateVelocity();
        void virtual recalculatePos() override;
        virtual void calculateAppliedForce(const SpaceObject& object) override;
};

#endif