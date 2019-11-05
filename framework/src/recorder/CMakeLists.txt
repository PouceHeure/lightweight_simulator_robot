## ADD FLAGS 

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

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

add_library(lsr_recorder
  ${files_cpp}
)

## INSTALL LIBRARY

target_include_directories(lsr_recorder PUBLIC include)

find_package (Threads)
target_link_libraries(lsr_recorder ${CMAKE_THREAD_LIBS_INIT} lsr_env)  

install (TARGETS lsr_recorder
        DESTINATION lib)

install(FILES ${files_hpp}
  DESTINATION include/${CMAKE_PROJECT_NAME}
)