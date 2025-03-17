//
// Created by andrii on 2/25/25.
//

#include "core/IntersectionStatistics.h"
#include <algorithm>

IntersectionStatistics::IntersectionStatistics(std::string intersection_id)
    : m_intersection_id(std::move(intersection_id)),
      m_total_vehicles_passed(0),
      m_total_vehicle_waiting(0.0),
      m_total_pedestrians_passed(0),
      m_total_pedestrian_waiting(0.0)
{}

std::string IntersectionStatistics::getIntersectionId() const
{
    return m_intersection_id;
}

void IntersectionStatistics::addVehiclePass(double waiting_time /*, PulseVehicleType vehicle_type*/)
{
    m_total_vehicles_passed += 1;
    m_total_vehicle_waiting += waiting_time;
}

std::size_t IntersectionStatistics::getTotalVehiclesPassed() const
{
    return m_total_vehicles_passed;
}

double IntersectionStatistics::getTotalVehicleWaitingTime() const
{
    return m_total_vehicle_waiting;
}

double IntersectionStatistics::getAverageVehicleWaitingTime() const
{
    return (m_total_vehicles_passed == 0) ? 0.0 : (m_total_vehicle_waiting / static_cast<double>(m_total_vehicles_passed));
}

void IntersectionStatistics::addPedestrianPass(double waiting_time)
{
    m_total_pedestrians_passed += 1;
    m_total_pedestrian_waiting += waiting_time;
}

std::size_t IntersectionStatistics::getTotalPedestriansPassed() const
{
    return m_total_pedestrians_passed;
}

double IntersectionStatistics::getTotalPedestrianWaitingTime() const
{
    return m_total_pedestrian_waiting;
}

double IntersectionStatistics::getAveragePedestrianWaitingTime() const
{
    return (m_total_pedestrians_passed == 0) ? 0.0 : (m_total_pedestrian_waiting / static_cast<double>(m_total_pedestrians_passed));
}
