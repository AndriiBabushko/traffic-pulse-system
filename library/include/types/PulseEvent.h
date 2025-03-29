//
// Created by andrii on 3/25/25.
//
#pragma once

#ifndef PULSEEVENT_H
#define PULSEEVENT_H

#include <any>
#include <string>
#include "PulseEvents.h"

struct PulseEvent {
    PulseEvents type;          ///< Type of event.
    std::string message;       ///< Detailed message if needed.
    std::any data;             ///< Optional additional data (e.g., loading progress)
};

#endif //PULSEEVENT_H
