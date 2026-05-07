#include <cstdint>
#include <vector>

#include "objects.hpp"

/**
 * @class The class that contains the simulation loop and all the objects
 */

class Simulation {
    private:
        std::uint64_t current_tick;
        std::uint64_t last_tick;
        std::vector<SpaceObject*> objects;
    public:
        /**
         * @brief   Add new object to a simulation
         * @param[in]   obj     New object
         */
        void addObject(SpaceObject* obj) {
            objects.push_back(obj);
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
        void checkCollisions();
        /**
         * @brief   Tick change, "cleaning"
         */
        void nextStep();
};