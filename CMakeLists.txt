cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_custom_target(run 
                   COMMAND cg 
                   DEPENDS cg
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   )

project(cg VERSION 1.0)

add_subdirectory(lib/wxWidgets)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(cg ${SRC_FILES})

target_include_directories(cg PRIVATE inc)
target_link_libraries(cg wx::net wx::core wx::base)