//
// Created by andrii on 2/22/25.
//

#ifndef PULSEEVENTS_H
#define PULSEEVENTS_H

#pragma once

/**
 * @brief Enum to represent different types of events that can occur during the simulation.
 */
enum class PulseEvents {
    SIMULATION_START,   ///< Simulation has started.
    SIMULATION_STEP,    ///< Simulation has advanced by one step.
    SIMULATION_END,     ///< Simulation has ended.
    VEHICLE_STATUS_CHANGE, ///< Vehicle has changed status.
    PEDESTRIAN_STATUS_CHANGE, ///< Pedestrian has changed status.
    TRAFFIC_LIGHT_CHANGE, ///< Traffic light has changed state.
};

#endif //PULSEEVENTS_H
