//
// Created by andrii on 2/25/25.
//

#include "entities/PulseIntersection.h"

PulseIntersection::PulseIntersection(int intersection_id, const PulsePosition& position)
    : m_intersection_id(intersection_id), m_position(position), m_statistics(intersection_id) {}

int PulseIntersection::getId() const
{
    return m_intersection_id;
}

PulsePosition PulseIntersection::getPosition() const
{
    return m_position;
}

void PulseIntersection::addTrafficLight(std::unique_ptr<PulseTrafficLight> traffic_light)
{
    m_traffic_lights.push_back(std::move(traffic_light));
}

std::vector<PulseTrafficLight*> PulseIntersection::getTrafficLights() const
{
    std::vector<PulseTrafficLight*> lights;
    for (const auto& light : m_traffic_lights)
    {
        lights.push_back(light.get());
    }
    return lights;
}

void PulseIntersection::addVehicle(std::unique_ptr<PulseVehicle> vehicle)
{
    m_vehicles.push_back(std::move(vehicle));
}

void PulseIntersection::removeVehicle(const std::string& vehicle_id)
{
    m_vehicles.erase(
        std::remove_if(m_vehicles.begin(), m_vehicles.end(),
            [&vehicle_id](const std::unique_ptr<PulseVehicle>& vehicle)
            {
                return vehicle->getId() == vehicle_id;
            }),
        m_vehicles.end());
}

std::vector<PulseVehicle*> PulseIntersection::getVehicles() const
{
    std::vector<PulseVehicle*> vehicles;
    for (const auto& vehicle : m_vehicles)
    {
        vehicles.push_back(vehicle.get());
    }
    return vehicles;
}

IntersectionStatistics& PulseIntersection::getStatistics()
{
    return m_statistics;
}
