set(CG_SRC
  ${CG_SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/window/buffered_pane.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/context/context.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/context/camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/context/shader.cpp
  PARENT_SCOPE
)

set(CG_INC
  ${CG_INC}
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  PARENT_SCOPE
)