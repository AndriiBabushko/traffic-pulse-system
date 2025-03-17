//
// Created by andrii on 3/1/25.
//

#include "entities/PulseRoadConnection.h"

PulseRoadConnection::PulseRoadConnection(PulseIntersection& intersection, PulseTrafficLight& traffic_light, double distance)
    : m_connected_intersection(intersection), m_traffic_light(traffic_light), m_distance(distance) {}

PulseIntersection& PulseRoadConnection::getConnectedIntersection() const
{
    return m_connected_intersection;
}

PulseTrafficLight& PulseRoadConnection::getTrafficLight() const
{
    return m_traffic_light;
}

double PulseRoadConnection::getDistance() const
{
    return m_distance;
}

void PulseRoadConnection::setTrafficLight(PulseTrafficLight& traffic_light)
{
    m_traffic_light = traffic_light;
}

void PulseRoadConnection::setDistance(double distance)
{
    m_distance = distance;
}
