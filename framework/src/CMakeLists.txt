SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

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
  wall.cpp
  resource.cpp
  element.cpp
  unknown.cpp

  # robot files 
  robot.cpp
  
  # env files 
  board.cpp
  cell.cpp

  # sensor files 
  ultrasonic_sensor.cpp
  detector_sensor.cpp
  i_sensor.cpp
  
  # communication files 
  i_topic.cpp
  interacter.cpp
  handle_communication.cpp

  # recorder files 
  i_recorder.cpp
  server.cpp
  payload.cpp
  )

find_package (Threads)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(collectif_robots_sim ${CMAKE_THREAD_LIBS_INIT})  

install (TARGETS collectif_robots_sim
        DESTINATION lib)

install(FILES ${headers}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)