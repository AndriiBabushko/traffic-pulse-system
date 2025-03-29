//
// Created by andrii on 3/1/25.
//

#include "core/TrafficSystem.h"
#include "core/SumoIntegration.h"
#include "core/PulseDataManager.h"
#include "core/PulseTrafficAlgo.h"
#include "core/PulseLoader.h"
#include "constants/SumoConfigPath.h"
#include "constants/SumoNetPath.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <algorithm>

TrafficSystem::TrafficSystem(const double update_frequency)
    : m_data_manager(PulseDataManager::getInstance())
    , m_update_frequency(update_frequency)
{
    m_sumo = std::make_unique<SumoIntegration>(SUMO_CONFIG_PATH);
    m_algo = std::make_unique<PulseTrafficAlgo>(m_data_manager, *m_sumo);
}

TrafficSystem::~TrafficSystem() {
    if (m_sumo->isRunning()) {
        m_sumo->stopSimulation();
    }
}

void TrafficSystem::attach(const std::shared_ptr<IObserver> observer) {
    if (std::ranges::find(m_observers, observer) == m_observers.end()) {
        m_observers.push_back(observer);
    }
}

void TrafficSystem::detach(const std::shared_ptr<IObserver> observer) {
    const auto it = std::ranges::remove(m_observers, observer).begin();
    m_observers.erase(it, m_observers.end());
}

void TrafficSystem::notify(const PulseEvent& event) {
    for (auto& obs : m_observers) {
        if (obs) {
            obs->update(event);
        }
    }
}

PulseDataManager& TrafficSystem::getDataManager() const {
    return m_data_manager;
}

void TrafficSystem::requestStop() {
    m_stop_requested.store(true);
}

void TrafficSystem::run() {
    try {
        m_sumo->startSimulation();

        notify({PulseEvents::SIMULATION_START, "Simulation started", {}});

        const std::string config_dir = std::string(CMAKE_BINARY_DIR) + "/config/sumo/";
        const std::string expected_path = config_dir + SUMO_NET_PATH;

        const PulseLoader loader(m_data_manager, expected_path, *this);
        loader.loadNetworkData();

        double sim_time = 0.0;
        while (!m_stop_requested.load()) {
            m_sumo->stepSimulation();
            m_algo->runOnce(sim_time);

            std::stringstream ss;
            ss << "Simulation step at time: " << sim_time;
            notify({PulseEvents::SIMULATION_STEP, ss.str(), {}});

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            sim_time += m_update_frequency;
        }

        m_sumo->stopSimulation();

        notify({PulseEvents::SIMULATION_END, "Simulation ended", {}});
    } catch (const std::exception& ex) {
        notify({
            PulseEvents::SIMULATION_END,
            std::string("Error in TrafficSystem: ") + ex.what(),
            {}
        });
    }
}
