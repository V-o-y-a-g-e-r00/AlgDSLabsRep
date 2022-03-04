#ifndef STATISTICSGRAPH_INL_INCLUDED
#define STATISTICSGRAPH_INL_INCLUDED

#include <limits> //для определения максимального числа в типе
#include <time.h> //для измерения времени
#include <fstream> //для файлов
#include <iomanip>      // std::setprecision

#include <random>

#include "Graph.h"

class StatisticsGraph
{
private:
    int CurrentSize=0; //текущее число вершин в графе
    int CurrentM=0;

    int NStart=0, NEnd=0, NStep=0;
    double MRatio=0; //Отношение числа ребер к максимально возможному для данного графа (будет округляться до целого числа m)
    int WeightMax=0; //максимальный вес ребер графа
    int NumberOfRuns=1; //число прогонов для каждого размера(числа вершин) графа
public:
//в callback будут Vertices Edges SourceVert DestVert   параметры для результатов работы MPath MPathLenght для ФлойдаУоршелла  Lenght для Дейкстры и т.д.  PresentHandler
    template<typename... CallBackParamsTail> //CallBackGenerate m WeightMax
    StatisticsGraph(int NNStart, int NNEnd, int NNStep, double NMRatio, int NWeightMax, int NNumberOfRuns, std::default_random_engine& generator, presenthandler& PresentHandler, const char* filename, void (*CallBackGenerate)(Graph&, int, int, std::default_random_engine&, presenthandler&), void(*CallBackFind)(Graph&, CallBackParamsTail&...), CallBackParamsTail& ...callbackparamstail): NStart(NNStart), NEnd(NNEnd), NStep(NNStep), MRatio(NMRatio), WeightMax(NWeightMax), NumberOfRuns(NNumberOfRuns)
    {
        printLabel(filename);

        for(CurrentSize=NStart; CurrentSize<=NEnd; CurrentSize+=NStep) //Цикл табуляции по числу вершин N
        {
            double timeSeconds=0;

            for(int k=0; k<NumberOfRuns; k++) //Число прогонов для данного числа вершин N
            {
                Graph Graph1(CurrentSize);
                CurrentM= (Graph1.Edges.size()-1+0)*Graph1.Edges.size()/2 * MRatio; //максимально возможное количество ребер на интересующий нас процент
                CallBackGenerate(Graph1, CurrentM, WeightMax, generator, PresentHandler); //генерируем подходящий граф               
                
                clock_t timeStart=clock(); //число тиков с начала выполнения программы
                CallBackFind(Graph1, callbackparamstail...);
                clock_t timeEnd=clock();

                timeSeconds+=double(timeEnd-timeStart)/CLOCKS_PER_SEC; //время работы алгоритма в секундах
                
                std::cout<<"CurrentSize="<< CurrentSize <<"; Iteration "<<k<<" is complete"<<std::endl;
            }
            timeSeconds/=NumberOfRuns;
            printValue(CurrentSize, timeSeconds, filename);
       } 
    }
    void printLabel(const char* filename) //пишем подпись оси размера массива в файл
    {
        std::ofstream fd(filename, std::ios_base::out|std::ios_base::trunc); //для записи очистив
        fd<< "#filename="<< filename<<"; MRatio="<<MRatio<<"; WeightMax="<<WeightMax<<"; NumberOfRuns="<<NumberOfRuns<<std::endl;
        fd.close();
    }
    void printValue(int CurrentSize, double value, const char* filename) //пишем время выполнения в файл
    {
        std::ofstream fd(filename, std::ios_base::app); //для записи в конец

        fd<< CurrentSize<< "\t"<<std::fixed <<std::setprecision(3)<<value<<std::endl;
       // fd<<std::endl;
        fd.close();
    }
};
#endif //STATISTICSGRAPH_INL_INCLUDED