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
  cell.cpp
  ultrasonic_sensor.cpp
  i_sensor.cpp
  
  i_publisher.cpp
  i_subscriber.cpp
  i_topic.cpp
  interacter.cpp
  handle_communication.cpp

  
  )

install (TARGETS collectif_robots_sim
        DESTINATION lib)

install(FILES ${headers}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)