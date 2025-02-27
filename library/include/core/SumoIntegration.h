//
// Created by andrii on 2/22/25.
//

#ifndef SUMOINTEGRATION_H
#define SUMOINTEGRATION_H

#include <string>
#include <memory>

/**
 * @class SumoIntegration
 * @brief Provides a minimal interface to start, stop, and step the SUMO simulation,
 *        plus retrieve relevant simulation data for use with the TrafficPulseLibrary.
 */
class SumoIntegration
{
public:
    /**
     * @brief Constructs a SumoIntegration object.
     * @param sumo_config_file The path to the SUMO configuration file (usually .sumocfg).
     * @param sumo_binary_path The path to the SUMO binary (e.g. "sumo" or "/usr/bin/sumo").
     */
    SumoIntegration(const std::string& sumo_config_file,
                    const std::string& sumo_binary_path);

    /**
     * @brief Starts the SUMO simulation in the background (e.g. via TraCI or a child process).
     *        This is a minimal illustration—replace with a real TraCI client if desired.
     */
    void startSimulation();

    /**
     * @brief Steps the simulation forward by one timestep.
     *        Here we might send a "simulationStep" command via TraCI or
     *        just rely on a separate child process stepping.
     */
    void stepSimulation();

    /**
     * @brief Retrieves the current traffic state from SUMO, e.g. traffic lights or vehicles.
     *        You might call TraCI methods here in a real scenario.
     * @return True if successful, false otherwise.
     */
    bool fetchSimulationData();

    /**
     * @brief Stops the SUMO simulation (optional).
     */
    void stopSimulation();

private:
    /**
     * @brief Path to the SUMO .sumocfg scenario file.
     */
    std::string m_sumo_config_file;

    /**
     * @brief Path to the SUMO binary/executable.
     */
    std::string m_sumo_binary_path;

    /**
     * @brief An example child-process handle or TraCI socket reference.
     *        In a real system, store your TraCI socket or process ID here.
     */
    int m_sumo_process_id;
};

#endif // SUMOINTEGRATION_H
