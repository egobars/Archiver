cmake_minimum_required(VERSION 3.0)
project(archiver)
add_library(BINARY_HEAP STATIC binary_heap.cpp)

# Setup testing
link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_custom_target(tests_binary_heap COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("binary_heap_tests" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("binary_heap_tests" gtest pthread BINARY_HEAP)
add_dependencies(tests_binary_heap "binary_heap_tests")
add_test("binary_heap_tests" "./binary_heap_tests")