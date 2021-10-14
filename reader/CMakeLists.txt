cmake_minimum_required(VERSION 3.0)
project(archiver)
add_library(READER STATIC reader.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/reader/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Setup testing
link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_custom_target(tests_reader COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("reader_tests" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("reader_tests" gtest pthread READER)
add_dependencies(tests_reader "reader_tests")
add_test("reader_tests" "./reader_tests")
