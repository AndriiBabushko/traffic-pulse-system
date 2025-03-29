//
// Created by andrii on 3/1/25.
//

#include "entities/PulseVehicle.h"

#include <utility>

PulseVehicle::PulseVehicle(std::string vehicle_id, const PulseVehicleType type, const PulseVehicleRole role, const PulsePosition& position)
    : m_vehicle_id(std::move(vehicle_id)), m_type(type), m_role(role), m_position(position) {}

std::string PulseVehicle::getId() const
{
    return m_vehicle_id;
}

PulseVehicleType PulseVehicle::getType() const
{
    return m_type;
}

PulseVehicleRole PulseVehicle::getRole() const
{
    return m_role;
}

PulsePosition PulseVehicle::getPosition() const
{
    return m_position;
}

void PulseVehicle::updatePosition(const PulsePosition& new_position)
{
    m_position = new_position;
}
