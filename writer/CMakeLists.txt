cmake_minimum_required(VERSION 3.0)
project(archiver)
add_library(WRITER STATIC writer.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/writer/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Setup testing
link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_custom_target(tests_writer COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("writer_tests" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("writer_tests" gtest pthread WRITER)
add_dependencies(tests_writer "writer_tests")
add_test("writer_tests" "./writer_tests")