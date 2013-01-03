#
# cmake for src directory of crowded_world
#
project(CROWDED_WORLD)

cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )

include_directories(.)
set(CMAKE_CXX_FLAGS "-g")
# opencv version
add_executable(cworld main.cpp)
target_link_libraries(cworld ${OpenCV_LIBS})
