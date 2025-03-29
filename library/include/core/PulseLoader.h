//
// Created by andrii on 3/20/25.
//
#pragma once

#ifndef PULSELOADER_H
#define PULSELOADER_H

#include <string>
#include "interfaces/ISubject.h"
#include "core/PulseDataManager.h"

/**
 * @class PulseLoader
 * @brief Loads and parses a SUMO .net.xml file, populating PulseDataManager with intersections,
 *        traffic lights, etc. It notifies its subject (e.g. TrafficSystem) about loading progress.
 */
class PulseLoader {
public:
    /**
     * @brief Constructs a PulseLoader with a reference to PulseDataManager and a path to the net file.
     * @param data_manager Reference to the data manager.
     * @param net_file Path to the SUMO .net.xml.
     * @param subject An ISubject (e.g. TrafficSystem) to notify about loading progress.
     */
    PulseLoader(PulseDataManager& data_manager, std::string net_file, ISubject& subject);

    /**
     * @brief Loads network data from the specified .net.xml file into the PulseDataManager.
     *        Notifies LOADING_START, LOADING_PROGRESS, LOADING_COMPLETE events during the process.
     *
     * @throws PulseException if the file is missing or invalid (e.g. parsing error).
     */
    void loadNetworkData() const;

private:
    /**
     * @brief Generates a simple incremental ID for road connections.
     * @return An integer ID unique for each call in the current session.
     */
    static int generateRoadID();

    PulseDataManager& m_data_manager;
    std::string       m_net_file_path;
    ISubject&         m_subject;
};

#endif //PULSELOADER_H
