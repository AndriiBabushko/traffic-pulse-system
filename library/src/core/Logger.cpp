//
// Created by andrii on 1/30/25.
//

#include "Logger.h"

#include <iostream>
#include <ctime>

Logger::Logger() {
    logFile.open("traffic_log.txt", std::ios::app);
    if (!logFile) {
        std::cerr << "An error occurred while opening log file." << std::endl;
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}


void Logger::log(const std::string& message) {
    const std::time_t now = std::time(nullptr);
    logFile << std::ctime(&now) << ": " << message << std::endl;
}

void Logger::logTrafficLight(const int id, const std::string& state) {
    log("Traffic Light " + std::to_string(id) + " change state to " + state);
}

void Logger::logIntersectionStats(const std::string& intersectionId, const int vehicleCount) {
    log("Intersection " + intersectionId + " has " + std::to_string(vehicleCount) + " vehicles.");
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

