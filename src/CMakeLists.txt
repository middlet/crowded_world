#
# cmake for src directory of crowded_world
#

find_package( OpenCV REQUIRED )

include_directories(. ${COMMON_INCLUDES})

# include opencv
add_executable(cworld main.cpp world.cpp universe.cpp)
target_link_libraries(cworld ${OpenCV_LIBS})

# build libraries for linking with tests
add_library(world STATIC "world.cpp")
add_library(universe STATIC "universe.cpp")
