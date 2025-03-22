//
// Created by andrii on 3/20/25.
//
#pragma once

#ifndef PULSELOADER_H
#define PULSELOADER_H

#include <string>

class PulseDataManager;

/**
 * @class PulseLoader
 * @brief Responsible for loading and parsing SUMO .net.xml files, creating intersections,
 *        traffic lights, and road connections in the PulseDataManager.
 */
class PulseLoader
{
public:
    /**
     * @brief Constructs a PulseLoader with reference to the data manager and path to net file.
     * @param data_manager Reference to the singleton or external PulseDataManager.
     * @param netFilePath Path to the SUMO .net.xml file (uncompressed).
     */
    PulseLoader(PulseDataManager& data_manager, std::string  netFilePath);

    /**
     * @brief Parses the network file and populates the PulseDataManager with intersections,
     *        traffic lights, and naive road connections.
     * @throws std::runtime_error if parsing fails or required XML elements are missing.
     */
    void loadNetworkData() const;

private:
    /**
     * @brief Generates a simple incremental ID for road connections.
     * @return An integer ID unique for each call in the current session.
     */
    static int generateRoadID();

private:
    PulseDataManager& m_data_manager;
    std::string       m_netFilePath;
};

#endif //PULSELOADER_H
