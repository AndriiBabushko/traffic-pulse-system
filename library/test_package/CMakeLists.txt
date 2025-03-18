cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

# Determine the library root (one level up from test_package)
get_filename_component(LIBRARY_ROOT "${CMAKE_SOURCE_DIR}/.." ABSOLUTE)
message(STATUS "Library root: ${LIBRARY_ROOT}")

# Define source and destination for the config/sumo directory
set(CONFIG_SRC "${LIBRARY_ROOT}/config/sumo")
set(CONFIG_DST "${CMAKE_BINARY_DIR}/config/sumo")

if(EXISTS "${CONFIG_SRC}")
    message(STATUS "Copying config from ${CONFIG_SRC} to ${CONFIG_DST}")
    file(MAKE_DIRECTORY "${CONFIG_DST}")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${CONFIG_SRC}" "${CONFIG_DST}"
            RESULT_VARIABLE copy_result
    )
    if(NOT copy_result EQUAL 0)
        message(FATAL_ERROR "Error copying directory from ${CONFIG_SRC} to ${CONFIG_DST}")
    endif()
else()
    message(FATAL_ERROR "Library config/sumo directory not found at: ${CONFIG_SRC}")
endif()

# Find libsumocpp for linking.
find_library(LIBSUMOCPP sumocpp HINTS /usr/lib /usr/local/lib)
if(NOT LIBSUMOCPP)
    message(FATAL_ERROR "libsumocpp not found! Please install SUMO with libsumo-cpp support.")
endif()

find_package(traffic_pulse_library CONFIG REQUIRED)

set(EXAMPLES_DIR "examples")

add_executable(PackageTest ${EXAMPLES_DIR}/application_example.cpp)
target_link_libraries(PackageTest PRIVATE traffic_pulse_library::traffic_pulse_library ${LIBSUMOCPP})
