//
// Created by andrii on 3/27/25.
//

#pragma once

#ifndef GREENWAVECORIDOR_H
#define GREENWAVECORIDOR_H

#include <vector>
#include <string>

/**
 * @struct GreenWaveCorridor
 * @brief Represents a path (sequence) of intersections for the green wave.
 */
struct GreenWaveCorridor {
    std::vector<std::string> intersection_ids; ///< Ordered intersections along this path
    double target_speed_m_s;                   ///< The speed to maintain the wave
};

#endif //GREENWAVECORIDOR_H
