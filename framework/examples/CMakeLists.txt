include_directories (${CMAKE_SOURCE_DIR}/include)
include_directories (${CMAKE_SOURCE_DIR}/src)

file(
    GLOB 
    usage_examples
	  example-*.cpp
)

foreach(f ${usage_examples})
  get_filename_component(exampleName ${f} NAME_WE) 
  add_executable (${exampleName} ${f}) 
  target_link_libraries(${exampleName} collectif_robots_sim)
  install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${exampleName}
    DESTINATION bin
    RENAME ${CMAKE_PROJECT_NAME}-${exampleName})
endforeach(f)
