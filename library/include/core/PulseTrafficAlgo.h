//
// Created by andrii on 2/25/25.
//

#ifndef PULSETRAFFICALGO_H
#define PULSETRAFFICALGO_H

#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "core/PulseDataManager.h"
#include "core/SumoIntegration.h"
#include "types/GreenWaveCoridor.h"

/**
 * @class PulseTrafficAlgo
 * @brief Implements a green-wave traffic control approach using BFS-based corridor detection
 *        and a 90-second cycle (45s green, 45s red).
 */
class PulseTrafficAlgo
{
public:
    /**
     * @brief Constructs the traffic algorithm with references to data manager and sumo integration.
     * @param data_manager Reference to PulseDataManager for local entity data.
     * @param sumo_integration Reference to SumoIntegration for real-time control of lights.
     */
    PulseTrafficAlgo(PulseDataManager& data_manager, SumoIntegration& sumo_integration);

    /**
     * @brief Initializes the green wave schedules by finding corridors and computing offsets.
     *        Typically called once after the system is loaded with intersections.
     */
    void initializeGreenWave();

    /**
     * @brief Runs the green wave logic at a given simulation time.
     * @param current_sim_time Current simulation time (e.g., from SUMO or a global clock).
     */
    void runOnce(double current_sim_time);

private:
    /**
     * @brief Finds major corridors in the intersection graph using BFS or a custom approach.
     *        Here we just pick one or two main paths for demonstration.
     */
    std::vector<GreenWaveCorridor> findMainCorridors() const;

    /**
     * @brief Calculates offsets for each intersection in each corridor based on road distances
     *        and the corridor’s target speed. Offsets stored in m_intersectionGreenOffset.
     */
    void calculateGreenWaveSchedules(const std::vector<GreenWaveCorridor>& corridors);

    /**
     * @brief Applies the green wave offsets at the current simulation time by setting traffic lights to green or red.
     */
    void applyGreenWave(double current_sim_time);

private:
    PulseDataManager& m_data_manager;
    SumoIntegration&  m_sumo_integration;
    std::unordered_map<std::string, double> m_intersection_green_offset; ///< Offset for each intersection.
    double m_cycle_length   = 90.0;  ///< Total cycle duration in seconds.
    double m_green_duration = 45.0;  ///< Duration of green phase.
};

#endif //PULSETRAFFICALGO_H
