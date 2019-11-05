
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

add_library(lsr_communication
  SHARED
  ${files_cpp}
)


## INSTALL LIBRARY

target_include_directories(lsr_communication PUBLIC include)

install (TARGETS lsr_communication
        DESTINATION lib)

install(FILES ${files_hpp}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)