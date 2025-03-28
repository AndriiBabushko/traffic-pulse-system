//
// Created by andrii on 2/25/25.
//

#ifndef PULSEVEHICLETYPE_H
#define PULSEVEHICLETYPE_H

#pragma once

/**
 * @brief Enum to represent the type of vehicle in the simulation.
 */
enum class PulseVehicleType {
    CAR,        ///< Car.
    BUS,        ///< Bus.
    MOTORCYCLE, ///< Motorcycle.
    TRUCK,      ///< Truck.
    TRAM,       ///< Tram.
    E_SCOOTER,  ///< Electric scooter.
    BICYCLE,    ///< Bicycle.
    PEDESTRIAN, ///< Pedestrian.
    EMERGENCY,  ///< Emergency vehicle.
};

#endif //PULSEVEHICLETYPE_H
