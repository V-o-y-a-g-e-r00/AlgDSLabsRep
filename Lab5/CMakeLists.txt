cmake_minimum_required(VERSION 3.0.0)
project(Lab5 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Lab5 main.cpp)
add_executable(main_GenerateGraph_Demo main_GenerateGraph_Demo.cpp)
add_executable(main_Dijkstra_Demo main_Dijkstra_Demo.cpp)
add_executable(main_BellmanFord_Demo main_BellmanFord_Demo.cpp)
add_executable(main_VisualGraphDemo main_VisualGraphDemo.cpp)
install(PROGRAMS PlotGraph.bash PlotScript.bash DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
