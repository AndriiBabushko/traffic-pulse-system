#include "TrafficPulseLibrary.h"
#include <iostream>

int main() {
    IntersectionStatistics stats(5);
    stats.addVehiclePass(8.5);
    stats.addVehiclePass(6.2);

    std::cout << "Intersection ID: " << stats.getIntersectionId() << std::endl;
    std::cout << "Vehicles passed: " << stats.getTotalVehiclesPassed() << std::endl;
    std::cout << "Average vehicle wait: " << stats.getAverageVehicleWaitingTime() << std::endl;

    return 0;
}
