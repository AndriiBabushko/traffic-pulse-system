add_executable(library_tests hello_test1.cpp)

target_link_libraries(library_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(library_tests)