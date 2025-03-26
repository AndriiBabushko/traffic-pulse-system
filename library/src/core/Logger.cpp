//
// Created by andrii on 3/18/25.
//

#include "core/Logger.h"

#include <iostream>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::update(const PulseEvent& event) {
    // For simplicity, log to console. You can extend this to log to file.
    std::cout << "[LOG] " << event.message << std::endl;
}

