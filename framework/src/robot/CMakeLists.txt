
## INCLUDE DIRECTORIES 

# hpp files 
include_directories(include)
# src files 
include_directories(src)

## GLOB FILES 

file(
	GLOB_RECURSE 
	files_hpp
	*.hpp
)

file(
	GLOB_RECURSE 
	files_cpp
	*.cpp
)

## CREATE LIBRARY

add_library(lsr_robot
  ${files_cpp}
)

## INSTALL LIBRARY

target_include_directories(lsr_robot PUBLIC include)

target_link_libraries(lsr_robot 
					  PRIVATE 
					  lsr_element
					  lsr_sensor
					  lsr_instruction
					)

install (TARGETS lsr_robot
        DESTINATION lib)

install(FILES ${files_hpp}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)