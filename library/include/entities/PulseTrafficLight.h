//
// Created by andrii on 1/30/25.
//

#ifndef PULSE_TRAFFIC_LIGHT_H
#define PULSE_TRAFFIC_LIGHT_H

#pragma once

#include <string>

#include "entities/PulseEntity.h"
#include "types/TrafficLightState.h"
#include "types/TrafficLightDurations.h"

/**
 * @class PulseTrafficLight
 * @brief Represents a traffic light in the simulation.
 */
class PulseTrafficLight : public PulseEntity
{
public:
    /**
     * @brief Constructs a traffic light with a unique ID and optional durations.
     * @param traffic_light_id Unique string identifier for the traffic light.
     * @param durations Custom durations for each light state.
     */
    explicit PulseTrafficLight(std::string traffic_light_id, const TrafficLightDurations& durations = {});

    /**
     * @brief Retrieves the traffic light ID.
     * @return The unique string identifier.
     */
    [[nodiscard]] std::string getId() const override;

    /**
     * @brief Sets the current state of the traffic light.
     * @param state The new state (RED, GREEN, etc.).
     */
    void setState(TrafficLightState state);

    /**
     * @brief Retrieves the current state of the traffic light.
     * @return The current state.
     */
    [[nodiscard]] TrafficLightState getState() const;

    /**
     * @brief Sets the duration for each state.
     * @param durations The new durations.
     */
    void setDurations(const TrafficLightDurations& durations);

    /**
     * @brief Gets the current state durations.
     * @return The TrafficLightDurations struct.
     */
    [[nodiscard]] TrafficLightDurations getDurations() const;

private:
    std::string m_traffic_light_id; ///< Unique identifier.
    TrafficLightState m_current_state; ///< Current state.
    TrafficLightDurations m_durations; ///< Durations for each state.
};

#endif // PULSE_TRAFFIC_LIGHT_H
