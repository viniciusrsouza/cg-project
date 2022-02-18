cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cg VERSION 1.0)

add_subdirectory(lib/wxWidgets)
add_executable(cg src/main.cpp)
target_link_libraries(cg wx::net wx::core wx::base)