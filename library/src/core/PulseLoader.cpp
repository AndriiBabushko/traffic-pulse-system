//
// Created by andrii on 3/20/25.
//
#include "core/PulseLoader.h"

#include <pugixml.hpp>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <utility>

#include "core/PulseDataManager.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "types/PulsePosition.h"

namespace
{
    int g_nextRoadID = 1;
}

PulseLoader::PulseLoader(PulseDataManager& data_manager, std::string netFilePath)
    : m_data_manager(data_manager),
      m_netFilePath(std::move(netFilePath))
{
}

void PulseLoader::loadNetworkData() const {
    if (!std::filesystem::exists(m_netFilePath)) {
        throw std::runtime_error("[PulseLoader] Network file not found: " + m_netFilePath);
    }

    std::cout << "[PulseLoader] LOADING_START: Parsing network file: " << m_netFilePath << std::endl;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(m_netFilePath.c_str());
    if (!result) {
        throw std::runtime_error("Could not parse network file: " + m_netFilePath +
                                   ", error: " + result.description());
    }

    pugi::xml_node netNode = doc.child("net");
    if (!netNode) {
        throw std::runtime_error("No <net> element found in network file.");
    }

    // 1) Parse <junction> elements
    bool foundAnyJunction = false;
    for (pugi::xml_node jnode : netNode.children("junction")) {
        foundAnyJunction = true;
        std::string jID = jnode.attribute("id").as_string();
        double x = jnode.attribute("x").as_double(0.0);
        double y = jnode.attribute("y").as_double(0.0);
        auto intersection = std::make_unique<PulseIntersection>(jID, PulsePosition{x, y});
        m_data_manager.addIntersection(std::move(intersection));
    }
    if (!foundAnyJunction) {
        throw std::runtime_error("No <junction> element found in network file.");
    }

    // 2) For each junction of type "traffic_light", add a traffic light to the data manager.
    for (pugi::xml_node jnode : netNode.children("junction")) {
        std::string jType = jnode.attribute("type").as_string("");
        if (jType == "traffic_light") {
            std::string tlID = jnode.attribute("id").as_string();
            auto tl = std::make_unique<PulseTrafficLight>(tlID);
            m_data_manager.addTrafficLight(std::move(tl));
        }
    }

    // 3) Parse <edge> elements to create road connections.
    for (pugi::xml_node edgeNode : netNode.children("edge")) {
        // Optionally skip edges that are internal.
        std::string func = edgeNode.attribute("function").as_string("");
        if (func == "internal") {
            continue;
        }

        std::string fromID = edgeNode.attribute("from").as_string("");
        std::string toID   = edgeNode.attribute("to").as_string("");

        PulseIntersection* fromInter = m_data_manager.getIntersection(fromID);
        PulseIntersection* toInter   = m_data_manager.getIntersection(toID);
        if (fromInter && toInter) {
            double distance = 100.0;
            if (pugi::xml_node laneNode = edgeNode.child("lane")) {
                distance = laneNode.attribute("length").as_double(100.0);
            }

            // Try to obtain a traffic light for the "from" intersection.
            PulseTrafficLight* tl = m_data_manager.getTrafficLight(fromID);
            if (!tl) {
                // Instead of throwing, create a default traffic light.
                std::cout << "[PulseLoader] Warning: No traffic light found for intersection: "
                          << fromID << ". Creating a default one." << std::endl;
                auto dummyTL = std::make_unique<PulseTrafficLight>(fromID);
                tl = dummyTL.get();
                m_data_manager.addTrafficLight(std::move(dummyTL));
            }
            int roadID = generateRoadID();
            fromInter->addRoadConnection(roadID, toInter, tl, distance);

            // If the edge is two-way, create the reverse connection.
            bool isOneWay = edgeNode.attribute("oneway").as_bool(false);
            if (!isOneWay) {
                int revRoadID = generateRoadID();
                // For the reverse direction, try to obtain a traffic light for the "to" intersection.
                PulseTrafficLight* revTL = m_data_manager.getTrafficLight(toID);
                if (!revTL) {
                    std::cout << "[PulseLoader] Warning: No traffic light found for intersection: "
                              << toID << ". Creating a default one." << std::endl;
                    auto dummyRevTL = std::make_unique<PulseTrafficLight>(toID);
                    revTL = dummyRevTL.get();
                    m_data_manager.addTrafficLight(std::move(dummyRevTL));
                }
                toInter->addRoadConnection(revRoadID, fromInter, revTL, distance);
            }
        }
    }

    std::cout << "[PulseLoader] Network file parsed successfully." << std::endl;
}

int PulseLoader::generateRoadID() {
    return g_nextRoadID++;
}
