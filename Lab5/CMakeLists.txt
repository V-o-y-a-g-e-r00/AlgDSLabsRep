cmake_minimum_required(VERSION 3.0.0)
project(Lab5 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Lab5 main.cpp) #Исследование алгоритмов ФлойдУоршелл Дейкстра БеллманФорд
add_executable(main_GenerateGraph_Demo main_GenerateGraph_Demo.cpp) #Демонстрация проверки связности. Поиск в глубину.
add_executable(main_Dijkstra_Demo main_Dijkstra_Demo.cpp)
add_executable(main_BellmanFord_Demo main_BellmanFord_Demo.cpp)
add_executable(main_VisualGraphDemo main_VisualGraphDemo.cpp) #Вывод графа в виде слова GRAPH
add_executable(main_GenerateAdjacency main_GenerateAdjacency.cpp) #Проверка генерации графа
add_executable(main_StatisticsGraph_SimpleDemo main_StatisticsGraph_SimpleDemo.cpp) #Демонстрация использования StatisticsGraph
add_executable(main_FromFileDebug main_FromFileDebug.cpp)

install(PROGRAMS PlotGraph.bash PlotScript.bash DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
