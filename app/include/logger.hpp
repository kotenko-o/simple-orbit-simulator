#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <simple_vector.hpp>
#include <objects.hpp>
#include <iostream>
#include <iomanip>
#include <fstream> 

/**
 * @namespace   logs
 * @brief       Contains functions to output the log table
 */
namespace logs {
    /**
     * @brief   Prints header of csv tabke
     * @param[in]   stream  Output stream
     */
    void startLogTable(std::ostream& stream) {
        stream << std::setw(7) << "Tick "
                << "; " << std::setw(3) << "id " 
                << "; " << std::setw(10) << "x-pos" << "; " << std::setw(10) << "y-pos"
                << "; " << "mass;" << std::endl;
    }

    /**
     * @brief   Logs information about the object
     * @param[in]   stream      Output stream
     * @param[in]   obj         Pointer to object
     * @param[in]   tick        Currern simulation tick
     */
    void logFullObjectInfo(std::ostream& stream, SpaceObject* obj, int tick) {
        stream << std::setw(7) << tick
                << "; " << std::setw(3) << obj->getId() 
                << "; " << std::setw(10) << obj->getPosition().getX() << "; " << std::setw(10) << obj->getPosition().getY()
                << "; " << obj->getMass() << std::endl;
    }
}

/**
 * @namespace   csvLog
 * @brief       Opens and closes the .csv-files
 */
namespace csvLog {
    const std::string DEFAULT_FILE_NAME = "simulation_result.csv";
    /**
     * @brief   Opens new date file
     * @return  fstream     File stream
     */
    std::fstream startLog() {
        std::fstream myFile(DEFAULT_FILE_NAME, std::ios::out);
        return std::move(myFile);
    }
    /**
     * @brief   Safe closing the file
     * @param[in]   myFile  Pointer to the file
     */
    void closeLog(std::fstream& myFile) {
        myFile.close();
    }
}

#endif