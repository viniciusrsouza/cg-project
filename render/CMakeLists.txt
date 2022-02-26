set(SRC
  ${SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/context.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/render.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/inc/shaders/basic_shader.h
  PARENT_SCOPE
)

set(INC
  ${INC}
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  PARENT_SCOPE
)