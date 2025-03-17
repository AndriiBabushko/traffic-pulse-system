//
// Created by andrii on 2/22/25.
//

#ifndef PULSEDATAMANAGER_H
#define PULSEDATAMANAGER_H

#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "core/SumoIntegration.h"

#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

/**
 * @class PulseDataManager
 * @brief Singleton manager that stores all traffic simulation entities (intersections, traffic lights, vehicles).
 *
 * It can sync data with a live SUMO simulation via SumoIntegration, ensuring that
 * local objects remain consistent with the real-time simulation.
 */
class PulseDataManager
{
public:
    /**
     * @brief Retrieves the singleton instance.
     * @return Reference to the single PulseDataManager.
     */
    static PulseDataManager& getInstance();

    /**
     * @brief Adds a new intersection to the data manager.
     * @throws std::invalid_argument if intersection is null
     * @throws std::runtime_error if an intersection with the same ID already exists
     */
    void addIntersection(std::unique_ptr<PulseIntersection> intersection);

    /**
     * @brief Retrieves an intersection by ID.
     * @param intersection_id The ID of the intersection to retrieve.
     * @return Pointer to the intersection, or nullptr if not found.
     */
    PulseIntersection* getIntersection(const std::string& intersection_id) const;

    /**
     * @brief Adds a new traffic light to the data manager.
     * @throws std::invalid_argument if traffic_light is null
     * @throws std::runtime_error if a traffic light with the same ID already exists
     */
    void addTrafficLight(std::unique_ptr<PulseTrafficLight> traffic_light);

    /**
     * @brief Retrieves a traffic light by ID.
     * @param traffic_light_id The ID of the traffic light.
     * @return Pointer to the traffic light, or nullptr if not found.
     */
    PulseTrafficLight* getTrafficLight(const std::string& traffic_light_id) const;

    /**
     * @brief Adds a new vehicle to the data manager.
     * @throws std::invalid_argument if vehicle is null
     * @throws std::runtime_error if a vehicle with the same ID already exists
     */
    void addVehicle(std::unique_ptr<PulseVehicle> vehicle);

    /**
     * @brief Retrieves a vehicle by ID.
     * @param vehicle_id The ID of the vehicle.
     * @return Pointer to the vehicle, or nullptr if not found.
     */
    PulseVehicle* getVehicle(const std::string& vehicle_id) const;

    /**
     * @brief Retrieves all intersections in the system.
     * @return A list of pointers to all intersections.
     */
    std::vector<PulseIntersection*> getAllIntersections() const;

    /**
     * @brief Retrieves all traffic lights in the system.
     * @return A list of pointers to all traffic lights.
     */
    std::vector<PulseTrafficLight*> getAllTrafficLights() const;

    /**
     * @brief Retrieves all vehicles in the system.
     * @return A list of pointers to all vehicles.
     */
    std::vector<PulseVehicle*> getAllVehicles() const;

    /**
     * @brief Clears all stored data (used when resetting or re-syncing).
     */
    void clearAll();

    /**
     * @brief Syncs data from SUMO the first time (or after clearing).
     *        This loads all traffic lights as intersections, plus vehicles.
     * @param sumo Reference to the SumoIntegration instance.
     */
    void syncFromSumo(const SumoIntegration &sumo);

    /**
     * @brief Updates local data from the current SUMO simulation step.
     *        Typically called each time we step the simulation.
     * @param sumo Reference to the SumoIntegration instance.
     */
    void updateFromSumo(const SumoIntegration &sumo);

    // Deleted copy constructor & assignment op for singleton
    PulseDataManager(const PulseDataManager&) = delete;
    PulseDataManager& operator=(const PulseDataManager&) = delete;

private:
    // Private constructor for singleton
    PulseDataManager() = default;

private:
    // Intersection, traffic light, and vehicle storage
    std::unordered_map<std::string, std::unique_ptr<PulseIntersection>> m_intersections;
    std::unordered_map<std::string, std::unique_ptr<PulseTrafficLight>> m_traffic_lights;
    std::unordered_map<std::string, std::unique_ptr<PulseVehicle>> m_vehicles;
};

#endif //PULSEDATAMANAGER_H
