//
// Created by andrii on 2/11/25.
//

#ifndef TRAFFICLIGHTSTATE_H
#define TRAFFICLIGHTSTATE_H

/**
 * @brief Enum representing the state of the traffic light.
 */
enum class TrafficLightState {
    RED,        ///< Traffic light is red.
    YELLOW,     ///< Traffic light is yellow.
    GREEN,      ///< Traffic light is green.
    UNKNOWN     ///< Traffic light is in an unknown state, flashing yellow to indicate malfunction.
};

#endif //TRAFFICLIGHTSTATE_H
