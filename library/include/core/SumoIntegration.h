//
// Created by andrii on 2/22/25.
//

#ifndef SUMOINTEGRATION_H
#define SUMOINTEGRATION_H

#pragma once

#include <string>
#include <vector>

/**
 * @class SumoIntegration
 * @brief Demonstrates using libsumo for starting, stepping, and controlling SUMO from C++.
 */
class SumoIntegration
{
public:
    /**
     * @brief Constructs a SumoIntegration object.
     * @param sumo_config The path to a SUMO config file (.sumocfg).
     */
    explicit SumoIntegration(std::string  sumo_config);

    /**
     * @brief Starts the SUMO simulation using libsumo.
     */
    void startSimulation();

    /**
     * @brief Steps the simulation forward by one timestep.
     */
    void stepSimulation() const;

    /**
     * @brief Stops the SUMO simulation.
     */
    void stopSimulation();

    /**
     * @brief Checks if the simulation is running.
     */
    [[nodiscard]] virtual bool isRunning() const;

    /**
     * @brief Retrieves all vehicle IDs.
     */
    [[nodiscard]] virtual std::vector<std::string> getAllVehicles() const;

    /**
     * @brief Retrieves the (x,y) position of a given vehicle by ID.
     */
    [[nodiscard]] virtual std::pair<double, double> getVehiclePosition(const std::string& vehicle_id) const;

    /**
     * @brief Retrieves a list of traffic light IDs.
     */
    [[nodiscard]] virtual std::vector<std::string> getAllTrafficLights() const;

    /**
     * @brief Retrieves a traffic light's state as a string (e.g., "rGrG").
     */
    [[nodiscard]] virtual std::string getTrafficLightState(const std::string& tl_id) const;

    /**
     * @brief Sets the state (e.g., "rGrG") of the specified traffic light.
     */
    void setTrafficLightState(const std::string& tl_id, const std::string& state) const;

private:
    std::string m_sumo_config;
    bool m_running;
};

#endif // SUMOINTEGRATION_H
