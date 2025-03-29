//
// Created by andrii on 2/22/25.
//

#pragma once
#ifndef SUMOINTEGRATION_H
#define SUMOINTEGRATION_H

#include <string>
#include <vector>

/**
 * @class SumoIntegration
 * @brief Demonstrates using libsumo for starting, stepping, and controlling SUMO from C++.
 *
 * The constructor accepts an optional flag to bypass filesystem configuration checks.
 * This is useful for mocking purposes.
 */
class SumoIntegration
{
public:
    /**
     * @brief Constructs a SumoIntegration object.
     * @param sumo_config The path to a SUMO config file (.sumocfg).
     * @param bypass_config_check If true, bypasses the filesystem configuration checks (for testing/mocking).
     */
    explicit SumoIntegration(std::string sumo_config, bool bypass_config_check = false);

    virtual ~SumoIntegration() = default;

    /**
     * @brief Starts the SUMO simulation using libsumo.
     */
    virtual void startSimulation();

    /**
     * @brief Steps the simulation forward by one timestep.
     */
    virtual void stepSimulation() const;

    /**
     * @brief Stops the SUMO simulation.
     */
    virtual void stopSimulation();

    /**
     * @brief Checks if the simulation is running.
     * @return True if the simulation is running, false otherwise.
     */
    [[nodiscard]] virtual bool isRunning() const;

    /**
     * @brief Retrieves all vehicle IDs.
     * @return A vector of vehicle IDs.
     */
    [[nodiscard]] virtual std::vector<std::string> getAllVehicles() const;

    /**
     * @brief Retrieves the (x,y) position of a given vehicle by ID.
     */
    [[nodiscard]] virtual std::pair<double, double> getVehiclePosition(const std::string& vehicle_id) const;

    /**
     * @brief Retrieves a list of traffic light IDs.
     * @return A vector of traffic light IDs.
     */
    [[nodiscard]] virtual std::vector<std::string> getAllTrafficLights() const;

    /**
     * @brief Retrieves a traffic light's state as a string (e.g., "rGrG").
     */
    [[nodiscard]] virtual std::string getTrafficLightState(const std::string& tl_id) const;

    /**
     * @brief Sets the state (e.g., "rGrG") of the specified traffic light.
     */
    virtual void setTrafficLightState(const std::string& tl_id, const std::string& state) const;

    /**
     * @brief Retrieves the "type" string of a vehicle from SUMO (e.g., "passenger", "truck", "emergency").
     * @param vehicle_id The ID of the vehicle in SUMO.
     * @return A string describing the vehicle type.
     * @throws PulseException if SUMO is not running or if there's an underlying SUMO error.
     */
    [[nodiscard]] virtual std::string getVehicleType(const std::string& vehicle_id) const;
protected:
    std::string m_sumo_config; ///< Path to the SUMO configuration file.
    bool m_running;            ///< Whether the simulation is running.
};

#endif // SUMOINTEGRATION_H
