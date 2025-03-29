//
// Created by andrii on 2/25/25.
//

#include <gtest/gtest.h>
#include <thread>
#include <chrono>

#include "core/PulseDataManager.h"
#include "core/SumoIntegration.h"
#include "core/PulseException.h"

#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

#include "constants/SumoConfigPath.h"

/**
 * @class PulseDataManagerWithRealSumoTest
 * @brief Single fixture that:
 *        1) sets up a real SUMO instance once for all tests,
 *        2) clears the PulseDataManager before each test.
 */
class PulseDataManagerWithRealSumoTest : public ::testing::Test {
protected:
    // The static pointer to the SUMO instance, accessible by all tests in this fixture
    static SumoIntegration* s_sumo;

    /**
     * @brief Start SUMO once for all tests in this suite
     */
    static void SetUpTestSuite() {
        s_sumo = new SumoIntegration(SUMO_CONFIG_PATH);
        s_sumo->startSimulation();
    }

    /**
     * @brief Stop SUMO after the entire test suite finishes
     */
    static void TearDownTestSuite() {
        if (s_sumo && s_sumo->isRunning()) {
            s_sumo->stopSimulation();
        }
        delete s_sumo;
        s_sumo = nullptr;
    }

    /**
     * @brief Clear manager data before each test
     */
    void SetUp() override {
        auto& manager = PulseDataManager::getInstance();
        manager.clearAll();
    }
};

SumoIntegration* PulseDataManagerWithRealSumoTest::s_sumo = nullptr;

TEST_F(PulseDataManagerWithRealSumoTest, AddIntersectionNoDup) {
    auto& manager = PulseDataManager::getInstance();

    // 1) Add intersections
    auto interA = std::make_unique<PulseIntersection>("intA", PulsePosition{1.0, 2.0});
    manager.addIntersection(std::move(interA));

    auto interB = std::make_unique<PulseIntersection>("intB", PulsePosition{3.0, 4.0});
    manager.addIntersection(std::move(interB));

    // 2) Check
    EXPECT_EQ(manager.getAllIntersections().size(), 2u);

    // 3) Attempt a duplicate => should throw
    auto dup = std::make_unique<PulseIntersection>("intA", PulsePosition{9.0, 9.0});
    EXPECT_THROW(manager.addIntersection(std::move(dup)), PulseException);
}

TEST_F(PulseDataManagerWithRealSumoTest, AddTrafficLightNoDup) {
    auto& manager = PulseDataManager::getInstance();

    auto tlA = std::make_unique<PulseTrafficLight>("TL_A");
    manager.addTrafficLight(std::move(tlA));

    auto tlB = std::make_unique<PulseTrafficLight>("TL_B");
    manager.addTrafficLight(std::move(tlB));

    EXPECT_EQ(manager.getAllTrafficLights().size(), 2u);

    auto dup = std::make_unique<PulseTrafficLight>("TL_A");
    EXPECT_THROW(manager.addTrafficLight(std::move(dup)), PulseException);
}

TEST_F(PulseDataManagerWithRealSumoTest, AddVehicleNoDup) {
    auto& manager = PulseDataManager::getInstance();

    auto v1 = std::make_unique<PulseVehicle>("veh1", PulseVehicleType::CAR, PulseVehicleRole::NORMAL, PulsePosition{5.0, 5.0});
    manager.addVehicle(std::move(v1));

    auto v2 = std::make_unique<PulseVehicle>("veh2", PulseVehicleType::TRUCK, PulseVehicleRole::NORMAL, PulsePosition{10.0, 20.0});
    manager.addVehicle(std::move(v2));

    EXPECT_EQ(manager.getAllVehicles().size(), 2u);

    auto dup = std::make_unique<PulseVehicle>("veh1", PulseVehicleType::CAR, PulseVehicleRole::NORMAL, PulsePosition{0, 0});
    EXPECT_THROW(manager.addVehicle(std::move(dup)), PulseException);
}

TEST_F(PulseDataManagerWithRealSumoTest, NullPointerThrowsInvalidArgument) {
    auto& manager = PulseDataManager::getInstance();

    EXPECT_THROW(manager.addIntersection(nullptr), std::invalid_argument);
    EXPECT_THROW(manager.addTrafficLight(nullptr), std::invalid_argument);
    EXPECT_THROW(manager.addVehicle(nullptr), std::invalid_argument);
}

TEST_F(PulseDataManagerWithRealSumoTest, SyncFromRealSumo) {
    auto& manager = PulseDataManager::getInstance();
    ASSERT_TRUE(s_sumo->isRunning()) << "SUMO should be running for this test.";

    for (int i = 0; i < 20; ++i) {
        s_sumo->stepSimulation();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    manager.syncFromSumo(*s_sumo);

    const auto intersections = manager.getAllIntersections();
    const auto trafficLights = manager.getAllTrafficLights();
    const auto vehicles = manager.getAllVehicles();

    EXPECT_GT(intersections.size(), 0u);
    EXPECT_GT(trafficLights.size(), 0u);
    EXPECT_GE(vehicles.size(), 1u);
}

TEST_F(PulseDataManagerWithRealSumoTest, UpdateFromRealSumoPositions) {
    auto& manager = PulseDataManager::getInstance();
    ASSERT_TRUE(s_sumo->isRunning());

    manager.syncFromSumo(*s_sumo);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Step sim so vehicles might move
    s_sumo->stepSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    s_sumo->stepSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    manager.updateFromSumo(*s_sumo);

    for (auto vehicles = manager.getAllVehicles(); auto* veh : vehicles) {
        EXPECT_GE(veh->getPosition().x, 0.0);
        EXPECT_GE(veh->getPosition().y, 0.0);
    }
}


TEST_F(PulseDataManagerWithRealSumoTest, PerformanceSyncUpdate) {
    auto& manager = PulseDataManager::getInstance();
    ASSERT_TRUE(s_sumo->isRunning());

    constexpr int iterations = 5;
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < iterations; ++i) {
        manager.syncFromSumo(*s_sumo);
        s_sumo->stepSimulation();
        manager.updateFromSumo(*s_sumo);
    }

    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    EXPECT_LT(elapsed_ms, 3000) << "Performance test took too long: " << elapsed_ms << " ms";
}