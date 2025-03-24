//
// Created by andrii on 3/01/25.
//

#include <libsumo/libsumo.h>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <utility>

#include "core/SumoIntegration.h"

#include "constants/CMakeBinaryDir.h"

SumoIntegration::SumoIntegration(std::string sumo_config, const bool bypassConfigCheck)
    : m_running(false)
{
    if (!bypassConfigCheck) {
        std::string config_dir = std::string(CMAKE_BINARY_DIR) + "/config/sumo/";

        std::string expected_path = config_dir + sumo_config;

        if (!std::filesystem::exists(config_dir)) {
            throw std::runtime_error(
                "SUMO config directory not found! Expected at: " + config_dir +
                "\nEnsure that the directory exists and is copied correctly."
            );
        }
        if (!std::filesystem::exists(expected_path)) {
            throw std::runtime_error(
                "SUMO config file not found! Expected at: " + expected_path +
                "\nEnsure you have placed the correct file inside 'config/sumo/'."
            );
        }
        m_sumo_config = std::move(expected_path);
    } else {
        // Bypass file checks for testing/mocking purposes.
        m_sumo_config = std::move(sumo_config);
    }
    std::cout << "[INFO] Using SUMO config file: " << m_sumo_config << std::endl;
}

void SumoIntegration::startSimulation()
{
    if (m_running) {
        throw std::runtime_error("SUMO simulation already running.");
    }

    std::cout << "[SumoIntegration] Starting libsumo with config: " << m_sumo_config << std::endl;
    libsumo::Simulation::start({"sumo", "-c", m_sumo_config});
    m_running = true;
    std::cout << "[SumoIntegration] SUMO simulation started via libsumo." << std::endl;
}

void SumoIntegration::stepSimulation() const {
    if (!m_running) {
        throw std::runtime_error("Cannot step simulation: SUMO not running.");
    }
    libsumo::Simulation::step();
}

void SumoIntegration::stopSimulation()
{
    if (!m_running) {
        throw std::runtime_error("Cannot stop simulation: SUMO not running.");
    }
    std::cout << "[SumoIntegration] Stopping libsumo simulation..." << std::endl;
    libsumo::Simulation::close();
    m_running = false;
    std::cout << "[SumoIntegration] SUMO simulation stopped." << std::endl;
}

bool SumoIntegration::isRunning() const {
    return m_running;
}

std::vector<std::string> SumoIntegration::getAllVehicles() const {
    if (!m_running) {
        throw std::runtime_error("Cannot retrieve vehicles: SUMO not running.");
    }
    return libsumo::Vehicle::getIDList();
}

std::pair<double, double> SumoIntegration::getVehiclePosition(const std::string& vehicle_id) const {
    if (!m_running) {
        throw std::runtime_error("Cannot retrieve position: SUMO not running.");
    }
    auto pos = libsumo::Vehicle::getPosition(vehicle_id);
    return {pos.x, pos.y};
}

std::vector<std::string> SumoIntegration::getAllTrafficLights() const {
    if (!m_running) {
        throw std::runtime_error("Cannot retrieve traffic lights: SUMO not running.");
    }
    return libsumo::TrafficLight::getIDList();
}

std::string SumoIntegration::getTrafficLightState(const std::string& tl_id) const {
    if (!m_running) {
        throw std::runtime_error("Cannot retrieve traffic light state: SUMO not running.");
    }
    return libsumo::TrafficLight::getRedYellowGreenState(tl_id);
}

void SumoIntegration::setTrafficLightState(const std::string& tl_id, const std::string& state) const {
    if (!m_running) {
        throw std::runtime_error("Cannot set traffic light state: SUMO not running.");
    }
    libsumo::TrafficLight::setRedYellowGreenState(tl_id, state);
}
