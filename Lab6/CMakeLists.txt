cmake_minimum_required(VERSION 3.0.0)
project(Lab6 VERSION 0.1.0)

#include(CTest)
#enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

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
#Алг поиска пути в лабиринте, основанные на поиске на графах с ребрами с различными весами.
add_executable(Dijkstra Dijkstra_main.cpp)
add_executable(AStar AStar_main.cpp)
#Сбор статистики с генерации лабиринтов
add_executable(StatisticsMazeSearch_main StatisticsMazeSearch_main.cpp)

#cli программа с меню
add_executable(cli cli_main.cpp)
add_executable(cli_debug cli_debug_main.cpp)

#Собирает проект перед каждым копированием. файлов. Не удобно
#install(PROGRAMS PlotScript.bash Welcome.txt Menu.txt Help.txt Config.txt MazeIn.txt MazeOut.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#Тут задаем копируемые в директорию с бинарниками файлы
set(rwxList PlotScript.bash)
set(rwList Welcome.txt Menu.txt Help.txt Config.txt MazeIn.txt MazeOut.txt)

#Это все не трогаем. Это нужно, чтобы передать лист в скрипт.
string(REPLACE ";" "\\;" rwxList "${rwxList}")
string(REPLACE ";" "\\;" rwList "${rwList}")

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/copyfiles.cmake DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(copyfile)
add_custom_command(TARGET copyfile COMMAND ${CMAKE_COMMAND} -DSRCDIR=${CMAKE_CURRENT_SOURCE_DIR} -DDSTDIR=${CMAKE_CURRENT_BINARY_DIR} -DrwxList="${rwxList}" -DrwList="${rwList}" -P ${CMAKE_CURRENT_SOURCE_DIR}/copyfiles.cmake)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
