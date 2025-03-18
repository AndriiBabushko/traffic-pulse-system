#include "core/TrafficSystem.h"
//#include "TrafficPulseSystem.h"
#include "core/Logger.h"
#include "interfaces/IObserver.h"
#include <iostream>
#include <memory>

int main() {
    try {
        // Rename variable to avoid conflict with the system() function.
        TrafficSystem trafficSystem(5.0);

        // Attach the Logger singleton as an observer.
        // We wrap the Logger::getInstance() in a shared_ptr with a no-op deleter.
        auto logger = std::shared_ptr<IObserver>(&Logger::getInstance(), [](IObserver*) {});
        trafficSystem.attach(logger);

        // Run the simulation loop.
        trafficSystem.run();

        // After simulation, display the number of intersections.
        std::cout << "Simulation complete. Number of intersections: "
                  << trafficSystem.getDataManager().getAllIntersections().size() << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << "Error in TrafficSystem: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

