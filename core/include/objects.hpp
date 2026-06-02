#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <simple_vector.hpp>
#include <hitbox.hpp>
#include <memory>

/**
 * @class   SpaceObjectt
 * @brief   Abstract base class for all space objects
 * 
 * Contains important information about the all space objects, such as
 * id, mass, Vectors of position and applied Force, pointer to the hitbox
 */
class SpaceObject {
    protected:
        int id;                         // uniqe Id of the object
        SimpleVector position;
        double mass;
        SimpleVector appliedForce;
        std::unique_ptr<Hitbox> hitbox;
        // orientation-vector of the object
        SimpleVector orientation;               
    public:

        /**
         * @brief   Constructor of SpaceObject
         * @param[in]   id      Uniqie id of the Object
         * @param[in]   mass    Mass of the object
         * @param[in]   pos     Vector of the position of an object
         * @param[in]   hb      Pointer to the hitbox
         * @param[in]   direction   Direction vector
         */
        SpaceObject(int id, double mass, SimpleVector pos, std::unique_ptr<Hitbox> hb = nullptr, SimpleVector direction = SimpleVector(1, 0))
            : id(id), position(pos), mass(mass), appliedForce(SimpleVector(0, 0)), 
            hitbox(hb ? std::move(hb) : std::make_unique<HitCircle>(1.0)),
            orientation(direction) {}
        virtual ~SpaceObject() {}

        /**
         * @brief       Abstract; Updating the position with the applied force
         * @param[in]   dt      Time-Factor
         */
        virtual void recalculatePos(double dt) = 0;

        /**
         * @brief       Abstract; Calculates applied force of other object
         * @param[in]   object  Poimter to the 2nd object  
         */
        virtual void calculateAppliedForce(const SpaceObject& object) = 0;

        /**
         * @brief   Abstract function to reset the values on each sim. tick
         */
        virtual void reset() {};

        /**
         * @brief       Checks if this object's hitbox overlaps with another
         * @param[in]   obj     Pointer to the other SpaceObject
         * @return      bool    True if a collision is detected, false otherwise.
         */
        bool collisionCheck(const SpaceObject* obj) const;

        /* -------------------
         *  Getter functions
           -------------------*/
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
        virtual const Hitbox* getHitbox() const {
            return this->hitbox.get(); 
        };
};

/**
 * @brief   Class for "static" space objects
 * 
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
        
        /**
         * @brief       Updating the position with the applied force
         * @param[in]   dt      Time-Factor
         */        
        void virtual recalculatePos(double dt) override;
        
        /**
         * @brief       Calculates applied force of other object
         * @param[in]   object  Poimter to the 2nd object  
         */
        virtual void calculateAppliedForce(const SpaceObject& object) override;

        /**
         * @brief   Function to reset the values on each sim. tick
         */
        virtual void reset() override;
};

/**
 * @brief   Struct holding engine configuration/specs
 */
struct EngineSpec {
    double thrust;
    double fuelConsumption;
};

/**
 * @brief   Class for the active/propelled object
 * 
 * Extends FreeObject with engine capabilities. Can receive throttle and
 * direction commands to produce thrust
 */
class ActiveObject : public FreeObject {
    private:
        std::unique_ptr<EngineSpec> engine;
        double fuelMass;
        double throttle;
        SimpleVector thrustDirection;
        bool engineOn;

    public:
        ActiveObject(int id, double dryMass, SimpleVector pos, SimpleVector velocity,
                     std::unique_ptr<EngineSpec> engine, double fuelMass,
                     std::unique_ptr<Hitbox> hb = nullptr);

        virtual ~ActiveObject() = default;

        void engineStart();
        void engineStop();
        ActiveObject& setThrottle(double level);
        ActiveObject& setThrustDirection(const SimpleVector& dir);

        virtual void calculateAppliedForce(const SpaceObject& object) override;
        virtual void recalculatePos(double dt) override;
        virtual void reset() override;

        /* -------------------
         *  Getter functions
           -------------------*/
        bool isEngineOn() const {
            return this->engineOn;
        }
        double getThrottle() const {
            return this->throttle;
        }
        double getFuelMass() const {
            return this->fuelMass;
        }
        double getTotalMass() const {
            return this->mass + this->fuelMass;
        }
        bool hasFuel() const {
            return this->fuelMass > 0.0;
        }
        SimpleVector getThrustDirection() const {
            return this->thrustDirection;
        }
        const EngineSpec* getEngine() const {
            return this->engine.get();
        }

    private:
        SimpleVector calculateThrustForce() const;
        void consumeFuel(double dt);
};

#endif