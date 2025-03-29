//
// Created by andrii on 3/25/25.
//
//
#include <gtest/gtest.h>
#include <filesystem>
#include "core/PulseLoader.h"
#include "core/PulseDataManager.h"
#include "types/PulseEvent.h"
#include "interfaces/IObserver.h"

#include "constants/SumoNetPath.h"

class LoaderFixture : public ::testing::Test {
protected:
    void SetUp() override {
        auto& manager = PulseDataManager::getInstance();
        manager.clearAll();
    }
};

TEST_F(LoaderFixture, LoaderFillsDataManager) {
    auto& manager = PulseDataManager::getInstance();

    std::string config_dir = std::string(CMAKE_BINARY_DIR) + "/config/sumo/";
    std::string expected_path = config_dir + SUMO_NET_PATH;
    if (!std::filesystem::exists(expected_path)) {
        GTEST_SKIP() << "Test network file does not exist at: " << expected_path;
    }

    struct DummySubject : public ISubject {
        void attach(std::shared_ptr<IObserver>) override {}
        void detach(std::shared_ptr<IObserver>) override {}
        void notify(const PulseEvent&) override {}
    } dummy_subject;

    const PulseLoader loader(manager, expected_path, dummy_subject);

    EXPECT_NO_THROW(loader.loadNetworkData());

    const auto intersections = manager.getAllIntersections();
    EXPECT_GT(intersections.size(), 0u);

    const auto trafficLights = manager.getAllTrafficLights();
    EXPECT_GT(trafficLights.size(), 0u);

    // Verify that every road connection in each intersection has a traffic light
    for (const auto* inter : intersections) {
        for (const auto& connections = inter->getConnectedRoads(); const auto& [road_id, conn] : connections) {
            EXPECT_NE(conn.getTrafficLight(), nullptr)
                << "Road connection " << road_id << " from intersection "
                << inter->getId() << " does not have a valid traffic light.";
        }
    }
}

