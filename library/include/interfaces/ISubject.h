//
// Created by andrii on 3/18/25.
//

#pragma once

#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>
#include "IObserver.h"

/**
 * @brief Interface for a subject that can be observed.
 */
class ISubject {
public:
    virtual ~ISubject() = default;

    /**
     * @brief Attach an observer to receive events.
     * @param observer Shared pointer to the observer.
     */
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;

    /**
     * @brief Detach an observer so it no longer receives events.
     * @param observer Shared pointer to the observer.
     */
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;

    /**
     * @brief Notifies all attached observers with a PulseEvent.
     * @param event The event that occurred.
     */
    virtual void notify(const PulseEvent& event) = 0;
};

#endif //ISUBJECT_H


