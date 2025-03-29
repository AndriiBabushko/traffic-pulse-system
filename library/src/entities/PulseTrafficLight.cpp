//
// Created by andrii on 3/1/25.
//

#include "entities/PulseTrafficLight.h"

#include <utility>

PulseTrafficLight::PulseTrafficLight(std::string traffic_light_id, const TrafficLightDurations& durations)
    : m_traffic_light_id(std::move(traffic_light_id)), m_current_state(TrafficLightState::RED), m_durations(durations) {}

std::string PulseTrafficLight::getId() const
{
    return m_traffic_light_id;
}

void PulseTrafficLight::setState(TrafficLightState state)
{
    m_current_state = state;
}

TrafficLightState PulseTrafficLight::getState() const
{
    return m_current_state;
}

void PulseTrafficLight::setDurations(const TrafficLightDurations& durations)
{
    m_durations = durations;
}

TrafficLightDurations PulseTrafficLight::getDurations() const
{
    return m_durations;
}
