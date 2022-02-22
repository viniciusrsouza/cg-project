cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  filelib 
  VERSION 1.0.0
  DESCRIPTION "file parsing library"
  LANGUAGES CXX
)

add_library(
  filelib STATIC
  inc/file.h
  src/file.cpp
)

target_include_directories(filelib PUBLIC inc)
set_target_properties(filelib PROPERTIES 
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER filelib.h
)
target_link_libraries(filelib mathlib)
