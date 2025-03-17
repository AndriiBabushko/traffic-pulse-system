//
// Created by andrii on 3/1/25.
//

#include "core/TrafficSystem.h"

void TrafficSystem::initialize()
{
    m_sumoIntegration->startSimulation();
    auto& manager = PulseDataManager::getInstance();
    manager.syncFromSumo(*m_sumoIntegration);
}

void TrafficSystem::stepSimulation()
{
    m_sumoIntegration->stepSimulation();
    auto& manager = PulseDataManager::getInstance();
    manager.updateFromSumo(*m_sumoIntegration);
}