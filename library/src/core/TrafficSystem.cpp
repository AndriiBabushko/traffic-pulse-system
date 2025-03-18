//
// Created by andrii on 3/1/25.
//

#include "core/TrafficSystem.h"
#include "core/SumoIntegration.h"
#include "core/PulseDataManager.h"
#include "core/PulseTrafficAlgo.h"
#include "core/Logger.h"
#include "constants/SumoConfigPath.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <algorithm>

TrafficSystem::TrafficSystem(double updateFrequency)
    : m_updateFrequency(updateFrequency),
      m_dataManager(PulseDataManager::getInstance())
{
    // Create our SumoIntegration using a defined config file.
    // Later, this might be replaced by a different data source.
    m_sumo = std::make_unique<SumoIntegration>(SUMO_CONFIG_PATH);

    // Create the traffic algorithm module with the data manager and SumoIntegration.
    m_algo = std::make_unique<PulseTrafficAlgo>(m_dataManager, *m_sumo);
}

TrafficSystem::~TrafficSystem() {
    if(m_sumo->isRunning()){
        m_sumo->stopSimulation();
    }
}

void TrafficSystem::attach(std::shared_ptr<IObserver> observer) {
    m_observers.push_back(observer);
}

void TrafficSystem::detach(std::shared_ptr<IObserver> observer) {
    auto it = std::remove(m_observers.begin(), m_observers.end(), observer);
    m_observers.erase(it, m_observers.end());
}

void TrafficSystem::notify(const std::string& eventDescription) {
    for (const auto& obs : m_observers) {
        obs->update(eventDescription);
    }
}

class PulseDataManager& TrafficSystem::getDataManager() const {
    return m_dataManager;
}

void TrafficSystem::run() {
    try {
        // Start the simulation
        m_sumo->startSimulation();
        notify("Event: SIMULATION_START");

        // For demonstration, we run a fixed number of simulation steps.
        const int numSteps = 20;
        double simTime = 0.0;
        for (int i = 0; i < numSteps; ++i) {
            // Step simulation (in real usage, update data manager from Sumo here)
            m_sumo->stepSimulation();

            // Here, you could call a method to update PulseDataManager from Sumo.
            // For now, assume data manager is updated externally or by the algo.

            // Run traffic algorithm (green wave)
            m_algo->runOnce(simTime);

            // Build an event message.
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
