//
// Created by andrii on 2/11/25.
//

#ifndef PULSEVEHICLE_H
#define PULSEVEHICLE_H

#include <string>

class PulseVehicle
{
private:
    std::string id;
    double speed;
public:
    explicit PulseVehicle(const std::string& vehicle_id);

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] double getSpeed() const;

    [[nodiscard]] std::pair<double, double> getPosition() const;

    void update();
};

#endif //PULSEVEHICLE_H
