cmake_minimum_required(VERSION 3.0.0)
project(statistics VERSION 0.1.0)

#include(CTest)
#enable_testing()

add_executable(statistics main.cpp)
#install(FILES PlotScript.gpi DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) Не подходит, т.к. не сохраняет права доступа
install(PROGRAMS PlotScript.gpi DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_custom_target(new_target
#    ${CMAKE_COMMAND} -E copy PlotScript.gpi ${CMAKE_BINARY_DIR}/PlotScript.gpi
#  )
#add_executable(QuickSortHoare QuickSortHoare.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
