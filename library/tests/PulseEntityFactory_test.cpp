//
// Created by andrii on 2/25/25.
//

#include <gtest/gtest.h>
#include "entities/PulseEntityFactory.h"
#include "entities/PulseIntersection.h"
#include "entities/PulseTrafficLight.h"
#include "entities/PulseVehicle.h"

TEST(PulseEntityFactoryTest, CreateIntersection)
{
    auto intersection = PulseEntityFactory::createEntity(PulseEntityType::INTERSECTION, "1", PulsePosition(10.5, 20.5));

    ASSERT_NE(intersection, nullptr);  // Ensure it's not null
    auto* casted_intersection = dynamic_cast<PulseIntersection*>(intersection.get());
    ASSERT_NE(casted_intersection, nullptr);  // Ensure correct type

    EXPECT_EQ(casted_intersection->getId(), 1);
    EXPECT_EQ(casted_intersection->getPosition().x, 10.5);
    EXPECT_EQ(casted_intersection->getPosition().y, 20.5);
}

TEST(PulseEntityFactoryTest, CreateTrafficLight)
{
    auto traffic_light = PulseEntityFactory::createEntity(PulseEntityType::TRAFFIC_LIGHT, "101");

    ASSERT_NE(traffic_light, nullptr);
    auto* casted_light = dynamic_cast<PulseTrafficLight*>(traffic_light.get());
    ASSERT_NE(casted_light, nullptr);

    EXPECT_EQ(casted_light->getId(), 101);
}

TEST(PulseEntityFactoryTest, CreateVehicle)
{
    auto vehicle = PulseEntityFactory::createEntity(PulseEntityType::VEHICLE, "V123", {}, PulseVehicleType::CAR, PulseVehicleRole::NORMAL);

    ASSERT_NE(vehicle, nullptr);
    auto* casted_vehicle = dynamic_cast<PulseVehicle*>(vehicle.get());
    ASSERT_NE(casted_vehicle, nullptr);

    EXPECT_EQ(casted_vehicle->getId(), "V123");
    EXPECT_EQ(casted_vehicle->getType(), PulseVehicleType::CAR);
    EXPECT_EQ(casted_vehicle->getRole(), PulseVehicleRole::NORMAL);
}

TEST(PulseEntityFactoryTest, InvalidEntityType)
{
    auto invalid_entity = PulseEntityFactory::createEntity(static_cast<PulseEntityType>(999), "X");

    EXPECT_EQ(invalid_entity, nullptr);
}
