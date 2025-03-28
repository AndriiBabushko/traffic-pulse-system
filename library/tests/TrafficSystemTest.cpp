//
// Created by andrii on 3/25/25.
//

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <any>

#include "core/TrafficSystem.h"
#include "core/PulseDataManager.h"
#include "types/PulseEvent.h"
#include "types/PulseEvents.h"
#include "interfaces/IObserver.h"

class TestObserver : public IObserver {
public:
    void update(const PulseEvent& event) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        events.push_back(event);
    }
    std::vector<PulseEvent> events;
private:
    std::mutex m_mutex;
};

TEST(TrafficSystem, CheckLoadingAndSimulationEvents) {
    TrafficSystem traffic_system(5.0);
    auto observer = std::make_shared<TestObserver>();
    traffic_system.attach(observer);

    // Run simulation in a separate thread
    std::thread sim_thread([&traffic_system]() {
        traffic_system.run();
    });

    // Let it run for 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Request stop
    traffic_system.requestStop();
    sim_thread.join();

    // Check data manager for intersections
    auto& manager = traffic_system.getDataManager();
    auto intersections = manager.getAllIntersections();
    EXPECT_GT(intersections.size(), 0u);

    // Look for events
    bool found_start = false;
    bool found_end = false;
    bool found_step = false;

    bool found_loading_start = false;
    bool found_loading_progress = false;
    bool found_loading_complete = false;

    for (const auto& ev : observer->events) {
        switch (ev.type) {
        case PulseEvents::SIMULATION_START:
            found_start = true;
            break;
        case PulseEvents::SIMULATION_STEP:
            found_step = true;
            break;
        case PulseEvents::SIMULATION_END:
            found_end = true;
            break;
        case PulseEvents::LOADING_START:
            found_loading_start = true;
            break;
        case PulseEvents::LOADING_PROGRESS:
            found_loading_progress = true;
            if (ev.data.has_value()) {
                if (ev.data.type() == typeid(float)) {
                    const auto progress = std::any_cast<float>(ev.data);
                    EXPECT_GE(progress, 0.0f);
                    EXPECT_LE(progress, 1.0f);
                }
            }
            break;
        case PulseEvents::LOADING_COMPLETE:
            found_loading_complete = true;
            break;
        default:
            // no-op
            break;
        }
    }

    EXPECT_TRUE(found_start);
    EXPECT_TRUE(found_step);
    EXPECT_TRUE(found_end);

    EXPECT_TRUE(found_loading_start);
    EXPECT_TRUE(found_loading_progress);
    EXPECT_TRUE(found_loading_complete);
}
