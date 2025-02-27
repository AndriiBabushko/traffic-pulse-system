//
// Created by andrii on 2/25/25.
//

#include "entities/PulseEntityFactory.h"

std::unique_ptr<PulseEntity> PulseEntityFactory::createEntity(
    PulseEntityType type,
    const std::string& id,
    const PulsePosition& position,
    PulseVehicleType vehicle_type,
    PulseVehicleRole vehicle_role)
{
    switch (type)
    {
        case PulseEntityType::INTERSECTION:
            return std::make_unique<PulseIntersection>(std::stoi(id), position);
        case PulseEntityType::TRAFFIC_LIGHT:
            return std::make_unique<PulseTrafficLight>(std::stoi(id));
        case PulseEntityType::VEHICLE:
            return std::make_unique<PulseVehicle>(id, vehicle_type, vehicle_role);
        default:
            return nullptr;
    }
}

