//
// Created by andrii on 1/30/25.
//

#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

/**
 * @brief Interface for objects that observe changes.
 */
class IObserver {
public:
    virtual ~IObserver() = default;
    /**
     * @brief Called when the subject notifies observers.
     * @param eventDescription A string describing the event.
     */
    virtual void update(const std::string& eventDescription) = 0;
};

#endif // OBSERVER_H
