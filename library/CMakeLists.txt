cmake_minimum_required(VERSION 3.14)

project(traffic_pulse_library VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include_directories(
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/include/core
#        ${CMAKE_CURRENT_SOURCE_DIR}/include/entities
#        ${CMAKE_CURRENT_SOURCE_DIR}/include/types
#)


#file(GLOB TEST_SOURCES "examples/*.cpp")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(${PROJECT_NAME}
        include/TrafficPulseLibrary.h
        include/CommonTypes.h
        src/TrafficPulseLibrary.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

enable_testing()

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${PROJECT_NAME}
)

if(EXISTS "${CMAKE_SOURCE_DIR}/tests")
    add_subdirectory(tests)
endif()