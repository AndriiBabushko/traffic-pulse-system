//
// Created by andrii on 3/28/25.
//
#pragma once

#ifndef SUMOUTILS_H
#define SUMOUTILS_H

#include <string>

#include "types/PulseVehicleType.h"
#include "types/PulseVehicleRole.h"

/**
 * @brief Tries to interpret a SUMO vehicle "type" string and returns a PulseVehicleType.
 *        This is partial logic—further expansions can be done in future.
 */
inline PulseVehicleType deduceVehicleTypeFromSumo(const std::string& sumo_type_str)
{
    if (sumo_type_str == "passenger") {
        return PulseVehicleType::CAR;
    }
    if (sumo_type_str == "truck" || sumo_type_str == "trailer") {
        return PulseVehicleType::TRUCK;
    }
    if (sumo_type_str == "emergency") {
        return PulseVehicleType::EMERGENCY;
    }
    // Fall back:
    return PulseVehicleType::CAR;
}

/**
 * @brief Tries to interpret role from a SUMO property or other logic.
 *        This is partial logic—further expansions can be done in future.
 */
inline PulseVehicleRole deduceVehicleRoleFromSumo(const std::string& sumo_role_str)
{
    // If SUMO indicates "ambulance", "fire", or "police", we might consider that EMERGENCY role.
    if (sumo_role_str == "police" || sumo_role_str == "fire" || sumo_role_str == "ambulance") {
        return PulseVehicleRole::EMERGENCY;
    }
    // Fall back:
    return PulseVehicleRole::NORMAL;
}


#endif //SUMOUTILS_H
