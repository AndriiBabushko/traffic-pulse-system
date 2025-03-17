//
// Created by andrii on 2/25/25.
//

#include "entities/PulseIntersection.h"

#include <stdexcept>

PulseIntersection::PulseIntersection(const std::string &intersection_id, const PulsePosition &position)
    : m_intersection_id(intersection_id), m_position(position), m_statistics(intersection_id) {}

std::string PulseIntersection::getId() const
{
    return m_intersection_id;
}

PulsePosition PulseIntersection::getPosition() const
{
    return m_position;
}

void PulseIntersection::addRoadConnection(int road_id, PulseIntersection* intersection, PulseTrafficLight* traffic_light, double distance)
{
    if (!intersection || !traffic_light)
    {
        throw std::invalid_argument("Invalid intersection or traffic light reference.");
    }

    if (m_connected_roads.find(road_id) != m_connected_roads.end())
    {
        throw std::runtime_error("Road connection with this ID already exists.");
    }

    m_connected_roads.emplace(road_id, PulseRoadConnection(*intersection, *traffic_light, distance));
}

const std::unordered_map<int, PulseRoadConnection>& PulseIntersection::getConnectedRoads() const
{
    return m_connected_roads;
}

IntersectionStatistics& PulseIntersection::getStatistics()
{
    return m_statistics;
}
