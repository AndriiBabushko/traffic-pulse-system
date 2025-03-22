//
// Created by andrii on 3/1/25.
//

#ifndef PULSEROADCONNECTION_H
#define PULSEROADCONNECTION_H

#include "PulseTrafficLight.h"

class PulseIntersection;

/**
 * @class PulseRoadConnection
 * @brief Represents a road connecting two intersections.
 */
class PulseRoadConnection
{
public:
    /**
     * @brief Constructs a road connection between two intersections.
     * @param intersection Reference to the connected intersection.
     * @param traffic_light Reference to the traffic light controlling this road.
     * @param distance Distance in meters between intersections.
     */
    PulseRoadConnection(PulseIntersection& intersection, PulseTrafficLight* traffic_light, double distance);

    /**
     * @brief Retrieves the connected intersection.
     * @return Reference to the connected intersection.
     */
    [[nodiscard]] PulseIntersection& getConnectedIntersection() const;

    /**
     * @brief Retrieves the traffic light controlling this road.
     * @return Pointer to the traffic light.
     */
    [[nodiscard]] PulseTrafficLight* getTrafficLight() const;

    /**
     * @brief Retrieves the distance between intersections.
     * @return Distance in meters.
     */
    [[nodiscard]] double getDistance() const;

    /**
     * @brief Updates the traffic light assigned to this road connection.
     * @param traffic_light New traffic light.
     */
    void setTrafficLight(PulseTrafficLight *traffic_light);

    /**
     * @brief Updates the distance between intersections.
     * @param distance New distance value.
     */
    void setDistance(double distance);

private:
    PulseIntersection& m_connected_intersection; ///< Connected intersection.
    PulseTrafficLight* m_traffic_light; ///< Traffic light managing the road.
    double m_distance; ///< Distance in meters.
};

#endif //PULSEROADCONNECTION_H
