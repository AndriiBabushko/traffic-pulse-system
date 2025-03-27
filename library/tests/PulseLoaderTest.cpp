//
// Created by andrii on 3/25/25.
//

#include <gtest/gtest.h>
#include <filesystem>
#include <constants/SumoNetPath.h>

#include "core/PulseLoader.h"
#include "core/PulseDataManager.h"

TEST(PulseLoaderTest, LoaderFillsDataManager) {
    auto& manager = PulseDataManager::getInstance();
    manager.clearAll();

    std::string config_dir = std::string(CMAKE_BINARY_DIR) + "/config/sumo/";
    std::string expected_path = config_dir + SUMO_NET_PATH;
    if (!std::filesystem::exists(expected_path)) {
        GTEST_SKIP() << "Test network file does not exist: " << expected_path;
    }

    PulseLoader loader(manager, expected_path, this);
    ASSERT_NO_THROW(loader.loadNetworkData());

    auto intersections = manager.getAllIntersections();
    EXPECT_GT(intersections.size(), 0u);

    auto trafficLights = manager.getAllTrafficLights();
    EXPECT_GT(trafficLights.size(), 0u);

    // Verify that every road connection in each intersection has a valid traffic light.
    for (auto* inter : intersections) {
        const auto& connections = inter->getConnectedRoads();
        for (const auto& pair : connections) {
            EXPECT_NE(pair.second.getTrafficLight(), nullptr)
                << "Road connection " << pair.first << " from intersection "
                << inter->getId() << " does not have a valid traffic light.";
        }
    }
}

