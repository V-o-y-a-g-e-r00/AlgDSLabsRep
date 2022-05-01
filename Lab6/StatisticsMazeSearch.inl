#ifndef STATISTICSMAZE_INL
#define STATISTICSMAZE_INL

/*
#include <limits> //для определения максимального числа в типе
*/

#include <string>
#include <time.h> //для измерения времени
#include <fstream> //для файлов
#include <iomanip>      // std::setprecision
#include <random>

#include "maze.h"
#include "presenthandler.h"

//PresentHandler.Mode11 выводить лабиринты в терминал

class StatisticsMazeSearch
{
private:
    int CurrentN=0;
    int CurrentM=0;
    int NStart=0, NEnd=0, NStep=0;
    double MRatio=1; // M/N отношение ширины к длине 
    int NumberOfRuns=1; //число прогонов для текущих значений N M

public:
    StatisticsMazeSearch()=default;

 //   template<typename... CallBackParamsTail> //CallBackGenerate m WeightMax
    void StatisticsMazeSearchFunc1()
    {

    }

 //   template<typename... CallBackParamsTail> //CallBackGenerate m WeightMax
    template <typename T>    
    void StatisticsMazeSearchFunc(int NNStart, int NNEnd, int NNStep, double NMRatio, int NNumberOfRuns, std::default_random_engine& generator, presenthandler& PresentHandler, std::string filename, void (*CallBackSearch)(T&, int starti, int startj, int finishi, int finishj, std::vector<std::pair<int,int>>& Path, presenthandler& PrHandler))
    {
        NStart=NNStart; NEnd=NNEnd; NStep=NNStep; MRatio=NMRatio; NumberOfRuns=NNumberOfRuns;
        printLabel(filename);
        for(CurrentN=NStart; CurrentN<=NEnd; CurrentN+=NStep) //Цикл табуляции по высоте лабиринта N
        {
            CurrentM= CurrentN*MRatio;
            std::uniform_int_distribution<int> undistrStartFinishI(0, CurrentN-1);
            std::uniform_int_distribution<int> undistrStartFinishJ(0, CurrentM-1);
            double timeSeconds=0;
            for(int k=0; k<NumberOfRuns; k++) //Число прогонов для данной высоты лабиринта N
            {
                mazeWeighted MazeWeighted(CurrentN, CurrentM, 1);
                
                //Генерируем лабиринт без недостижимых областей с циклами. У ячеек устанавливаем веса от 1 до 10.
                std::cout<<"Maze generation started"<<std::endl;
            //    WilsonReduced(MazeWeighted, generator, PresentHandler, 0.3);
                int alpha=0;
                BinaryTree(MazeWeighted, generator, PresentHandler, alpha);
                WallsReduce(MazeWeighted, 0.3, generator);
                RandomCircules(MazeWeighted, generator, 2, 10, 0.05, 1, 0.5); //1, 3, 0.03, 2, 0.5
                std::cout<<"Maze generation ended"<<std::endl;
                if(PresentHandler.Mode==11) MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true, MazeWeighted.Weights);

                //Запускаем алг поиска по лабиринту
                int starti=undistrStartFinishI(generator);
                int startj=undistrStartFinishJ(generator);
                int finishi=undistrStartFinishI(generator);
                int finishj=undistrStartFinishJ(generator);
                if(PresentHandler.Mode==11)
                {
                    std::cout<<"start=("<<starti<<", "<<startj<<") finish=("<<finishi<<", "<<finishj<<")"<<std::endl;
                }
                std::vector<std::pair<int,int>> Path;

                std::cout<<"Maze search started"<<std::endl;
                clock_t timeStart=clock(); //число тиков с начала выполнения программы
                CallBackSearch(MazeWeighted, starti, startj, finishi, finishj, Path, PresentHandler);
                clock_t timeEnd=clock();
                std::cout<<"Maze search ended"<<std::endl;
                if(PresentHandler.Mode==11)
                {
                    PrintVector(Path, "Path");
                }

                timeSeconds+=double(timeEnd-timeStart)/CLOCKS_PER_SEC; //время работы алгоритма в секундах
                std::cout<<"CurrentN="<< CurrentN <<"; Iteration "<<k<<" is completed"<<std::endl;
            }
            timeSeconds/=NumberOfRuns;
            printValue(CurrentN, timeSeconds, filename);
        }
    }

    void printLabel(std::string filename) //пишем подпись оси высоты лабиринта в файл
    {
        std::ofstream fd(filename, std::ios_base::out|std::ios_base::trunc); //для записи очистив
        fd<< "#filename="<< filename<<"; MRatio="<<MRatio<<"; NumberOfRuns="<<NumberOfRuns<<std::endl;
        fd.close();
    }
    void printValue(int CurrentSize, double value, std::string filename) //пишем время выполнения в файл
    {
        std::ofstream fd(filename, std::ios_base::app); //для записи в конец

        fd<< CurrentN<< "\t"<<std::fixed <<std::setprecision(5)<<value<<std::endl;
       // fd<<std::endl;
        fd.close();
    }
};

#endif //STATISTICSMAZE_INL