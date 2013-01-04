#
# cmake file for the crowd simulation code
#

project(CROWDED_WORLD)

cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -pthread)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
