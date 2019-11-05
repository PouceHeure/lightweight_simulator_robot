
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

add_library(lsr_element
  ${files_cpp}
)

## INSTALL LIBRARY

install (TARGETS lsr_element
        DESTINATION lib)

install(FILES ${headers}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)

target_include_directories(lsr_element PUBLIC include)