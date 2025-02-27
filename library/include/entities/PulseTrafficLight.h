//
// Created by andrii on 1/30/25.
//

#ifndef PULSE_TRAFFIC_LIGHT_H
#define PULSE_TRAFFIC_LIGHT_H

#include <string>
#include "types/TrafficLightState.h"
#include "types/TrafficLightDurations.h"
#include "types/PulsePosition.h"

namespace Pulse {
    /**
     * @brief Class representing an individual traffic light within the simulation.
     */
    class PulseTrafficLight {
    private:
        std::string id;                     ///< Unique ID for the traffic light.
        TrafficLightState state;            ///< Current state of the traffic light.
        TrafficLightDurations durations;    ///< Durations for red, yellow, and green lights.
        PulsePosition position;             ///< Position of the traffic light.

    public:
        /**
         * @brief Constructor to initialize a traffic light.
         * @param lightId Unique identifier for the traffic light.
         * @param position Position of the traffic light.
         */
        explicit PulseTrafficLight(const std::string& lightId, const PulsePosition& position = {0.0, 0.0});

        /**
         * @brief Update the current state of the traffic light.
         * @param state The new state to be set.
         */
        void updateState(TrafficLightState state);

        /**
         * @brief Retrieve the current state of the traffic light.
         * @return Current state.
         */
        [[nodiscard]] TrafficLightState getState() const;

        /**
         * @brief Retrieve the ID of the traffic light.
         * @return ID as string.
         */
        [[nodiscard]] std::string getId() const;

        /**
         * @brief Retrieve the position of the traffic light.
         * @return A pair of X and Y coordinates.
         */
        [[nodiscard]] std::pair<double, double> getPosition() const;
    };
}

#endif // PULSE_TRAFFIC_LIGHT_H
