//
// Created by andrii on 3/17/25.
//

#include "core/PulseTrafficAlgo.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include <queue>
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
    auto corridors = findMainCorridors();
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

    // Build a list of intersection IDs and sort them for deterministic order.
    std::vector<std::string> sortedIDs;
    for (auto* inter : intersections) {
        sortedIDs.push_back(inter->getId());
    }
    std::ranges::sort(sortedIDs);

    // Use the first intersection (lexicographically smallest) as the root.
    std::string rootID = sortedIDs.front();

    // BFS starting from the sorted root.
    std::unordered_map<std::string, bool> visited;
    std::queue<std::string> q;
    q.push(rootID);
    visited[rootID] = true;

    std::vector<std::string> corridorIDs;
    while (!q.empty()) {
        std::string currentID = q.front();
        q.pop();
        corridorIDs.push_back(currentID);
        auto* currentInter = m_data_manager.getIntersection(currentID);
        if (!currentInter) continue;
        // For each connected road, add neighbor if not visited.
        for (const auto& [roadID, roadConn] : currentInter->getConnectedRoads()) {
            std::string neighborID = roadConn.getConnectedIntersection().getId();
            if (!visited[neighborID]) {
                visited[neighborID] = true;
                q.push(neighborID);
            }
        }
    }

    if (!corridorIDs.empty()) {
        GreenWaveCorridor corridor;
        corridor.intersection_ids = corridorIDs;
        corridor.target_speed_m_s = 13.9; // ~50 km/h
        results.push_back(corridor);
    }
    return results;
}

void PulseTrafficAlgo::calculateGreenWaveSchedules(const std::vector<GreenWaveCorridor>& corridors)
{
    m_intersectionGreenOffset.clear();
    for (const auto& corridor : corridors) {
        double accumulatedTime = 0.0;
        for (size_t i = 0; i < corridor.intersection_ids.size(); ++i) {
            const std::string& currentID = corridor.intersection_ids[i];
            double offset = std::fmod(accumulatedTime, m_cycle_length);
            m_intersectionGreenOffset[currentID] = offset;
            if (i + 1 < corridor.intersection_ids.size()) {
                auto nextID = corridor.intersection_ids[i + 1];
                auto* currentInter = m_data_manager.getIntersection(currentID);
                auto* nextInter = m_data_manager.getIntersection(nextID);
                if (!currentInter || !nextInter) continue;
                double distance = 0.0;
                bool foundRoad = false;
                for (auto& [road_id, conn] : currentInter->getConnectedRoads()) {
                    if (conn.getConnectedIntersection().getId() == nextID) {
                        distance = conn.getDistance();
                        foundRoad = true;
                        break;
                    }
                }
                if (!foundRoad) continue;
                double travelTime = distance / corridor.target_speed_m_s;
                accumulatedTime += travelTime;
            }
        }
    }
}

void PulseTrafficAlgo::applyGreenWave(double current_sim_time)
{
    // This function updates only the local system's traffic light objects
    // based on the computed green wave schedule.
    for (auto& [interID, offset] : m_intersectionGreenOffset) {
        double localTime = std::fmod((current_sim_time - offset + m_cycle_length), m_cycle_length);
        bool isGreen = (localTime < m_green_duration);

        // Instead of calling SumoIntegration to set the state in SUMO,
        // we update our own local system's traffic light.
        auto* light = m_data_manager.getTrafficLight(interID);
        if (light) {
            if (isGreen) {
                light->setState(TrafficLightState::GREEN);
            } else {
                light->setState(TrafficLightState::RED);
            }
        }
        // Optionally, log the intended state.
        std::cout << "[PulseTrafficAlgo] Intersection " << interID << " localTime: "
                  << localTime << " -> " << (isGreen ? "GREEN" : "RED") << std::endl;
    }
}

