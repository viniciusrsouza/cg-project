set(CG_SRC
  ${CG_SRC}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/window/buffered_pane.cpp
  PARENT_SCOPE
)

set(CG_INC
  ${CG_INC}
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  PARENT_SCOPE
  )