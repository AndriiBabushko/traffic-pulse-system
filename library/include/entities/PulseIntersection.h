//
// Created by andrii on 1/30/25.
//

#ifndef PULSE_INTERSECTION_H
#define PULSE_INTERSECTION_H

#include <vector>
#include <string>

#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"
#include <types/AverageWaitingTimes.h>
#include "types/PulsePosition.h"

namespace Pulse {
    /**
     * @brief Class representing an intersection in the simulation.
     * It manages multiple traffic lights and notifies observers of state changes.
     */
    class PulseIntersection {
    private:
        std::string id;                                           ///< Unique ID for the intersection.
        std::vector<PulseTrafficLight*> traffic_lights;           ///< List of traffic lights at this intersection.
        PulseVehicle vehicles;                                    ///< Current vehicles at the intersection.
        PulsePosition position;                                   ///< Position of the intersection.
        AverageWaitingTimes average_waiting_times;                ///< Average waiting times for vehicles and pedestrians.

    public:
        /**
         * @brief Constructor to initialize the intersection.
         * @param intersection_id Unique identifier for the intersection.
         * @param position Position of the intersection.
         */
        explicit PulseIntersection(const std::string& intersection_id, const PulsePosition &position);

        /**
         * @brief Add a traffic light to the intersection.
         * @param light Pointer to a PulseTrafficLight object.
         */
        void addTrafficLight(PulseTrafficLight* light);

        /**
         * @brief Get the current vehicle count.
         * @return Vehicle count as an integer.
         */
        [[nodiscard]] int getVehicleCount() const;

        /**
         * @brief Update the average waiting time for vehicles and pedestrians.
         * @param vehicles_time Average waiting time for vehicles in seconds.
         * @param pedestrians_time Average waiting time for pedestrians in seconds.
         */
        void updateAverageWT(double vehicles_time, double pedestrians_time);

        /**
         * @brief Get the average waiting time for vehicles.
         * @return Average waiting time in seconds for vehicles and pedestrians.
         */
        [[nodiscard]] double getAverageWT() const;

        /**
         * @brief Retrieve intersection ID.
         * @return Intersection ID as string.
         */
        [[nodiscard]] std::string getId() const;

        /**
         * @brief Retrieve the position of the intersection.
         * @return A pair of X and Y coordinates.
         */
        [[nodiscard]] std::pair<double, double> getPosition() const;
    };
}

#endif // PULSE_INTERSECTION_H
