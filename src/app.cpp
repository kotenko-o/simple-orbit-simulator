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

    FreeObject earth(1, mEarth, SimpleVector(0, 0),   SimpleVector(0, -0.00513));
    FreeObject moon(2, mMoon,  SimpleVector(384, 0),  SimpleVector(0, 0.419));
    FreeObject ship(3, mShip,  SimpleVector(394, 0),  SimpleVector(0, 0.417 + 0.082));

    Simulation sim(600000, 0.01);
    std::fstream file = csvLog::startLog();

    logs::startLogTable(file);

    sim.addObject(&earth);
    sim.addObject(&moon);
    sim.addObject(&ship);

    while (sim.getCurrentTick() < sim.getLastTick()) {
        sim.calculateSystem();
        if (sim.getCurrentTick() % 5000 == 0) {
            logs::logFullObjectInfo(file, &earth, sim.getCurrentTick());
            logs::logFullObjectInfo(file, &moon, sim.getCurrentTick());
            logs::logFullObjectInfo(file, &ship, sim.getCurrentTick());
        }
        sim.nextStep();
    }
    
    csvLog::closeLog(file);

    return 0;
}