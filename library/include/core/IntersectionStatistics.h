//
// Created by andrii on 2/25/25.
//

#ifndef INTERSECTIONSTATISTICS_H
#define INTERSECTIONSTATISTICS_H

#include <cstddef>
#include <string>

/**
 * @class IntersectionStatistics
 * @brief Stores and manages statistical data specific to a single intersection.
 *
 * This class follows the Single Responsibility Principle by focusing solely on
 * collecting and providing intersection-level metrics, such as total vehicles passed,
 * average waiting time, and so forth.
 */
class IntersectionStatistics
{
public:
    /**
     * @brief Constructs an IntersectionStatistics object for a particular intersection.
     * @param intersection_id A unique string identifier for the intersection.
     */
    explicit IntersectionStatistics(std::string intersection_id);

    /**
     * @brief Returns the ID of the intersection associated with these statistics.
     * @return The intersection's unique ID.
     */
    [[nodiscard]] std::string getIntersectionId() const;

    /**
     * @brief Records that a vehicle has passed this intersection.
     * @param waiting_time The time (in seconds) that the vehicle waited before passing.
     */
    void addVehiclePass(double waiting_time /*, PulseVehicleType vehicle_type*/);

    /**
     * @brief Retrieves the total number of vehicles that have passed through the intersection.
     * @return The total count of vehicles.
     */
    [[nodiscard]] std::size_t getTotalVehiclesPassed() const;

    /**
     * @brief Retrieves the sum of all waiting times for vehicles that have passed.
     * @return The total waiting time accumulated (in seconds).
     */
    [[nodiscard]] double getTotalVehicleWaitingTime() const;

    /**
     * @brief Computes the average waiting time for vehicles that have passed.
     * @return The average waiting time in seconds. Returns 0.0 if no vehicles have passed.
     */
    [[nodiscard]] double getAverageVehicleWaitingTime() const;

    /**
     * @brief Records that a pedestrian has passed this intersection.
     * @param waiting_time The time (in seconds) that the pedestrian waited before passing.
     */
    void addPedestrianPass(double waiting_time);

    /**
     * @brief Retrieves the total number of pedestrians that have passed through the intersection.
     * @return The total count of pedestrians.
     */
    [[nodiscard]] std::size_t getTotalPedestriansPassed() const;

    /**
     * @brief Retrieves the sum of all waiting times for pedestrians that have passed.
     * @return The total waiting time (in seconds) for all pedestrians.
     */
    [[nodiscard]] double getTotalPedestrianWaitingTime() const;

    /**
     * @brief Computes the average waiting time for pedestrians that have passed.
     * @return The average waiting time in seconds. Returns 0.0 if no pedestrians have passed.
     */
    [[nodiscard]] double getAveragePedestrianWaitingTime() const;

private:
    std::string m_intersection_id;          ///< Unique string identifier for the intersection.

    std::size_t m_total_vehicles_passed;    ///< Count of vehicles that passed.
    double      m_total_vehicle_waiting;    ///< Sum of their waiting times.

    std::size_t m_total_pedestrians_passed; ///< Count of pedestrians that passed.
    double      m_total_pedestrian_waiting; ///< Sum of their waiting times.

    // In the future, we could store additional maps or counters keyed by vehicle type/role if desired.
};

#endif //INTERSECTIONSTATISTICS_H
