//
// Created by andrii on 3/20/25.
//

#include "core/PulseLoader.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "types/PulsePosition.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

// Constructor
PulseLoader::PulseLoader(PulseDataManager& dataManager, std::string  netFilePath)
    : m_dataManager(dataManager), m_netFilePath(std::move(netFilePath)) {
}

// Main loading function
void PulseLoader::loadNetworkData() const {
    std::cout << "[PulseLoader] LOADING_START: Parsing network file: " << m_netFilePath << std::endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_netFilePath.c_str());
    if (!result) {
        std::stringstream ss;
        ss << "Failed to parse network file: " << result.description();
        throw std::runtime_error(ss.str());
    }
    std::cout << "[PulseLoader] Network file parsed successfully." << std::endl;

    // First, parse junctions to create intersections.
    parseJunctions(doc);
    // Next, parse traffic lights.
    parseTrafficLights(doc);
    // Finally, parse edges to create road connections.
    parseEdges(doc);

    std::cout << "[PulseLoader] LOADING_COMPLETE: Network data loaded." << std::endl;
}

// Parse <junction> elements
void PulseLoader::parseJunctions(const pugi::xml_document& doc) const {
    pugi::xml_node net = doc.child("net");
    pugi::xml_node junctions = net.child("junctions");
    if (!junctions) {
        throw std::runtime_error("No <junctions> element found in network file.");
    }

    int count = 0;
    for (pugi::xml_node junction : junctions.children("junction")) {
        std::string id = junction.attribute("id").as_string();
        double x = junction.attribute("x").as_double();
        double y = junction.attribute("y").as_double();

        // Create an intersection with the real position from the net file.
        auto intersection = std::make_unique<PulseIntersection>(id, PulsePosition{x, y});
        m_dataManager.addIntersection(std::move(intersection));
        count++;
        std::cout << "[PulseLoader] Loaded intersection: " << id << " at (" << x << ", " << y << ")" << std::endl;
    }
    std::cout << "[PulseLoader] Loaded " << count << " intersections." << std::endl;
}

// Parse <tlLogics> elements to load traffic lights
void PulseLoader::parseTrafficLights(const pugi::xml_document& doc) const {
    pugi::xml_node net = doc.child("net");
    pugi::xml_node tlLogics = net.child("tlLogics");
    if (!tlLogics) {
        std::cout << "[PulseLoader] No <tlLogics> element found. Skipping traffic light loading." << std::endl;
        return;
    }
    int count = 0;
    for (pugi::xml_node tlLogic : tlLogics.children("tlLogic")) {
        std::string id = tlLogic.attribute("id").as_string();
        // Create a traffic light with this id.
        auto tl = std::make_unique<PulseTrafficLight>(id);
        m_dataManager.addTrafficLight(std::move(tl));
        count++;
        std::cout << "[PulseLoader] Loaded traffic light: " << id << std::endl;
    }
    std::cout << "[PulseLoader] Loaded " << count << " traffic lights." << std::endl;
}

// Parse <edge> elements to create road connections
void PulseLoader::parseEdges(const pugi::xml_document& doc) const {
    pugi::xml_node net = doc.child("net");
    pugi::xml_node edges = net.child("edges");
    if (!edges) {
        std::cout << "[PulseLoader] No <edges> element found. Skipping road connection loading." << std::endl;
        return;
    }

    int roadCounter = 1;
    int count = 0;
    for (pugi::xml_node edge : edges.children("edge")) {
        std::string fromID = edge.attribute("from").as_string();
        std::string toID = edge.attribute("to").as_string();
        double length = edge.attribute("length").as_double();

        // Retrieve intersections from data manager.
        auto* fromInter = m_dataManager.getIntersection(fromID);
        auto* toInter = m_dataManager.getIntersection(toID);
        if (!fromInter || !toInter) {
            // Skip if one of the intersections is missing.
            continue;
        }

        // For the traffic light pointer, we assume the destination's traffic light controls the incoming road.
        auto* tl = m_dataManager.getTrafficLight(toID);
        if (!tl) {
            // Skip adding a connection if no traffic light exists for the destination.
            continue;
        }

        try {
            fromInter->addRoadConnection(roadCounter, toInter, tl, length);
            count++;
            roadCounter++;
            std::cout << "[PulseLoader] Added road connection from " << fromID << " to " << toID
                      << " with length " << length << std::endl;
        } catch (const std::exception& ex) {
            std::cerr << "[PulseLoader] Failed to add road connection: " << ex.what() << std::endl;
        }
    }
    std::cout << "[PulseLoader] Added " << count << " road connections." << std::endl;
}
