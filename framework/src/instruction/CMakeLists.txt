
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

add_library(lsr_instruction
  ${files_cpp}
)

## INSTALL LIBRARY

target_include_directories(lsr_instruction PUBLIC include)

install (TARGETS lsr_instruction
        DESTINATION lib)

install(FILES ${files_hpp}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)