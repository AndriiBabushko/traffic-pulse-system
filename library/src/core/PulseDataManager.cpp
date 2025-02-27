//
// Created by andrii on 2/25/25.
//

#include "core/PulseDataManager.h"

PulseDataManager& PulseDataManager::getInstance()
{
    static PulseDataManager instance;
    return instance;
}

void PulseDataManager::addIntersection(std::unique_ptr<PulseIntersection> intersection)
{
    int id = intersection->getId();
    m_intersections[id] = std::move(intersection);
}

PulseIntersection* PulseDataManager::getIntersection(int intersection_id) const
{
    auto it = m_intersections.find(intersection_id);
    return (it != m_intersections.end()) ? it->second.get() : nullptr;
}

void PulseDataManager::addTrafficLight(std::unique_ptr<PulseTrafficLight> traffic_light)
{
    int id = traffic_light->getId();
    m_traffic_lights[id] = std::move(traffic_light);
}

PulseTrafficLight* PulseDataManager::getTrafficLight(int traffic_light_id) const
{
    auto it = m_traffic_lights.find(traffic_light_id);
    return (it != m_traffic_lights.end()) ? it->second.get() : nullptr;
}

void PulseDataManager::addVehicle(std::unique_ptr<PulseVehicle> vehicle)
{
    std::string vehicle_id = vehicle->getId();
    m_vehicles[vehicle_id] = std::move(vehicle);
}

PulseVehicle* PulseDataManager::getVehicle(const std::string& vehicle_id) const
{
    auto it = m_vehicles.find(vehicle_id);
    return (it != m_vehicles.end()) ? it->second.get() : nullptr;
}

void PulseDataManager::clearAll()
{
    m_intersections.clear();
    m_traffic_lights.clear();
    m_vehicles.clear();
}
