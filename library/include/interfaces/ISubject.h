//
// Created by andrii on 3/18/25.
//

#pragma once

#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>
#include <vector>
#include <string>
#include "IObserver.h"

/**
 * @brief Interface for a subject that can be observed.
 */
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify(const std::string& eventDescription) = 0;
};


#endif //ISUBJECT_H
