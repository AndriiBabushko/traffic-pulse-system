cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(traffic_pulse_library CONFIG REQUIRED)

set(EXAMPLES_DIR "examples")

add_executable(example1 ${EXAMPLES_DIR}/example1.cpp)
target_link_libraries(example1 traffic_pulse_library::traffic_pulse_library)

add_executable(example2 "${EXAMPLES_DIR}/example2.cpp")
target_link_libraries(example2 traffic_pulse_library::traffic_pulse_library)

