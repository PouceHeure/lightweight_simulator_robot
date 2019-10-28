include_directories (${CMAKE_SOURCE_DIR}/include)

file(
	GLOB_RECURSE 
	headers
	*.hpp
)

add_library(collectif_robots_sim
  SHARED
  # scheduler file 
  scheduler.cpp

  # element files 
  board.cpp
  wall.cpp
  resource.cpp
  element.cpp
  robot.cpp
  cell.cpp

  # sensor files 
  ultrasonic_sensor.cpp
  detector_sensor.cpp
  i_sensor.cpp
  
  # communication files 
  i_topic.cpp
  interacter.cpp
  handle_communication.cpp

  
  )

install (TARGETS collectif_robots_sim
        DESTINATION lib)

install(FILES ${headers}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)