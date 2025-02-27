//
// Created by andrii on 2/22/25.
//

#ifndef PULSEDATAMANAGER_H
#define PULSEDATAMANAGER_H

#include <unordered_map>
#include <memory>
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

/**
 * @class PulseDataManager
 * @brief Singleton manager that stores all traffic simulation entities.
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
     * @brief Adds or updates an intersection in the data manager.
     * @param intersection A unique_ptr to the intersection object to store.
     */
    void addIntersection(std::unique_ptr<PulseIntersection> intersection);

    /**
     * @brief Retrieves a pointer to the PulseIntersection with the given ID.
     * @param intersection_id The unique identifier for the intersection.
     * @return Pointer to the PulseIntersection or nullptr if not found.
     */
    PulseIntersection* getIntersection(int intersection_id) const;

    /**
     * @brief Adds or updates a traffic light in the data manager.
     * @param traffic_light A unique_ptr to the traffic light object.
     */
    void addTrafficLight(std::unique_ptr<PulseTrafficLight> traffic_light);

    /**
     * @brief Retrieves a pointer to the PulseTrafficLight with the given ID.
     * @param traffic_light_id The unique identifier for the traffic light.
     * @return Pointer to the PulseTrafficLight or nullptr if not found.
     */
    PulseTrafficLight* getTrafficLight(int traffic_light_id) const;

    /**
     * @brief Adds or updates a vehicle in the data manager.
     * @param vehicle A unique_ptr to the vehicle object.
     */
    void addVehicle(std::unique_ptr<PulseVehicle> vehicle);

    /**
     * @brief Retrieves a pointer to the PulseVehicle with the given ID.
     * @param vehicle_id The unique identifier for the vehicle.
     * @return Pointer to the PulseVehicle or nullptr if not found.
     */
    PulseVehicle* getVehicle(const std::string& vehicle_id) const;

    /**
     * @brief Clears all stored data (used when resetting the simulation).
     */
    void clearAll();

private:
    /**
     * @brief Private constructor for singleton pattern.
     */
    PulseDataManager() = default;

    /**
     * @brief Deleted copy constructor and assignment operator to prevent duplicates.
     */
    PulseDataManager(const PulseDataManager&) = delete;
    PulseDataManager& operator=(const PulseDataManager&) = delete;

private:
    std::unordered_map<int, std::unique_ptr<PulseIntersection>> m_intersections;
    std::unordered_map<int, std::unique_ptr<PulseTrafficLight>> m_traffic_lights;
    std::unordered_map<std::string, std::unique_ptr<PulseVehicle>> m_vehicles;
};

#endif //PULSEDATAMANAGER_H
