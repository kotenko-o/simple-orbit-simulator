#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "simple_vector.hpp"
#include "objects.hpp"
#include <iostream>
#include <iomanip>

namespace console {

    void startLogTable() {
        return;
    }
    void logFullObjectInfo(FixedObject* obj) {
        std::cout << std::setw(7) << 0
                << "; " << std::setw(3) << obj->getId() 
                << "; " << std::setw(10) << obj->getPosition().getX() << "; " << std::setw(10) << obj->getPosition().getY()
                << "; " << obj->getMass() << std::endl;
    }
    void logFullObjectInfo(FreeObject* obj, int tick) {
        std::cout << std::setw(7) << tick 
                << "; " << std::setw(3) << obj->getId() 
                << "; " << std::setw(10) << obj->getPosition().getX() << "; " << std::setw(10) << obj->getPosition().getY()
                << "; " << obj->getMass() << std::endl;
    }
}

#endif