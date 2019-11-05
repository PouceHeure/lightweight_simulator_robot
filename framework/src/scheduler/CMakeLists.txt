
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

add_library(lsr_scheduler
  SHARED
  ${files_cpp}
)

## INSTALL LIBRARY

target_include_directories(lsr_scheduler PUBLIC include)

target_link_libraries(lsr_scheduler 
					  PRIVATE 
					  lsr_env
					  lsr_robot
					  lsr_recorder
					)

install (TARGETS lsr_scheduler
        DESTINATION lib)

install(FILES ${files_hpp}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)