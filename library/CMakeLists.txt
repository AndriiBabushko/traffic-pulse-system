cmake_minimum_required(VERSION 3.14)

project(traffic_pulse_library VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/config/sumo)
# Copy entire "config/sumo/" directory structure to the build directory
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/config/sumo ${CMAKE_BINARY_DIR}/config/sumo
)

file(GLOB_RECURSE LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_definitions(-DCMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}")

find_package(PugiXML REQUIRED)
add_library(${PROJECT_NAME} STATIC ${LIBRARY_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

find_library(LIBSUMOCPP sumocpp HINTS /usr/lib /usr/local/lib)
if(NOT LIBSUMOCPP)
    message(FATAL_ERROR "libsumocpp not found! Please install SUMO with libsumo-cpp support.")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBSUMOCPP} pugixml)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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
