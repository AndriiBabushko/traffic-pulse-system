//
// Created by andrii on 2/25/25.
//

#include <gtest/gtest.h>
#include "core/PulseDataManager.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

TEST(PulseDataManagerTest, IntersectionStorage)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    auto intersection = std::make_unique<PulseIntersection>(1);
    manager.addIntersection(std::move(intersection));

    auto retrieved = manager.getIntersection(1);
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), 1);
}

TEST(PulseDataManagerTest, TrafficLightStorage)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    auto light = std::make_unique<PulseTrafficLight>(101);
    manager.addTrafficLight(std::move(light));

    auto retrieved = manager.getTrafficLight(101);
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), 101);
}

TEST(PulseDataManagerTest, VehicleStorage)
{
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    auto vehicle = std::make_unique<PulseVehicle>("V123");
    manager.addVehicle(std::move(vehicle));

    auto retrieved = manager.getVehicle("V123");
    EXPECT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->getId(), "V123");
}
