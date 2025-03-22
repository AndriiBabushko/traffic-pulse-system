//
// Created by andrii on 1/30/25.
//

#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>
#include <iostream>
#include "interfaces/IObserver.h"

/**
 * @class Logger
 * @brief A singleton logger that implements IObserver to log system events.
 */
class Logger : public IObserver {
public:
    /**
     * @brief Retrieves the singleton instance of Logger.
     * @return Reference to the Logger instance.
     */
    static Logger& getInstance();

    /**
     * @brief Logs an event.
     * @param eventDescription The event description to log.
     */
    void update(const std::string& eventDescription) override;

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};


#endif // LOGGER_H
