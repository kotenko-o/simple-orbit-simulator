/**
 * @file    app.cpp
 * @brief   Example for full simulatiot cycle
 */

#include <objects.hpp>
#include <logger.hpp>
#include <simulation.hpp>

int main() {

    double mEarth = 1e12;
    double mMoon = 1.23e10;
    double mShip = 1.0;

    Simulation sim(60000, 0.01);
    std::fstream file = csvLog::startLog();

    SpaceObject* earth = sim.createFreeObject(mEarth, SimpleVector(0, 0), SimpleVector(0, -0.00513));
    SpaceObject* moon = sim.createFreeObject(mMoon,  SimpleVector(384, 0),  SimpleVector(0, 0.419));

    logs::startLogTable(file);

    while (sim.running()) {
        sim.calculateSystem();
        if (sim.getCurrentTick() % 10000 == 0) {
            logs::logFullObjectInfo(file, earth, sim.getCurrentTick());
            logs::logFullObjectInfo(file, moon, sim.getCurrentTick());
        }
        sim.checkCollisions();
        sim.nextStep();
    }
    
    csvLog::closeLog(file);

    return 0;
}