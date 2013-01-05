#
# cmake for src directory of crowded_world
#

find_package( OpenCV REQUIRED )

include_directories(. ${COMMON_INCLUDES})

# include opencv
add_executable(cworld main.cpp world.cpp)
target_link_libraries(cworld ${OpenCV_LIBS})

# build library for linking with tests
add_library(world STATIC "world.cpp")
