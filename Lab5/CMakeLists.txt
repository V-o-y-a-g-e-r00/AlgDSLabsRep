cmake_minimum_required(VERSION 3.0.0)
project(Lab5 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Lab5 main.cpp)
install(PROGRAMS PlotGraph.bash PlotScript.gpi DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
