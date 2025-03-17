//
// Created by andrii on 1/30/25.
//

#ifndef PULSE_INTERSECTION_H
#define PULSE_INTERSECTION_H

#pragma once

#include <string>
#include <unordered_map>

#include "core/IntersectionStatistics.h"

#include "entities/PulseEntity.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseRoadConnection.h"

#include "types/PulsePosition.h"

/**
 * @class PulseIntersection
 * @brief Represents a traffic intersection in a graph-based model.
 */
class PulseIntersection : public PulseEntity
{
public:
    /**
     * @brief Constructs an intersection with a given ID and position.
     * @param intersection_id Unique identifier for this intersection.
     * @param position The (x, y) coordinates of this intersection.
     */
    PulseIntersection(const std::string &intersection_id, const PulsePosition &position);

    /**
     * @brief Retrieves the intersection ID as int.
     * @return The unique identifier of the intersection as a string.
     */
    [[nodiscard]] std::string getId() const override;

    /**
     * @brief Retrieves the position of the intersection.
     * @return The (x, y) coordinates of the intersection.
     */
    PulsePosition getPosition() const;

    /**
     * @brief Adds a road connection between this intersection and another.
     * @param road_id Unique identifier for the road connection.
     * @param intersection The intersection at the other end of the road.
     * @param traffic_light The traffic light controlling the road.
     * @param distance The distance in meters between the intersections.
     */
    void addRoadConnection(int road_id, PulseIntersection* intersection, PulseTrafficLight* traffic_light, double distance);

    /**
     * @brief Retrieves all road connections from this intersection.
     * @return A map of road ID to RoadConnection.
     */
    const std::unordered_map<int, PulseRoadConnection>& getConnectedRoads() const;

    /**
     * @brief Retrieves statistics for this intersection.
     * @return A reference to the IntersectionStatistics object.
     */
    IntersectionStatistics& getStatistics();

private:
    std::string m_intersection_id; ///< Unique identifier for the intersection.
    PulsePosition m_position; ///< The (x, y) coordinates of the intersection.
    std::unordered_map<int, PulseRoadConnection> m_connected_roads; ///< Graph-based road connections.

    IntersectionStatistics m_statistics; ///< Stores traffic data for this intersection.
};


#endif // PULSE_INTERSECTION_H
