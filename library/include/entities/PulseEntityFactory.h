//
// Created by andrii on 2/22/25.
//

#ifndef PULSEENTITYFACTORY_H
#define PULSEENTITYFACTORY_H

#include <memory>

#include <types/PulseVehicleRole.h>
#include <types/PulseVehicleType.h>
#include <types/PulseEntityType.h>

#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

/**
 * @class PulseEntityFactory
 * @brief Abstract factory for creating PulseEntities dynamically.
 */
class PulseEntityFactory
{
public:
    /**
     * @brief Creates an entity based on the requested type.
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
        const PulsePosition& position = {0.0, 0.0},
        PulseVehicleType vehicle_type = PulseVehicleType::CAR,
        PulseVehicleRole vehicle_role = PulseVehicleRole::NORMAL
    );
};

#endif //PULSEENTITYFACTORY_H
