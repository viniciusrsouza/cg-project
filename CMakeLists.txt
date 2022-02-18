cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/wxWidgets)

project(cg VERSION 1.0)

add_executable(cg src/main.cpp)