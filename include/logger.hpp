#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "simple_vector.hpp"
#include "objects.hpp"
#include <iostream>
#include <iomanip>
#include <fstream> 

namespace logs {
    void startLogTable(std::ostream& stream) {
        stream << std::setw(7) << "Tick "
                << "; " << std::setw(3) << "id " 
                << "; " << std::setw(10) << "x-pos" << "; " << std::setw(10) << "y-pos"
                << "; " << "mass;" << std::endl;
    }
    void logFullObjectInfo(std::ostream& stream, FixedObject* obj, int tick) {
        stream << std::setw(7) << tick
                << "; " << std::setw(3) << obj->getId() 
                << "; " << std::setw(10) << obj->getPosition().getX() << "; " << std::setw(10) << obj->getPosition().getY()
                << "; " << obj->getMass() << std::endl;
    }
    void logFullObjectInfo(std::ostream& stream, FreeObject* obj, int tick) {
        stream << std::setw(7) << tick 
                << "; " << std::setw(3) << obj->getId() 
                << "; " << std::setw(10) << obj->getPosition().getX() << "; " << std::setw(10) << obj->getPosition().getY()
                << "; " << obj->getMass() << std::endl;
    }
}

namespace csvLog {
    const std::string DEFAULT_FILE_NAME = "simulation_result.csv";
    std::fstream startLog() {
        std::fstream myFile(DEFAULT_FILE_NAME, std::ios::out);
        return std::move(myFile);
    }
    void closeLog(std::fstream& myFile) {
        myFile.close();
    }
}

#endif