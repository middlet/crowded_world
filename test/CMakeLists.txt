#
# cmake for the test directory of crowded_world
#

find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(. ${COMMON_INCLUDES})

add_executable(world_test world_test.cpp)
target_link_libraries(world_test world ${GTEST_BOTH_LIBRARIES} pthread ${OpenCV_LIBS})
add_test(world_test world_test)


