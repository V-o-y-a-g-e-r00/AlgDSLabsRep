#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {
//  int seed=time(0);
    int seed=2;
    std::default_random_engine generator1(seed);
    presenthandler PrHandler;
    PrHandler.Mode=1;
  
    mazeWeighted MazeWeighted(10,10, 1);
    //Генерация лабиринта
    WilsonReduced(MazeWeighted, generator1, PrHandler, 0.3);
    RandomCircules(MazeWeighted, generator1, 2, 9, 0.05, 1, 0.5); //1, 3, 0.03, 2, 0.5
    //MazeWeighted.SetCellWalls(0,0,0,true);
    //MazeWeighted.SetCellWalls(0,0,3,true);
    //Вывод весов лабиринта
//    MazeWeighted.WeightsToValues();
//    std::cout<<"Weights:"<<std::endl;
//    MazeWeighted.ShowDecorate((char*)"cout",1, 2, true);
    
    //Запуск алгоритма
    std::vector<std::pair<int,int>> Path;
    AStar(MazeWeighted, 0, 0, 2, 2, Path, PrHandler);
    PrintVector(Path, "Path");

}

