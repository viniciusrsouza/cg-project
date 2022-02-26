cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_custom_target(run 
                   COMMAND cglib 
                   DEPENDS cglib
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/web/public/dist")
set(CMAKE_EXECUTABLE_SUFFIX ".js")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project(cglib VERSION 1.0)

add_subdirectory(math)
add_subdirectory(file)
add_subdirectory(render)

add_executable(cglib ${SRC})

target_include_directories(cglib PRIVATE ${INC})
target_link_libraries(cglib mathlib filelib)
set_target_properties(cglib PROPERTIES
  PUBLIC_HEADER render/inc/entry.h
  LINK_FLAGS "-s WASM=1 -s EXPORTED_FUNCTIONS=_c_render,_dbg,_malloc -s EXPORTED_RUNTIME_METHODS=ccall,cwrap,allocateUTF8 -s FORCE_FILESYSTEM=1 -lidbfs.js"
)