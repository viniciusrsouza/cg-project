cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
  mathlib 
  VERSION 1.0.0
  DESCRIPTION "linear algebra library"
  LANGUAGES CXX
)

add_library(
  mathlib STATIC
  inc/vec3.h
  src/vec3.cpp
  inc/mat3.h
  src/mat3.cpp
)

target_include_directories(mathlib PUBLIC inc)
set_target_properties(mathlib PROPERTIES 
  VERSION ${PROJECT_VERSION}
  SOVERSION 1
  PUBLIC_HEADER mathlib.h
)
