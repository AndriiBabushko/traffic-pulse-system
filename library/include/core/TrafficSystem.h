//
// Created by andrii on 2/22/25.
//

#ifndef TRAFFICSYSTEM_H
#define TRAFFICSYSTEM_H

#pragma once

#include <memory>
#include "core/PulseDataManager.h"
#include "core/SumoIntegration.h"

/**
 * @class TrafficSystem
 * @brief Controls the overall traffic simulation, handling initialization, SUMO interaction, and updates.
 */
class TrafficSystem
{
public:
    /**
     * @brief Retrieves the singleton instance of TrafficSystem.
     * @return Reference to the singleton TrafficSystem.
     */
    static TrafficSystem& getInstance();

    /**
     * @brief Initializes the traffic simulation using SUMO.
     * This function starts SUMO and loads intersections, roads, and traffic lights.
     */
    void initialize();

    /**
     * @brief Runs the simulation step.
     * This function steps SUMO forward and updates traffic lights, vehicles, and statistics.
     */
    void stepSimulation();

    /**
     * @brief Stops the traffic simulation.
     */
    void stopSimulation();

    /**
     * @brief Retrieves the system-wide data manager.
     * @return Reference to the PulseDataManager.
     */
    PulseDataManager& getDataManager();

private:
    /**
     * @brief Private constructor for singleton pattern.
     */
    TrafficSystem();

    /**
     * @brief Deleted copy constructor and assignment operator.
     */
    TrafficSystem(const TrafficSystem&) = delete;
    TrafficSystem& operator=(const TrafficSystem&) = delete;

private:
    std::unique_ptr<SumoIntegration> m_sumoIntegration; ///< SUMO integration handler.
};

#endif //TRAFFICSYSTEM_H
