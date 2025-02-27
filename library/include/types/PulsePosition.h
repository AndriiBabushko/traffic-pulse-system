//
// Created by andrii on 2/11/25.
//

#ifndef PULSEPOSITION_H
#define PULSEPOSITION_H

/**
 * @brief Struct to hold the position of an object in 2D space.
 */

struct PulsePosition {
    double x; ///< X-coordinate of the object.
    double y; ///< Y-coordinate of the object.

    /**
     * @brief Constructor for a position.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     */
    PulsePosition(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    /**
     * @brief Equality operator for comparing positions.
     */
    bool operator==(const PulsePosition& other) const
    {
        return x == other.x && y == other.y;
    }
};

#endif //PULSEPOSITION_H
