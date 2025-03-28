//
// Created by andrii on 2/25/25.
//

#include <stdexcept>
#include <unordered_set>

#include "core/PulseDataManager.h"

PulseDataManager& PulseDataManager::getInstance()
{
    static PulseDataManager instance;
    return instance;
}

void PulseDataManager::addIntersection(std::unique_ptr<PulseIntersection> intersection)
{
    if (!intersection) {
        throw std::invalid_argument("Cannot add a null intersection.");
    }

    const std::string& id = intersection->getId();
    if (m_intersections.contains(id)) {
        throw std::runtime_error("Intersection with this ID already exists: " + id);
    }
    m_intersections[id] = std::move(intersection);
}

PulseIntersection* PulseDataManager::getIntersection(const std::string& intersection_id) const
{
    auto it = m_intersections.find(intersection_id);
    return (it != m_intersections.end()) ? it->second.get() : nullptr;
}

void PulseDataManager::addTrafficLight(std::unique_ptr<PulseTrafficLight> traffic_light)
{
    if (!traffic_light) {
        throw std::invalid_argument("Cannot add a null traffic light.");
    }

    const std::string& id = traffic_light->getId();
    if (m_traffic_lights.contains(id)) {
        throw std::runtime_error("Traffic light with this ID already exists: " + id);
    }
    m_traffic_lights[id] = std::move(traffic_light);
}

PulseTrafficLight* PulseDataManager::getTrafficLight(const std::string& traffic_light_id) const
{
    auto it = m_traffic_lights.find(traffic_light_id);
    return (it != m_traffic_lights.end()) ? it->second.get() : nullptr;
}

void PulseDataManager::addVehicle(std::unique_ptr<PulseVehicle> vehicle)
{
    if (!vehicle) {
        throw std::invalid_argument("Cannot add a null vehicle.");
    }

    const std::string& id = vehicle->getId();
    if (m_vehicles.contains(id)) {
        throw std::runtime_error("Vehicle with this ID already exists: " + id);
    }
    m_vehicles[id] = std::move(vehicle);
}

PulseVehicle* PulseDataManager::getVehicle(const std::string& vehicle_id) const
{
    auto it = m_vehicles.find(vehicle_id);
    return (it != m_vehicles.end()) ? it->second.get() : nullptr;
}

std::vector<PulseIntersection*> PulseDataManager::getAllIntersections() const
{
    std::vector<PulseIntersection*> results;
    results.reserve(m_intersections.size());
    for (const auto& [id, intersection] : m_intersections) {
        results.push_back(intersection.get());
    }
    return results;
}

std::vector<PulseTrafficLight*> PulseDataManager::getAllTrafficLights() const
{
    std::vector<PulseTrafficLight*> results;
    results.reserve(m_traffic_lights.size());
    for (const auto& [id, light] : m_traffic_lights) {
        results.push_back(light.get());
    }
    return results;
}

std::vector<PulseVehicle*> PulseDataManager::getAllVehicles() const
{
    std::vector<PulseVehicle*> results;
    results.reserve(m_vehicles.size());
    for (const auto& [id, vehicle] : m_vehicles) {
        results.push_back(vehicle.get());
    }
    return results;
}

void PulseDataManager::clearAll()
{
    m_intersections.clear();
    m_traffic_lights.clear();
    m_vehicles.clear();
}

void PulseDataManager::syncFromSumo(const SumoIntegration &sumo)
{
    // First-time load or re-sync: clear old data
    clearAll();

    // 1) Summo uses traffic lights to represent intersections, so let's load them as well
    auto intersectionIDs = sumo.getAllTrafficLights();
    for (const auto& id : intersectionIDs) {
        auto intersection = std::make_unique<PulseIntersection>(id, PulsePosition{0.0, 0.0});
        addIntersection(std::move(intersection));
    }

    // 2) Create traffic light objects
    for (const auto& tl_id : intersectionIDs) {
        auto traffic_light = std::make_unique<PulseTrafficLight>(tl_id);
        addTrafficLight(std::move(traffic_light));
    }

    // 3) Load vehicles
    auto vehicleIDs = sumo.getAllVehicles();
    for (const auto& veh_id : vehicleIDs) {
        auto [x, y] = sumo.getVehiclePosition(veh_id);
        auto newVehicle = std::make_unique<PulseVehicle>(
            veh_id,
            PulseVehicleType::CAR,       // could refine from SUMO data if desired
            PulseVehicleRole::NORMAL,    // likewise
            PulsePosition{x, y}
        );
        addVehicle(std::move(newVehicle));
    }
}

void PulseDataManager::updateFromSumo(const SumoIntegration &sumo)
{
    // --- Vehicles ---
    auto sumoVehicleIDs = sumo.getAllVehicles();
    std::unordered_set<std::string> sumoVehSet(sumoVehicleIDs.begin(), sumoVehicleIDs.end());

    // Remove local vehicles not in SUMO
    std::vector<std::string> toRemoveVeh;
    for (const auto& [id, vehPtr] : m_vehicles) {
        if (!sumoVehSet.count(id)) {
            toRemoveVeh.push_back(id);
        }
    }
    for (const auto& id : toRemoveVeh) {
        m_vehicles.erase(id);
    }

    // Add new vehicles from SUMO
    for (const auto& veh_id : sumoVehicleIDs) {
        if (!m_vehicles.count(veh_id)) {
            auto [x, y] = sumo.getVehiclePosition(veh_id);
            auto newVeh = std::make_unique<PulseVehicle>(
                veh_id,
                PulseVehicleType::CAR,
                PulseVehicleRole::NORMAL,
                PulsePosition{x, y}
            );
            m_vehicles[veh_id] = std::move(newVeh);
        }
    }

    // Update positions of existing vehicles
    for (auto& [id, vehPtr] : m_vehicles) {
        auto [x, y] = sumo.getVehiclePosition(id);
        vehPtr->updatePosition(PulsePosition{x, y});
    }

    // --- Traffic Lights ---
    auto tlIDs = sumo.getAllTrafficLights();
    std::unordered_set<std::string> sumoTlSet(tlIDs.begin(), tlIDs.end());

    // Remove local TLs not in SUMO
    std::vector<std::string> toRemoveTL;
    for (const auto& [id, tlPtr] : m_traffic_lights) {
        if (!sumoTlSet.count(id)) {
            toRemoveTL.push_back(id);
        }
    }
    for (const auto& id : toRemoveTL) {
        m_traffic_lights.erase(id);
    }

    // Add newly discovered traffic lights
    for (const auto& tl_id : tlIDs) {
        if (!m_traffic_lights.count(tl_id)) {
            auto tl = std::make_unique<PulseTrafficLight>(tl_id);
            m_traffic_lights[tl_id] = std::move(tl);
        }
    }

    // Optionally retrieve the current state from SUMO:
    for (auto& [id, tlPtr] : m_traffic_lights) {
        auto sumoState = sumo.getTrafficLightState(id);
        // Convert sumoState to a local enum:
        if (sumoState.find('g') != std::string::npos) {
            tlPtr->setState(TrafficLightState::GREEN);
        }
        else if (sumoState.find('r') != std::string::npos) {
            tlPtr->setState(TrafficLightState::RED);
        }
        else {
            tlPtr->setState(TrafficLightState::YELLOW);
        }
    }

    // Intersections: if mostly static, skip or do the same approach. Typically they don't vanish or appear dynamically.
}
