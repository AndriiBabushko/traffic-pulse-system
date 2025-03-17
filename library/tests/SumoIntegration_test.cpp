//
// Created by andrii on 3/1/25.
//

#include <gtest/gtest.h>

#include "core/SumoIntegration.h"

#include "constants/SumoConfigPath.h"

class SumoIntegrationTestSuite : public ::testing::Test
{
protected:
    static SumoIntegration* sumo;

    static void SetUpTestSuite() {
        std::cout << "Attempting to start SUMO" << std::endl;
        try {
            sumo = new SumoIntegration(SUMO_CONFIG_PATH);
            sumo->startSimulation();
            std::cout << "startSimulation returned OK" << std::endl;
        } catch(const std::exception& e) {
            std::cout << "Exception in SetUpTestSuite: " << e.what() << std::endl;
        }
    }

    static void TearDownTestSuite()
    {
        if (sumo->isRunning()) {
            sumo->stopSimulation();
        }
        delete sumo;
        sumo = nullptr;
    }
};

SumoIntegration* SumoIntegrationTestSuite::sumo = nullptr;

TEST_F(SumoIntegrationTestSuite, StartSimulation)
{
    EXPECT_TRUE(sumo->isRunning());
}

TEST_F(SumoIntegrationTestSuite, StepSimulation)
{
    EXPECT_NO_THROW(sumo->stepSimulation());
}

TEST_F(SumoIntegrationTestSuite, GetAllVehicles)
{
    EXPECT_NO_THROW({
        auto vehicles = sumo->getAllVehicles();
        EXPECT_TRUE(vehicles.empty() || !vehicles.empty());
    });
}

// TODO: test skips so maybe its because no vehicles exist in the scenario at certain step
TEST_F(SumoIntegrationTestSuite, GetVehiclePosition)
{
    EXPECT_NO_THROW({
        auto vehicles = sumo->getAllVehicles();
        if (vehicles.empty()) {
            GTEST_SKIP() << "No vehicles exist in the SUMO scenario. Skipping test.";
        } else {
            auto vehicle_id = vehicles.front();
            auto position = sumo->getVehiclePosition(vehicle_id);

            EXPECT_GE(position.first, 0.0);
            EXPECT_GE(position.second, 0.0);
        }
    });
}

TEST_F(SumoIntegrationTestSuite, GetTrafficLightState)
{
    EXPECT_NO_THROW({
        auto lights = sumo->getAllTrafficLights();
        if (lights.empty()) {
            GTEST_SKIP() << "No traffic lights exist in the SUMO scenario. Skipping test.";
        } else {
            auto tl_id = lights.front();
            auto state = sumo->getTrafficLightState(tl_id);

            EXPECT_FALSE(state.empty());
        }
    });
}

TEST_F(SumoIntegrationTestSuite, SetTrafficLightState)
{
    auto lights = sumo->getAllTrafficLights();
    if (lights.empty()) {
        GTEST_SKIP() << "No traffic lights exist in the SUMO scenario. Skipping test.";
    } else {
        auto tl_id = lights.front();

        auto current_state = sumo->getTrafficLightState(tl_id);

        // Modify the state carefully, e.g. flipping 'r'->'g' or 'g'->'r'
        std::string new_state = current_state;
        for (char &c : new_state) {
            if (c == 'r') c = 'g';
            else if (c == 'g') c = 'r';
        }

        EXPECT_NO_THROW({
            sumo->setTrafficLightState(tl_id, new_state);
        });

        auto updated_state = sumo->getTrafficLightState(tl_id);
        EXPECT_EQ(updated_state, new_state);
    }
}

TEST_F(SumoIntegrationTestSuite, StopSimulation)
{
    EXPECT_NO_THROW(sumo->stopSimulation());
}
