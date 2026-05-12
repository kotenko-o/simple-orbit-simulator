#include <cstdint>
#include <vector>

#include "objects.hpp"

/**
 * @class Simulation
 * @brief Manages the lifecycle of simulations and space objects
 */
class Simulation {
    private:
        int id = 0;                              // Counter for objects id's
        std::uint64_t current_tick = 0;
        std::uint64_t last_tick = 0;
        // Container for all objects in simulation
        std::vector<std::unique_ptr<SpaceObject>> objects;
        double dt;                              // Timestep for calculations
    public:
        /**
         * @brief   Constructor
         * @param[in]   lastTick    Number of ticks, simulation should do
         * @param[in]   dt          Physical timestep
         */
        Simulation(std::uint64_t lastTick, double dt) 
            : last_tick(lastTick), dt(dt) {}
        /**
         * @brief   Destructor
         */
        ~Simulation() = default;
        /**
         * @brief   Add an existing object to a simulation
         * @param[in]   obj     New object
         */
        void addObject(std::unique_ptr<SpaceObject> obj) {
            objects.push_back(std::move(obj));
        }

        /* ------------------- 
         *  Simulation logic 
         * -------------------*/
        /**
         * @brief   Calculates "physics" for all objects
         * Calculates the forces exerted by all objects on all other objects and 
         * determines the positions of the free objects
         */
        void calculateSystem();
        /**
         * @brief   Check for collisions
         * @todo    Update workaround for output
         * @todo    Optimize algorithm O(n^2)
         */
        void checkCollisions() const;
        /**
         * @brief   Next step: Tick increment, coordinates reset
         */
        void nextStep();
        /**
         * @brief   Checks, if function should run
         */
        bool running() const;
        
        /* ------------------- 
         *  Getter Methods 
         * -------------------*/
        double getDt() const {
            return this->dt;
        }
        uint64_t getCurrentTick() const {
            return this->current_tick;
        }
        uint64_t getLastTick() const {
            return this->last_tick;
        }

        /* ------------------- 
         *  Fabric Methods 
         * -------------------*/
        /**
         * @brief   Fabric method for creation of the free object
         * @return  SpaceObject*    Pointer to the object als reference
         */
        SpaceObject* createFreeObject(double mass, SimpleVector pos, SimpleVector velocity, 
                                        std::unique_ptr<Hitbox> hb = nullptr);
        /**
         * @brief   Fabric method for creation of the fixed object
         * @return  SpaceObject*    Pointer to the object als reference
         */
        SpaceObject* createFixedObject(double mass, SimpleVector pos, 
                                        std::unique_ptr<Hitbox> hb = nullptr);
};