# Add the root test executable
add_executable(root_tests hello_test.cpp)

# Link the GoogleTest main library
target_link_libraries(root_tests PRIVATE gtest_main)

# Register the test with CMake
include(GoogleTest)
gtest_discover_tests(root_tests)