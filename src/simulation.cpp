#include "simulation.hpp"

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
