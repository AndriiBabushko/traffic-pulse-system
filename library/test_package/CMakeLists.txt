cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

# Find libsumocpp for linking.
find_library(LIBSUMOCPP sumocpp HINTS /usr/lib /usr/local/lib)
if(NOT LIBSUMOCPP)
    message(FATAL_ERROR "libsumocpp not found! Please install SUMO with libsumo-cpp support.")
endif()

find_package(traffic_pulse_library CONFIG REQUIRED)

set(EXAMPLES_DIR "examples")

add_executable(PackageTest ${EXAMPLES_DIR}/application_example.cpp)
target_link_libraries(PackageTest PRIVATE traffic_pulse_library::traffic_pulse_library ${LIBSUMOCPP})
