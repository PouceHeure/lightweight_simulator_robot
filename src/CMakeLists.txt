include_directories (${CMAKE_SOURCE_DIR}/include)

file(
	GLOB_RECURSE 
	headers
	*.hpp
)

add_library(collectif_robots_sim
  SHARED
  board.cpp
  wall.cpp
  element.cpp
  scheduler.cpp
  robot.cpp
  cell.cpp)

install (TARGETS collectif_robots_sim
        DESTINATION lib)

install(FILES ${headers}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)