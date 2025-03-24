cmake_minimum_required(VERSION 3.14)
project(traffic_simulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(LIBSUMOCPP sumocpp HINTS /usr/lib /usr/local/lib)
if(NOT LIBSUMOCPP)
    message(FATAL_ERROR "libsumocpp not found! Please install SUMO with libsumo-cpp support.")
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.15.2
)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(library)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE traffic_pulse_library ${LIBSUMOCPP} pugixml)

enable_testing()

if(EXISTS "${CMAKE_SOURCE_DIR}/tests")
    add_subdirectory(tests)
endif()
