//
// Created by andrii on 3/01/25.
//

#include <libsumo/libsumo.h>
#include <iostream>
#include <filesystem>
#include <utility>

#include "core/SumoIntegration.h"
#include <core/PulseException.h>
#include "constants/CMakeBinaryDir.h"

SumoIntegration::SumoIntegration(std::string sumo_config, const bool bypass_config_check)
    : m_running(false)
{
    if (!bypass_config_check) {
        const std::string config_dir = std::string(CMAKE_BINARY_DIR) + "/config/sumo/";
        std::string expected_path = config_dir + sumo_config;

        if (!std::filesystem::exists(config_dir)) {
            throw PulseException(
                "SUMO config directory not found! Expected at: " + config_dir +
                "\nEnsure that the directory exists and is copied correctly.", PulseErrorCode::InvalidFilePath
            );
        }

        if (!std::filesystem::exists(expected_path)) {
            throw PulseException(
                "SUMO config file not found! Expected at: " + expected_path +
                "\nEnsure you have placed the correct file inside 'config/sumo/'.", PulseErrorCode::InvalidFilePath
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
        throw PulseException("SUMO simulation already running.", PulseErrorCode::AlreadyRunning);
    }

    std::cout << "[SumoIntegration] Starting libsumo with config: " << m_sumo_config << std::endl;
    libsumo::Simulation::start({"sumo", "-c", m_sumo_config});
    m_running = true;
    std::cout << "[SumoIntegration] SUMO simulation started via libsumo." << std::endl;
}

void SumoIntegration::stepSimulation() const {
    if (!m_running) {
        throw PulseException("Cannot step simulation: SUMO not running.", PulseErrorCode::NotRunning);
    }
    libsumo::Simulation::step();
}

void SumoIntegration::stopSimulation()
{
    if (!m_running) {
        throw PulseException("Cannot stop simulation: SUMO not running.", PulseErrorCode::NotRunning);
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
        throw PulseException("Cannot retrieve vehicles: SUMO not running.", PulseErrorCode::NotRunning);
    }
    return libsumo::Vehicle::getIDList();
}

std::pair<double, double> SumoIntegration::getVehiclePosition(const std::string& vehicle_id) const {
    if (!m_running) {
        throw PulseException("Cannot retrieve position: SUMO not running.", PulseErrorCode::NotRunning);
    }
    auto pos = libsumo::Vehicle::getPosition(vehicle_id);
    return {pos.x, pos.y};
}

std::vector<std::string> SumoIntegration::getAllTrafficLights() const {
    if (!m_running) {
        throw PulseException("Cannot retrieve traffic lights: SUMO not running.", PulseErrorCode::NotRunning);
    }
    return libsumo::TrafficLight::getIDList();
}

std::string SumoIntegration::getTrafficLightState(const std::string& tl_id) const {
    if (!m_running) {
        throw PulseException("Cannot retrieve traffic light state: SUMO not running.", PulseErrorCode::NotRunning);
    }
    return libsumo::TrafficLight::getRedYellowGreenState(tl_id);
}

void SumoIntegration::setTrafficLightState(const std::string& tl_id, const std::string& state) const {
    if (!m_running) {
        throw PulseException("Cannot set traffic light state: SUMO not running.", PulseErrorCode::NotRunning);
    }
    libsumo::TrafficLight::setRedYellowGreenState(tl_id, state);
}


std::string SumoIntegration::getVehicleType(const std::string& vehicle_id) const
{
    if (!m_running) {
        throw PulseException("Cannot get vehicle type, SUMO not running.",
                             PulseErrorCode::NotRunning);
    }

    try {
        // Example if libsumo has: libsumo::Vehicle::getTypeID(vehicle_id)
        // This returns e.g. "passenger", "truck", "bicycle", "emergency", etc.
        return libsumo::Vehicle::getTypeID(vehicle_id);
    }
    catch (const std::exception& ex) {
        throw PulseException(std::string("SumoIntegration::getVehicleType error: ") + ex.what(),
                             PulseErrorCode::ParsingError);
    }
}
