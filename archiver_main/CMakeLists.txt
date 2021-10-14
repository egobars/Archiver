cmake_minimum_required(VERSION 3.0)
project(archiver)
add_subdirectory(../reader ${CMAKE_CURRENT_BINARY_DIR}/reader)
add_subdirectory(../trie ${CMAKE_CURRENT_BINARY_DIR}/trie)
add_subdirectory(../writer ${CMAKE_CURRENT_BINARY_DIR}/writer)
add_subdirectory(../binary_heap ${CMAKE_CURRENT_BINARY_DIR}/binary_heap)
add_library(ARCHIVER_MAIN STATIC archiver_main.cpp)
target_link_libraries(ARCHIVER_MAIN READER TRIE WRITER BINARY_HEAP)

file(COPY ${CMAKE_SOURCE_DIR}/archiver_main/tests/mock DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Setup testing
link_directories(/usr/local/lib)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_custom_target(tests_archiver_main COMMAND GTEST_COLOR=yes ${CMAKE_CTEST_COMMAND} --verbose)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable("archiver_main_tests" EXCLUDE_FROM_ALL ${TEST_FILES})
target_link_libraries("archiver_main_tests" gtest pthread ARCHIVER_MAIN)
add_dependencies(tests_archiver_main "archiver_main_tests")
add_test("archiver_main_tests" "./archiver_main_tests")