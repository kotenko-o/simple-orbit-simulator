#include "simulation.hpp"

/* ------------------- 
 *  Simulation logic 
 * -------------------*/

void Simulation::calculateSystem() {
    int objectsSize = this->objects.size();
    for (int i = 0; i < objectsSize - 1; i++) {
        for (int j = i + 1; j < objectsSize; j++) {
                objects[i]->calculateAppliedForce(*objects[j]);
                objects[j]->calculateAppliedForce(*objects[i]);
            }
    }
    for (const auto& obj : objects) {
        obj->recalculatePos(this->dt);
    }
}

void Simulation::nextStep() {
    for (const auto& obj : objects) {
        obj->reset();
    }
    this->current_tick++;
}

void Simulation::checkCollisions() const {
    int objectsSize = this->objects.size();
    for (int i = 0; i < objectsSize - 1; i++) {
        for (int j = i + 1; j < objectsSize; j++) {
                if (objects[i]->collisionCheck(objects[j].get()))
                    std::cout << "Collision!" << std::endl;
            }
    }
}

bool Simulation::running() const {
    if (this->current_tick < this->last_tick) {
        return true;
    }
    return false;
}

/* ------------------- 
 *  Fabric Methods 
 * -------------------*/

SpaceObject* Simulation::createFreeObject(double mass, SimpleVector pos, SimpleVector velocity, std::unique_ptr<Hitbox> hb = nullptr) {
    auto new_object = std::make_unique<FreeObject>(id++, mass, pos, velocity, std::move(hb));
    SpaceObject* ptr = new_object.get();
    objects.push_back(std::move(new_object));
    return ptr;
}

SpaceObject* Simulation::createFixedObject(double mass, SimpleVector pos, 
                                        std::unique_ptr<Hitbox> hb = nullptr) {
    auto new_object = std::make_unique<FixedObject>(id++, mass, pos, std::move(hb));
    SpaceObject* ptr = new_object.get();
    objects.push_back(std::move(new_object));
    return ptr;
}
