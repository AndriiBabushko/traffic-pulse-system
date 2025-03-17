//
// Created by andrii on 2/22/25.
//

#ifndef PULSEENTITYFACTORY_H
#define PULSEENTITYFACTORY_H

#pragma once

#include <memory>

#include "entities/PulseEntity.h"
#include "entities/PulseVehicle.h"

#include "types/PulsePosition.h"
#include "types/PulseEntityType.h"

/**
 * @class PulseEntityFactory
 * @brief Factory class for creating PulseIntersection, PulseTrafficLight, and PulseVehicle objects.
 */
class PulseEntityFactory
{
public:
    /**
     * @brief Creates an entity dynamically based on the requested type.
     * @param type The type of entity to create.
     * @param id The unique identifier of the entity.
     * @param position (Optional) The position for intersections.
     * @param vehicle_type (Optional) The type of vehicle.
     * @param vehicle_role (Optional) The role of the vehicle.
     * @return A unique pointer to the created PulseEntity.
     */
    static std::unique_ptr<PulseEntity> createEntity(
        PulseEntityType type,
        const std::string& id,
        const PulsePosition& position = {},
        PulseVehicleType vehicle_type = PulseVehicleType::CAR,
        PulseVehicleRole vehicle_role = PulseVehicleRole::NORMAL
    );
};


#endif //PULSEENTITYFACTORY_H
