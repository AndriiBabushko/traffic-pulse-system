//
// Created by andrii on 2/25/25.
//
//
//#include <gtest/gtest.h>
//#include "core/IntersectionStatistics.h"
//
//TEST(IntersectionStatisticsTest, Initialization)
//{
//    IntersectionStatistics stats(42);
//
//    EXPECT_EQ(42, stats.getIntersectionId());
//    EXPECT_EQ((size_t)0, stats.getTotalVehiclesPassed());
//    EXPECT_EQ(0.0, stats.getTotalVehicleWaitingTime());
//    EXPECT_EQ(0.0, stats.getAverageVehicleWaitingTime());
//    EXPECT_EQ((size_t)0, stats.getTotalPedestriansPassed());
//    EXPECT_EQ(0.0, stats.getTotalPedestrianWaitingTime());
//    EXPECT_EQ(0.0, stats.getAveragePedestrianWaitingTime());
//}
//
//TEST(IntersectionStatisticsTest, VehicleStats)
//{
//    IntersectionStatistics stats(1);
//
//    stats.addVehiclePass(10.0);
//    stats.addVehiclePass(6.0);
//
//    EXPECT_EQ((size_t)2, stats.getTotalVehiclesPassed());
//    EXPECT_DOUBLE_EQ(16.0, stats.getTotalVehicleWaitingTime());
//    EXPECT_DOUBLE_EQ(8.0, stats.getAverageVehicleWaitingTime());
//
//    stats.addVehiclePass(4.0);
//
//    EXPECT_EQ((size_t)3, stats.getTotalVehiclesPassed());
//    EXPECT_DOUBLE_EQ(20.0, stats.getTotalVehicleWaitingTime());
//    EXPECT_DOUBLE_EQ(20.0 / 3.0, stats.getAverageVehicleWaitingTime());
//}
//
//TEST(IntersectionStatisticsTest, PedestrianStats)
//{
//    IntersectionStatistics stats(2);
//
//    stats.addPedestrianPass(2.5);
//    stats.addPedestrianPass(3.5);
//
//    EXPECT_EQ((size_t)2, stats.getTotalPedestriansPassed());
//    EXPECT_DOUBLE_EQ(6.0, stats.getTotalPedestrianWaitingTime());
//    EXPECT_DOUBLE_EQ(3.0, stats.getAveragePedestrianWaitingTime());
//
//    // Add more data
//    stats.addPedestrianPass(1.0);
//    EXPECT_EQ((size_t)3, stats.getTotalPedestriansPassed());
//    EXPECT_DOUBLE_EQ(7.0, stats.getTotalPedestrianWaitingTime());
//    EXPECT_DOUBLE_EQ(7.0 / 3.0, stats.getAveragePedestrianWaitingTime());
//}
//
