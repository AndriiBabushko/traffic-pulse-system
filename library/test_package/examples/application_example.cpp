#include "TrafficPulseLibrary.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

int main() {
    try {
        TrafficSystem trafficSystem(5.0);

        auto logger = std::shared_ptr<IObserver>(&Logger::getInstance(), [](IObserver*) {});
        trafficSystem.attach(logger);

        // Run the simulation in a separate thread.
        std::thread simThread([&trafficSystem]() {
            trafficSystem.run();
        });

        std::this_thread::sleep_for(std::chrono::seconds(20));
        trafficSystem.requestStop();

        simThread.join();

        std::cout << "Simulation complete. Number of intersections: "
                  << trafficSystem.getDataManager().getAllIntersections().size() << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << "Error in TrafficSystem: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

