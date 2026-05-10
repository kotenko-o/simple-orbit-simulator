/**
 * @file    app.cpp
 * @brief   Example for full simulatiot cycle
 */

#include "objects.hpp"
#include "logger.hpp"
#include "simulation.hpp"

int main() {

    double mEarth = 1e12;
    double mMoon = 1.23e10;
    double mShip = 1.0;

    Simulation sim(600000, 0.01);
    std::fstream file = csvLog::startLog();

    sim.createFreeObject(mEarth, SimpleVector(0, 0), SimpleVector(0, -0.00513));
    sim.createFreeObject(mMoon,  SimpleVector(384, 0),  SimpleVector(0, 0.419));

    logs::startLogTable(file);

    while (sim.getCurrentTick() < sim.getLastTick()) {
        sim.calculateSystem();
        if (sim.getCurrentTick() % 5000 == 0) {
            logs::logFullObjectInfo(file, earth, sim.getCurrentTick());
            logs::logFullObjectInfo(file, &moon, sim.getCurrentTick());
        }
        sim.checkCollisions();
        sim.nextStep();
    }
    
    csvLog::closeLog(file);

    return 0;
}