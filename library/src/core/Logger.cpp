//
// Created by andrii on 3/18/25.
//

#include "core/Logger.h"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::update(const std::string& eventDescription) {
    // For simplicity, log to console. You can extend this to log to file.
    std::cout << "[LOG] " << eventDescription << std::endl;
}

