//
// Created by andrii on 3/1/25.
//

#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

#include "core/SumoIntegration.h"
#include "core/PulseException.h"
#include "constants/SumoConfigPath.h"

/**
 * @brief Fixture that starts a real SUMO simulation once and stops it afterward.
 *        All tests in this suite share that one instance.
 */
class SumoIntegrationFixture : public ::testing::Test {
protected:
    static SumoIntegration* s_sumo;

    /**
     * @brief Start SUMO once for all tests in this suite.
     */
    static void SetUpTestSuite() {
        try {
            s_sumo = new SumoIntegration(SUMO_CONFIG_PATH);
            s_sumo->startSimulation();
            std::cout << "SumoIntegrationFixture: SUMO started OK" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception in SetUpTestSuite: " << e.what() << std::endl;
        }
    }

    /**
     * @brief Stop SUMO after the entire suite finishes.
     */
    static void TearDownTestSuite() {
        if (s_sumo && s_sumo->isRunning()) {
            s_sumo->stopSimulation();
            std::cout << "SumoIntegrationFixture: SUMO stopped." << std::endl;
        }
        delete s_sumo;
        s_sumo = nullptr;
    }
};

SumoIntegration* SumoIntegrationFixture::s_sumo = nullptr;

/**
 * @test StartAndStopSimulation
 * Checks that SUMO is indeed running after start and not running after stop.
 */
TEST_F(SumoIntegrationFixture, StartAndStopSimulation) {
    ASSERT_NE(s_sumo, nullptr) << "SUMO pointer is null, something went wrong in SetUpTestSuite.";
    EXPECT_TRUE(s_sumo->isRunning()) << "Expected SUMO to be running after startSimulation.";

    s_sumo->stopSimulation();
    EXPECT_FALSE(s_sumo->isRunning()) << "Expected SUMO to no longer be running after stopSimulation.";

    EXPECT_NO_THROW(s_sumo->startSimulation());
    EXPECT_TRUE(s_sumo->isRunning()) << "Expected SUMO to be running again after re-starting.";
}

/**
 * @test StepSimulationAndTime
 * Steps the simulation a few times, verifying no exceptions are thrown and
 * that it doesn't exceed a certain time. Also checks we can call step multiple times.
 */
TEST_F(SumoIntegrationFixture, StepSimulationAndTime) {
    ASSERT_NE(s_sumo, nullptr);
    ASSERT_TRUE(s_sumo->isRunning()) << "SUMO is not running. Did startSimulation fail?";

    constexpr int steps = 10;
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < steps; ++i) {
        EXPECT_NO_THROW(s_sumo->stepSimulation());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Arbitrary threshold to see if stepping N times is too slow.
    EXPECT_LT(elapsed_ms, 6000) << "Stepping the simulation took too long: " << elapsed_ms << " ms";
}

/**
 * @test VehiclesEventuallyAppear
 * Some scenarios spawn vehicles after a certain sim time. We do repeat step calls
 * up to N times or T seconds, then check if we have vehicles in the scenario.
 * If your .sumocfg spawns no vehicles, you can skip or lower your expectation.
 */
TEST_F(SumoIntegrationFixture, VehiclesEventuallyAppear) {
    ASSERT_NE(s_sumo, nullptr);
    ASSERT_TRUE(s_sumo->isRunning());


    bool foundVehicle = false;
    for (int i = 0; i < 20; ++i) {
        s_sumo->stepSimulation();
        if (const auto vehicles = s_sumo->getAllVehicles(); !vehicles.empty()) {
            foundVehicle = true;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    EXPECT_TRUE(foundVehicle) << "No vehicles appeared after 20 steps, but scenario was expected to have some.";

    if (foundVehicle) {
        const auto vehicles = s_sumo->getAllVehicles();
        const auto& v_id = vehicles.front();
        EXPECT_NO_THROW({
            auto pos = s_sumo->getVehiclePosition(v_id);

            EXPECT_GE(pos.first, 0.0);
            EXPECT_GE(pos.second, 0.0);
        });
    }
}

/**
 * @test TrafficLightsCheck
 * Verifies we can retrieve traffic lights, set them, and get them back.
 * If no traffic lights exist, skip. If you know your scenario has them, you can fail instead.
 */
TEST_F(SumoIntegrationFixture, TrafficLightsCheck) {
    ASSERT_NE(s_sumo, nullptr);
    ASSERT_TRUE(s_sumo->isRunning());

    auto lights = s_sumo->getAllTrafficLights();
    if (lights.empty()) {
        GTEST_SKIP() << "No traffic lights in scenario, skipping traffic light test.";
    }

    const auto& tl_id = lights.front();
    EXPECT_NO_THROW({
        auto state = s_sumo->getTrafficLightState(tl_id);
        EXPECT_FALSE(state.empty()) << "Traffic light state is empty, unexpected.";
    });

    // Attempt to flip r->g, g->r
    {
        std::string current_state = s_sumo->getTrafficLightState(tl_id);
        std::string flipped = current_state;
        for (char &c : flipped) {
            if (c == 'r') c = 'g';
            else if (c == 'g') c = 'r';
        }

        EXPECT_NO_THROW(s_sumo->setTrafficLightState(tl_id, flipped));
        auto updated_state = s_sumo->getTrafficLightState(tl_id);
        EXPECT_EQ(updated_state, flipped);
        EXPECT_NO_THROW(s_sumo->setTrafficLightState(tl_id, current_state));
    }
}

/**
 * @test PerformanceTest
 * Steps the simulation a large number of times and ensures it doesn't blow up
 * in terms of time or memory usage.
 */
TEST_F(SumoIntegrationFixture, PerformanceTest) {
    ASSERT_NE(s_sumo, nullptr);
    ASSERT_TRUE(s_sumo->isRunning());

    constexpr int largeSteps = 100;
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < largeSteps; ++i) {
        s_sumo->stepSimulation();
    }

    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    EXPECT_LT(elapsed_ms, 8000) << "Performance test took too long for " << largeSteps
                                << " steps: " << elapsed_ms << " ms";
}
