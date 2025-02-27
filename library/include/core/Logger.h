//
// Created by andrii on 1/30/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
private:
    std::ofstream logFile;

public:
    static Logger& getInstance();

    void log(const std::string& message);
    void logTrafficLight(int id, const std::string& state);
    void logIntersectionStats(const std::string& intersectionId, int vehicleCount);

    ~Logger();
private:
    Logger(); // Private constructor
};

#endif // LOGGER_H
