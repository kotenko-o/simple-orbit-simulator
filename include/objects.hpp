#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "simple_vector.hpp"
#include "hitbox.hpp"

/**
 * @class   Basic class for all space objects
 */
class SpaceObject {
    protected:
        int id;
        SimpleVector position;
        double mass;
        SimpleVector appliedForce;
        Hitbox* hitbox;
    public:
        SpaceObject(int id, double mass, SimpleVector pos) 
            : id(id), position(pos), mass(mass), appliedForce(SimpleVector(0, 0)), hitbox(new HitCircle(1.0, this)) {}
        virtual ~SpaceObject() {}
        /**
         * @brief       Updating the position with the applied force
         */
        virtual void recalculatePos(double dt) = 0;
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
        virtual void reset() {};
        virtual Hitbox* getHitbox() const {
            return this->hitbox;
        };
        bool collisionCheck(const SpaceObject* obj) const;
};

/**
 * @brief   Class for "static" space objects
 * Non-moving static object. Applicable to systems such as Earth - Spaceship.
 * Used to avoid unnecessary calculations of extrem small moving of huge objects 
 */
class FixedObject : public SpaceObject {
    public:
        using SpaceObject::SpaceObject;
        virtual void recalculatePos(double dt) override {};
        virtual void calculateAppliedForce(const SpaceObject& object) override {};
};

/**
 * @brief   Class for moving space objects 
 */
class FreeObject : public SpaceObject {
    protected:
        SimpleVector acceleration;
        SimpleVector velocity;
    public:
        FreeObject(int id, double mass, SimpleVector pos, SimpleVector velocity) 
            : SpaceObject(id, mass, pos), acceleration(SimpleVector(0, 0)), velocity(velocity) {}
        /**
         * @brief Calculate the momental speed
         */
        void recalculateVelocity(double dt);
        void virtual recalculatePos(double dt) override;
        virtual void calculateAppliedForce(const SpaceObject& object) override;
        virtual void reset() override;
};

#endif