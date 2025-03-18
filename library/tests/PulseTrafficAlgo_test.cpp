//
// Created by andrii on 3/17/25.
//

#include <gtest/gtest.h>
#include "core/PulseDataManager.h"
#include "core/PulseTrafficAlgo.h"
#include "core/SumoIntegration.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "types/PulsePosition.h"
#include "constants/SumoConfigPath.h"
#include <iostream>
#include <unordered_map>

/**
 * @brief Mock SumoIntegration for testing purposes.
 *        In this mock, only isRunning() is used; the other methods are not used by the algorithm.
 */
class MockSumoIntegration : public SumoIntegration
{
public:
    MockSumoIntegration() : SumoIntegration(SUMO_CONFIG_PATH, true) {
        m_running = true;
    }

    void startSimulation() override { m_running = true; }
    void stopSimulation() override { m_running = false; }
    void stepSimulation() const override {}
    bool isRunning() const override { return m_running; }
    std::vector<std::string> getAllTrafficLights() const override { return {}; }
    std::vector<std::string> getAllVehicles() const override { return {}; }
    std::pair<double, double> getVehiclePosition(const std::string&) const override { return {0.0, 0.0}; }
    std::string getTrafficLightState(const std::string&) const override { return "rr"; }
    void setTrafficLightState(const std::string&, const std::string&) const override {}
protected:
    using SumoIntegration::m_running;
};

TEST(PulseTrafficAlgoTest, SingleCorridorGreenWave)
{
    // Setup data manager with 3 intersections: intA -> intB -> intC, each 100m apart.
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    // Create intersections.
    auto intA = std::make_unique<PulseIntersection>("intA", PulsePosition{0, 0});
    auto intB = std::make_unique<PulseIntersection>("intB", PulsePosition{100, 0});
    auto intC = std::make_unique<PulseIntersection>("intC", PulsePosition{200, 0});

    // Create traffic lights for road connections.
    auto tlRoadAB = std::make_unique<PulseTrafficLight>("roadAB");
    auto* rawTlAB = tlRoadAB.get();
    manager.addTrafficLight(std::move(tlRoadAB));

    auto tlRoadBC = std::make_unique<PulseTrafficLight>("roadBC");
    auto* rawTlBC = tlRoadBC.get();
    manager.addTrafficLight(std::move(tlRoadBC));

    // Connect intersections using valid traffic light pointers.
    intA->addRoadConnection(1, intB.get(), rawTlAB, 100.0);
    intB->addRoadConnection(1, intA.get(), rawTlAB, 100.0);
    intB->addRoadConnection(2, intC.get(), rawTlBC, 100.0);
    intC->addRoadConnection(2, intB.get(), rawTlBC, 100.0);

    // Add intersections to the manager.
    manager.addIntersection(std::move(intA));
    manager.addIntersection(std::move(intB));
    manager.addIntersection(std::move(intC));

    // Also add intersection-level traffic lights (to be updated by the algo).
    manager.addTrafficLight(std::make_unique<PulseTrafficLight>("intA"));
    manager.addTrafficLight(std::make_unique<PulseTrafficLight>("intB"));
    manager.addTrafficLight(std::make_unique<PulseTrafficLight>("intC"));

    // Create mock SumoIntegration.
    MockSumoIntegration mockSumo;

    // Create the traffic algorithm instance.
    PulseTrafficAlgo algo(manager, mockSumo);

    // Initialize the green wave (find corridors, calculate offsets).
    algo.initializeGreenWave();

    // Run the algorithm at simulation time 0.
    // Expect "intA" to be green (offset 0).
    algo.runOnce(0.0);
    auto tlA = manager.getTrafficLight("intA");
    ASSERT_NE(tlA, nullptr);
    EXPECT_EQ(tlA->getState(), TrafficLightState::GREEN);

    // Run the algorithm at simulation time 8.
    algo.runOnce(8.0);
    auto tlB = manager.getTrafficLight("intB");
    ASSERT_NE(tlB, nullptr);
    // Based on computed offset (~travel time from A to B), at time 8, tlB should be green.
    EXPECT_EQ(tlB->getState(), TrafficLightState::GREEN);
}
