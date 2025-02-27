//
// Created by andrii on 1/30/25.
//

#ifndef PULSE_INTERSECTION_H
#define PULSE_INTERSECTION_H

#include <vector>
#include <string>
#include <memory>

#include "core/IntersectionStatistics.h"

#include "entities/PulseEntity.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

#include "types/PulsePosition.h"

/**
 * @class PulseIntersection
 * @brief Represents a traffic intersection, managing traffic lights, vehicles, and statistics.
 */
class PulseIntersection : public PulseEntity
{
public:
    /**
     * @brief Constructs an intersection with a given ID and position.
     * @param intersection_id Unique identifier for this intersection.
     * @param position The (x, y) coordinates of this intersection.
     */
    PulseIntersection(int intersection_id, const PulsePosition& position);

    /**
     * @brief Retrieves the intersection ID.
     * @return The unique identifier of the intersection.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Retrieves the position of the intersection.
     * @return The (x, y) coordinates of the intersection.
     */
    [[nodiscard]] PulsePosition getPosition() const;

    /**
     * @brief Adds a traffic light to this intersection.
     * @param traffic_light A unique pointer to a PulseTrafficLight object.
     */
    void addTrafficLight(std::unique_ptr<PulseTrafficLight> traffic_light);

    /**
     * @brief Retrieves a list of all traffic lights at this intersection.
     * @return A vector of raw pointers to PulseTrafficLight objects.
     */
    [[nodiscard]] std::vector<PulseTrafficLight*> getTrafficLights() const;

    /**
     * @brief Registers a vehicle as entering the intersection.
     * @param vehicle A unique pointer to a PulseVehicle object.
     */
    void addVehicle(std::unique_ptr<PulseVehicle> vehicle);

    /**
     * @brief Removes a vehicle from the intersection (after it leaves).
     * @param vehicle_id The unique identifier of the vehicle.
     */
    void removeVehicle(const std::string& vehicle_id);

    /**
     * @brief Retrieves a list of all vehicles currently in the intersection.
     * @return A vector of raw pointers to PulseVehicle objects.
     */
    [[nodiscard]] std::vector<PulseVehicle*> getVehicles() const;

    /**
     * @brief Retrieves statistics for this intersection.
     * @return A reference to the IntersectionStatistics object.
     */
    IntersectionStatistics& getStatistics();

private:
    int m_intersection_id; ///< Unique identifier for the intersection.
    PulsePosition m_position; ///< The (x, y) coordinates of the intersection.

    std::vector<std::unique_ptr<PulseTrafficLight>> m_traffic_lights; ///< Traffic lights at this intersection.
    std::vector<std::unique_ptr<PulseVehicle>> m_vehicles; ///< Vehicles currently in the intersection.

    IntersectionStatistics m_statistics; ///< Stores traffic data for this intersection.
};


#endif // PULSE_INTERSECTION_H
