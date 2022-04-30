cmake_minimum_required(VERSION 3.0.0)
project(Lab6 VERSION 0.1.0)

#include(CTest)
#enable_testing()

#Разработка класса лабиринта
add_executable(maze_debug_main maze_debug_main.cpp)
add_executable(mazeWeighted_debug_main mazeWeighted_debug_main.cpp)
#Алг генерации лабиринтов
add_executable(AldousBroder AldousBroder_main.cpp)
add_executable(Wilson Wilson_main.cpp)
add_executable(BinaryTree BinaryTree_main.cpp)
#Сбор статистики с генерации лабиринтов
add_executable(StatisticsMaze StatisticsMaze_main.cpp)
#Алг поиска пути в лабиринте
add_executable(Lee Lee_main.cpp)
add_executable(Lee2Waves Lee2Waves_main.cpp)

add_executable(AStar AStar_main.cpp)

install(PROGRAMS PlotScript.bash DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
