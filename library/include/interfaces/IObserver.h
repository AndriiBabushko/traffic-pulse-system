//
// Created by andrii on 1/30/25.
//

#pragma once

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include "types/PulseEvent.h"

/**
 * @brief Interface for observers that receive updates from a subject.
 */
class IObserver {
public:
    virtual ~IObserver() = default;

    /**
     * @brief Called when the subject emits an event.
     * @param event The event data.
     */
    virtual void update(const PulseEvent& event) = 0;
};

#endif //IOBSERVER_H

