#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "simple_vector.hpp"
#include "hitbox.hpp"
#include <memory>

/**
 * @class   Abstract base class for all space objects
 */
class SpaceObject {
    protected:
        int id;
        SimpleVector position;
        double mass;
        SimpleVector appliedForce;
        std::unique_ptr<Hitbox> hitbox;
    public:
        SpaceObject(int id, double mass, SimpleVector pos, std::unique_ptr<Hitbox> hb = nullptr) 
            : id(id), position(pos), mass(mass), appliedForce(SimpleVector(0, 0)), hitbox(hb ? std::move(hb) : std::make_unique<HitCircle>(1.0)) {}
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
        virtual const Hitbox* getHitbox() const {
            return this->hitbox.get(); 
        };
        /**
         * @brief       Checks if this object's hitbox overlaps with another
         * @param[in]   obj     Pointer to the other SpaceObject
         * @return      bool    True if a collision is detected, false otherwise.
         */
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
        FreeObject(int id, double mass, SimpleVector pos, SimpleVector velocity, std::unique_ptr<Hitbox> hb = nullptr) 
            : SpaceObject(id, mass, pos, std::move(hb)), acceleration(SimpleVector(0, 0)), velocity(velocity) {}
        /**
         * @brief Calculate the momental speed
         */
        void recalculateVelocity(double dt);
        void virtual recalculatePos(double dt) override;
        virtual void calculateAppliedForce(const SpaceObject& object) override;
        virtual void reset() override;
};

#endif