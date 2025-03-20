//
// Created by andrii on 3/1/25.
//

#include "core/TrafficSystem.h"
#include "core/SumoIntegration.h"
#include "core/PulseDataManager.h"
#include "core/PulseTrafficAlgo.h"
#include "core/PulseLoader.h"
#include "core/Logger.h"
#include "constants/SumoConfigPath.h"
#include "constants/SumoNetPath.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <algorithm>

TrafficSystem::TrafficSystem(double updateFrequency)
    : m_dataManager(PulseDataManager::getInstance()),
      m_updateFrequency(updateFrequency)
{
    m_sumo = std::make_unique<SumoIntegration>(SUMO_CONFIG_PATH);
    m_algo = std::make_unique<PulseTrafficAlgo>(m_dataManager, *m_sumo);
}

TrafficSystem::~TrafficSystem() {
    if (m_sumo->isRunning()) {
        m_sumo->stopSimulation();
    }
}

void TrafficSystem::attach(const std::shared_ptr<IObserver> observer) {
    m_observers.push_back(observer);
}

void TrafficSystem::detach(const std::shared_ptr<IObserver> observer) {
    auto it = std::ranges::remove(m_observers, observer).begin();
    m_observers.erase(it, m_observers.end());
}

void TrafficSystem::notify(const std::string& eventDescription) {
    for (const auto& obs : m_observers) {
        obs->update(eventDescription);
    }
}

PulseDataManager& TrafficSystem::getDataManager() const {
    return m_dataManager;
}

void TrafficSystem::requestStop() {
    m_stopRequested.store(true);
}

void TrafficSystem::run() {
    try {
        m_sumo->startSimulation();
        notify("Event: SIMULATION_START");

        // Use PulseLoader to load static network data.
        // Assume we have a constant SUMO_NET_PATH defined, pointing to an uncompressed net file.
        PulseLoader loader(m_dataManager, SUMO_NET_PATH);
        loader.loadNetworkData();
        notify("Event: LOADING_COMPLETE");

        double simTime = 0.0;
        while (!m_stopRequested.load()) {
            m_sumo->stepSimulation();
            m_algo->runOnce(simTime);
            std::stringstream ss;
            ss << "Event: SIMULATION_STEP, time: " << simTime;
            notify(ss.str());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            simTime += m_updateFrequency;
        }

        m_sumo->stopSimulation();
        notify("Event: SIMULATION_END");
    } catch (const std::exception& ex) {
        notify(std::string("Error in TrafficSystem: ") + ex.what());
    }
}
