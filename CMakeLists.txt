cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_custom_target(run 
                   COMMAND cg 
                   DEPENDS cg
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project(cg VERSION 1.0)

add_subdirectory(math)
add_subdirectory(file)
add_subdirectory(render)

add_library(cg STATIC ${SRC})

target_include_directories(cg PRIVATE ${INC})
target_link_libraries(cg mathlib filelib)
set_target_properties(cg PROPERTIES 
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER render/renderlib.h
)