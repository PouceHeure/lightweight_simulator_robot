cmake_minimum_required( VERSION 2.8 )

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project (light_simulator_robots)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(doc)