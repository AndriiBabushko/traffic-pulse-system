//
// Created by andrii on 2/11/25.
//

#ifndef PULSEVEHICLE_H
#define PULSEVEHICLE_H

#pragma once

#include <string>

#include "PulseEntity.h"
#include "types/PulseVehicleType.h"
#include "types/PulseVehicleRole.h"
#include "types/PulsePosition.h"

/**
 * @class PulseVehicle
 * @brief Represents a vehicle moving through the traffic system.
 */
class PulseVehicle: public PulseEntity
{
public:
    /**
     * @brief Constructs a vehicle with a unique ID, type, and role.
     * @param vehicle_id Unique string identifier.
     * @param type Type of the vehicle (CAR, BUS, etc.).
     * @param role Role of the vehicle (NORMAL, EMERGENCY, etc.).
     * @param position Initial position of the vehicle.
     */
    PulseVehicle(std::string vehicle_id, PulseVehicleType type, PulseVehicleRole role, const PulsePosition& position);

    /**
     * @brief Retrieves the vehicle ID.
     * @return The unique string identifier.
     */
    [[nodiscard]] std::string getId() const override;

    /**
     * @brief Retrieves the type of the vehicle.
     * @return The vehicle type.
     */
    [[nodiscard]] PulseVehicleType getType() const;

    /**
     * @brief Retrieves the role of the vehicle.
     * @return The vehicle role.
     */
    [[nodiscard]] PulseVehicleRole getRole() const;

    /**
     * @brief Retrieves the current position of the vehicle.
     * @return The vehicle's position.
     */
    [[nodiscard]] PulsePosition getPosition() const;

    /**
     * @brief Updates the vehicle's position.
     * @param new_position The new position of the vehicle.
     */
    void updatePosition(const PulsePosition& new_position);

private:
    std::string m_vehicle_id; ///< Unique identifier.
    PulseVehicleType m_type; ///< Type of vehicle.
    PulseVehicleRole m_role; ///< Role of vehicle.
    PulsePosition m_position; ///< Current position of the vehicle.
};


#endif //PULSEVEHICLE_H
