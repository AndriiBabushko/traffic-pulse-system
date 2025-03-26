//
// Created by andrii on 2/25/25.
//

#include <gtest/gtest.h>

#include "core/PulseDataManager.h"
#include <core/PulseLoader.h>
#include "core/SumoIntegration.h"

#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

#include "constants/SumoConfigPath.h"


class MockSumoIntegration : public SumoIntegration
{
public:
    MockSumoIntegration()
        : SumoIntegration(SUMO_CONFIG_PATH)
    {}

    void startSimulation() override {}
    void stopSimulation() override {}
    void stepSimulation() const override {}

    [[nodiscard]] bool isRunning() const override { return true; }

    [[nodiscard]] std::vector<std::string> getAllTrafficLights() const override
    {
        return {"mock_tl1", "mock_tl2"};
    }

    [[nodiscard]] std::vector<std::string> getAllVehicles() const override
    {
        return {"mock_vehicle1", "mock_vehicle2"};
    }

    [[nodiscard]] std::pair<double, double> getVehiclePosition(const std::string& vehicle_id) const override
    {
        if (vehicle_id == "mock_vehicle1") return {10.0, 20.0};
        if (vehicle_id == "mock_vehicle2") return {30.0, 40.0};
        return {0.0, 0.0};
    }

    [[nodiscard]] std::string getTrafficLightState(const std::string& tl_id) const override
    {
        return "rGrG";
    }
};

TEST(PulseDataManagerTest, BasicIntersectionStorage)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    // Add an intersection
    auto intersection = std::make_unique<PulseIntersection>("int1", PulsePosition{1.0, 2.0});
    manager.addIntersection(std::move(intersection));

    auto retrieved = manager.getIntersection("int1");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), "int1");

    auto allInts = manager.getAllIntersections();
    EXPECT_EQ(allInts.size(), 1u);
}

TEST(PulseDataManagerTest, BasicTrafficLightStorage)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    auto tl = std::make_unique<PulseTrafficLight>("light1");
    manager.addTrafficLight(std::move(tl));

    auto retrieved = manager.getTrafficLight("light1");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), "light1");

    auto allTls = manager.getAllTrafficLights();
    EXPECT_EQ(allTls.size(), 1u);
}

TEST(PulseDataManagerTest, BasicVehicleStorage)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    auto vehicle = std::make_unique<PulseVehicle>("V123", PulseVehicleType::CAR, PulseVehicleRole::NORMAL, PulsePosition{5.0, 5.0});
    manager.addVehicle(std::move(vehicle));

    auto retrieved = manager.getVehicle("V123");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), "V123");

    auto allVeh = manager.getAllVehicles();
    EXPECT_EQ(allVeh.size(), 1u);
}

TEST(PulseDataManagerTest, SyncFromMockSumo)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    MockSumoIntegration mockSumo;
    manager.syncFromSumo(mockSumo);

    // Check intersections
    auto ints = manager.getAllIntersections();
    EXPECT_EQ(ints.size(), 2u);

    // Check traffic lights
    auto tl1 = manager.getTrafficLight("mock_tl1");
    ASSERT_NE(tl1, nullptr);
    auto tl2 = manager.getTrafficLight("mock_tl2");
    ASSERT_NE(tl2, nullptr);

    // Check vehicles
    auto v1 = manager.getVehicle("mock_vehicle1");
    ASSERT_NE(v1, nullptr);
    EXPECT_EQ(v1->getPosition().x, 10.0);
    EXPECT_EQ(v1->getPosition().y, 20.0);

    auto v2 = manager.getVehicle("mock_vehicle2");
    ASSERT_NE(v2, nullptr);
    EXPECT_EQ(v2->getPosition().x, 30.0);
    EXPECT_EQ(v2->getPosition().y, 40.0);

    // Also check getAllVehicles() & getAllTrafficLights()
    auto allVehs = manager.getAllVehicles();
    EXPECT_EQ(allVehs.size(), 2u);
    auto allTLights = manager.getAllTrafficLights();
    EXPECT_EQ(allTLights.size(), 2u);
}

TEST(PulseDataManagerTest, UpdateFromMockSumo)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    MockSumoIntegration mockSumo;
    manager.syncFromSumo(mockSumo);

    // Modify scenario so only 1 vehicle remains
    class Step2MockSumo : public MockSumoIntegration {
    public:
        std::vector<std::string> getAllVehicles() const override {
            return {"mock_vehicle1"}; // dropped "mock_vehicle2"
        }
        // Suppose we drop "mock_tl2" as well
        std::vector<std::string> getAllTrafficLights() const override {
            return {"mock_tl1"}; // only 1 remains
        }
    } step2Sumo;

    manager.updateFromSumo(step2Sumo);

    // Vehicle2 should be removed
    auto v2 = manager.getVehicle("mock_vehicle2");
    EXPECT_EQ(v2, nullptr);

    // Vehicle1 still present
    auto v1 = manager.getVehicle("mock_vehicle1");
    ASSERT_NE(v1, nullptr);

    // Traffic light2 removed
    auto tl2 = manager.getTrafficLight("mock_tl2");
    EXPECT_EQ(tl2, nullptr);

    // Traffic light1 still present
    auto tl1 = manager.getTrafficLight("mock_tl1");
    ASSERT_NE(tl1, nullptr);
}