// workaround for main

#include "objects.hpp"
#include "logger.hpp"

int main() {
// ТЕЛА СТОЯТ ПО ВЕРТИКАЛИ
FreeObject o1(1, 1e12, SimpleVector(-243, -970), SimpleVector(0,0), SimpleVector(2.85, -3.81));
FreeObject o2(2, 1e12, SimpleVector(243, 970),   SimpleVector(0,0), SimpleVector(2.85, -3.81));
// ТЕЛО 3 В ЦЕНТРЕ
FreeObject o3(3, 1e12, SimpleVector(0, 0),       SimpleVector(0,0), SimpleVector(-5.70, 7.62));
    console::logFullObjectInfo(&o1, 0);
    console::logFullObjectInfo(&o2, 0);
    console::logFullObjectInfo(&o3, 0);
    
    for (int i = 0; i < 15000; i++) {
        o3.calculateAppliedForce(o1);
        o3.calculateAppliedForce(o2);
        o1.calculateAppliedForce(o3);
        o1.calculateAppliedForce(o2);
        o2.calculateAppliedForce(o1);
        o2.calculateAppliedForce(o3);
        o1.recalculateVelocity(0.01);
        o1.recalculatePos(0.01);
        o2.recalculateVelocity(0.01);
        o2.recalculatePos(0.01);
        o3.recalculateVelocity(0.01);
        o3.recalculatePos(0.01);
        if (i % 100 == 0) {
            console::logFullObjectInfo(&o1, i);
            console::logFullObjectInfo(&o2, i);
            console::logFullObjectInfo(&o3, i);
        }
    }
    return 0;
}