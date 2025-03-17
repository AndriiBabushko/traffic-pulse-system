cmake_minimum_required(VERSION 3.14)
project(traffic_simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SUMO_CONFIG_PATH "${CMAKE_CURRENT_SOURCE_DIR}/library/sumo/zhytomyr/2025-01-28-19-55-28/osm.sumocfg")

add_compile_definitions(SUMO_CONFIG_PATH="${SUMO_CONFIG_PATH}")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(library)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE traffic_pulse_library)

enable_testing()

if(EXISTS "${CMAKE_SOURCE_DIR}/tests")
    add_subdirectory(tests)
endif()
