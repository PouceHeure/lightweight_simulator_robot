
## INCLUDE DIRECTORIES 

# hpp files 
include_directories(include)
# src files 
include_directories(src)

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../utils/include")

## GLOB FILES 

file(
	GLOB_RECURSE 
	files_hpp
	*.hpp
)

foreach(f ${files_hpp})
message("fichier: ${f}")
endforeach(f)


file(
	GLOB_RECURSE 
	files_cpp
	*.cpp
)

## CREATE LIBRARY

add_library(lsr_env
  ${files_cpp}
)

## INSTALL LIBRARY

target_include_directories(lsr_env PUBLIC include)

target_link_libraries(lsr_env 
					  PRIVATE 
					  lsr_element
					  lsr_utils
					)

install (TARGETS lsr_env
        DESTINATION lib)

install(FILES ${headers}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)


