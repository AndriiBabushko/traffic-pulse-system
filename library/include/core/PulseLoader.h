//
// Created by andrii on 3/20/25.
//
#pragma once

#ifndef PULSELOADER_H
#define PULSELOADER_H

#include <string>
#include "pugixml.hpp"
#include "core/PulseDataManager.h"
#include "core/SumoIntegration.h"

/**
 * @class PulseLoader
 * @brief Parses the SUMO network file using pugixml and loads static network data
 *        (intersections, traffic lights, and road connections) into PulseDataManager.
 *
 * The loader reports progress via console messages (which you can later extend to use
 * your event/observer system).
 */
class PulseLoader {
public:
    /**
     * @brief Constructs a PulseLoader.
     * @param dataManager Reference to the PulseDataManager to populate.
     * @param netFilePath The path to the uncompressed SUMO network file (net.xml).
     */
    PulseLoader(PulseDataManager& dataManager, std::string  netFilePath);

    /**
     * @brief Loads network data by parsing the net file and populates the DataManager.
     */
    void loadNetworkData() const;

private:
    PulseDataManager& m_dataManager;
    std::string m_netFilePath;

    void parseJunctions(const pugi::xml_document& doc) const;
    void parseTrafficLights(const pugi::xml_document& doc) const;
    void parseEdges(const pugi::xml_document& doc) const;
};

#endif //PULSELOADER_H
