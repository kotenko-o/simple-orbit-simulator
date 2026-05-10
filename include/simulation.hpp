#include <cstdint>
#include <vector>

#include "objects.hpp"

/**
 * @class The class that contains the simulation loop and all the objects
 */

class Simulation {
    private:
        int id = 0;
        std::uint64_t current_tick = 0;
        std::uint64_t last_tick = 0;
        std::vector<std::unique_ptr<SpaceObject>> objects;
        double dt;
    public:
        /**
         * @brief   Constructor
         * @param[in]   lastTick    Tick up to which simulation should run
         * @param[in]   dt          Factor for time
         */
        Simulation(std::uint64_t lastTick, double dt) 
            : last_tick(lastTick), dt(dt) {}
        /**
         * @brief   Destructor
         */
        ~Simulation() {}
        /**
         * @brief   Add new object to a simulation
         * @param[in]   obj     New object
         */
        void addObject(std::unique_ptr<SpaceObject> obj) {
            objects.push_back(std::move(obj));
        }
        /**
         * @brief   Remove an object from simulation
         * @param[in]   obj     Pointer to object to remove
         */
        void removeObject(SpaceObject* obj);
        /**
         * @brief   Main loop for each tick
         */
        void calculateSystem();
        /**
         * @brief   Check for collisions and take action
         */
        void checkCollisions() const;
        /**
         * @brief   Tick change, "cleaning"
         */
        void nextStep();
        /**
         * @brief   Getter for dt
         * @return  double  dt
         */
        double getDt() const {
            return this->dt;
        }
        /**
         * @brief   Getter for Current Tick
         * @return  double  Curret Tick
         */
        int64_t getCurrentTick() const {
            return this->current_tick;
        }
        /**
         * @brief   Getter for last Tick
         * @return  double  last Tick
         */
        int64_t getLastTick() const {
            return this->last_tick;
        }

        void createFreeObject(double mass, SimpleVector pos, SimpleVector velocity, std::unique_ptr<Hitbox> hb = nullptr) {
            auto new_object = std::make_unique<FreeObject>(id, mass, pos, velocity, hb);
            objects.push_back(std::move(new_object));
            this->id++;
        }

        void createFixedObject(double mass, SimpleVector pos, std::unique_ptr<Hitbox> hb = nullptr) {
            auto new_object = std::make_unique<FixedObject>(id, mass, pos, hb);
            objects.push_back(std::move(new_object));
            this->id++;
        }
};