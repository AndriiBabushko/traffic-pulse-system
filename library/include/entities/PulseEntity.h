//
// Created by andrii on 2/25/25.
//

#ifndef PULSEENTITY_H
#define PULSEENTITY_H

#pragma once

#include <string>

/**
 * @class PulseEntity
 * @brief Base class for all simulation entities (intersections, vehicles, traffic lights).
 */
class PulseEntity
{
public:
    virtual ~PulseEntity() = default;

    /**
     * @brief Retrieves the entity's unique ID.
     * @return The unique identifier of the entity.
     */
    [[nodiscard]] virtual std::string getId() const = 0;
};

#endif //PULSEENTITY_H
