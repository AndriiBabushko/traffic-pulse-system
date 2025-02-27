//
// Created by andrii on 2/11/25.
//

#ifndef TRAFFICLIGHTDURATIONS_H
#define TRAFFICLIGHTDURATIONS_H

#pragma once

/**
 * @brief Struct to hold durations for different traffic light states.
 */
struct TrafficLightDurations {
    double red;       ///< Duration of red light.
    double yellow;    ///< Duration of yellow light.
    double green;     ///< Duration of green light.
    double walk;      ///< Duration of walk signal for pedestrians.
    double dont_walk; ///< Duration of don't walk signal for pedestrians.

    /**
     * @brief Default constructor with default timings (in seconds).
     */
    TrafficLightDurations(
        double red = 30.0,
        double yellow = 5.0,
        double green = 30.0,
        double walk = 15.0,
        double dont_walk = 5.0)
        : red(red), yellow(yellow), green(green), walk(walk), dont_walk(dont_walk) {}
};


#endif //TRAFFICLIGHTDURATIONS_H
