//
// Created by andrii on 3/17/25.
//

#include "core/PulseTrafficAlgo.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "utils/BFSUtils.h"
#include <iostream>
#include <cmath>
#include <algorithm>

PulseTrafficAlgo::PulseTrafficAlgo(PulseDataManager& data_manager, SumoIntegration& sumo_integration)
    : m_data_manager(data_manager),
      m_sumo_integration(sumo_integration)
{
}

void PulseTrafficAlgo::initializeGreenWave()
{
    const auto corridors = findMainCorridors();
    calculateGreenWaveSchedules(corridors);
}

void PulseTrafficAlgo::runOnce(double current_sim_time)
{
    applyGreenWave(current_sim_time);
}


std::vector<GreenWaveCorridor> PulseTrafficAlgo::findMainCorridors() const
{
    std::vector<GreenWaveCorridor> results;
    auto intersections = m_data_manager.getAllIntersections();
    if (intersections.empty()) return results;

    std::vector<std::string> sorted_ids;
    sorted_ids.reserve(intersections.size());
    for (const auto* inter : intersections) {
        sorted_ids.push_back(inter->getId());
    }
    std::ranges::sort(sorted_ids);
    if (sorted_ids.empty()) {
        return results;
    }

    // Use the lexicographically smallest intersection as the BFS root
    const std::string& root_id = sorted_ids.front();

    const auto visited_order = runBFS(root_id, [&](const std::string& node_id) {
        std::vector<std::string> neighbor_ids;
        const auto* current_inter = m_data_manager.getIntersection(node_id);
        if (!current_inter) {
            return neighbor_ids;
        }

        // For each road connection, collect neighbor intersection IDs
        for (auto& [road_id, road_conn] : current_inter->getConnectedRoads()) {
            neighbor_ids.push_back(road_conn.getConnectedIntersection().getId());
        }
        return neighbor_ids;
    });

    if (!visited_order.empty()) {
        GreenWaveCorridor corridor;
        corridor.intersection_ids = visited_order;
        corridor.target_speed_m_s = 13.9;
        results.push_back(corridor);
    }
    return results;
}

void PulseTrafficAlgo::calculateGreenWaveSchedules(const std::vector<GreenWaveCorridor>& corridors)
{
    m_intersection_green_offset.clear();
    for (const auto& corridor : corridors) {
        double accumulated_time = 0.0;

        for (size_t i = 0; i < corridor.intersection_ids.size(); ++i) {
            const std::string& current_id = corridor.intersection_ids[i];
            double offset = std::fmod(accumulated_time, m_cycle_length);
            m_intersection_green_offset[current_id] = offset;

            if (i + 1 < corridor.intersection_ids.size()) {
                auto next_id = corridor.intersection_ids[i + 1];
                const auto* current_inter = m_data_manager.getIntersection(current_id);

                if (const auto* next_inter = m_data_manager.getIntersection(next_id); !current_inter || !next_inter) continue;

                double distance = 0.0;
                bool found_road = false;

                for (auto& [road_id, conn] : current_inter->getConnectedRoads()) {
                    if (conn.getConnectedIntersection().getId() == next_id) {
                        distance = conn.getDistance();
                        found_road = true;
                        break;
                    }
                }

                if (!found_road) continue;

                double travel_time = distance / corridor.target_speed_m_s;
                accumulated_time += travel_time;
            }
        }
    }
}

void PulseTrafficAlgo::applyGreenWave(const double current_sim_time)
{
    // This function updates only the local system's traffic light objects
    // based on the computed green wave schedule.
    for (auto& [inter_id, offset] : m_intersection_green_offset) {
        const double local_time = std::fmod((current_sim_time - offset + m_cycle_length), m_cycle_length);
        const bool is_green = (local_time < m_green_duration);

        if (auto* light = m_data_manager.getTrafficLight(inter_id)) {
            if (is_green) {
                light->setState(TrafficLightState::GREEN);
            } else {
                light->setState(TrafficLightState::RED);
            }
        }

        std::cout << "[PulseTrafficAlgo] Intersection " << inter_id << " localTime: "
                  << local_time << " -> " << (is_green ? "GREEN" : "RED") << std::endl;
    }
}

