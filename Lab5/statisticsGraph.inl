#ifndef STATISTICSGRAPH_INL_INCLUDED
#define STATISTICSGRAPH_INL_INCLUDED

#include <limits> //для определения максимального числа в типе
#include <time.h> //для измерения времени
#include <fstream> //для файлов
#include <iomanip>      // std::setprecision

#include <random>

#include "vertices.h"
#include "edges.h"

class statisticsGraph
{
private:
    int CurrentSize=0; //текущее число вершин в графе

    int NStart=0, NEnd=0, NStep=0;
    double MRatio=0; //Отношение числа ребер к максимально возможному для данного графа (будет округляться до целого числа m)
    int WeightMax=0; //максимальный вес ребер графа
    int NumberOfRuns=1; //число прогонов для каждого размера(числа вершин) графа
public:
//в callback будут Vertices Edges SourceVert DestVert   параметры для результатов работы MPath MPathLenght для ФлойдаУоршелла  Lenght для Дейкстры и т.д.  PresentHandler
    template<typename... CallBackParamsTail>
    statisticsGraph(int NNStart, int NNEnd, int NNStep, double MRatio, int WeightMax, int NNumberOfRuns, std::default_random_engine& generator, const char* filename, void(*CallBack)(vertices&, edges&, CallBackParamsTail...), CallBackParamsTail ...callbackparamstail)
    {

    }



};


template<typename T>
class statistics
{
private:
    int CurrentSize=0; //текущее число элементов в массиве
    T* Arr=nullptr;
    int NStart=0, NEnd=0, NStep=0;
    int RandMax=0;
    int NumberOfRuns=1; //число прогонов для каждого размера массива
public:
    statistics(void (*callback)(T*, int, bool, bool, int), int NNStart, int NNEnd, int NNStep, bool SortOrder, bool IsStepbystep, int NRandMax, int NNumberOfRuns, char* filename, int seed): NStart(NNStart), NEnd(NNEnd), NStep(NNStep), RandMax(NRandMax), NumberOfRuns(NNumberOfRuns) //Начальное, конечное значение числа элементов; IsStepbystep выводить пошагово; RandMax макс случайное число (-1 будут значения от 0 до максимального в данном типе). filename - файл для вывода seed для генерации одинаковых массивов
    {
        if(seed!=-1) srand(seed);
        printLabel(filename);

        for(CurrentSize=NStart; CurrentSize<=NEnd; CurrentSize+=NStep)
        {
            Arr=new T [CurrentSize];
            double timeSeconds=0;
            for(int k=0; k<NumberOfRuns; k++) //
            {
                for(int j=0; j<CurrentSize; j++) //заполняем массив
                {
                    if(RandMax==-1) Arr[j]=rand() % ((unsigned long long)std::numeric_limits<T>::max()+1); //по максимальное значение в этом типе
                    else Arr[j]=rand() % RandMax;
                }
                if(IsStepbystep)  printArr((char*)"before sort"); //выводим массив со случайными значениями
                clock_t timeStart=clock(); //число тиков с начала выполнения программы
                callback(Arr, CurrentSize, SortOrder, IsStepbystep, 0);
                clock_t timeEnd=clock();
                timeSeconds+=double(timeEnd-timeStart)/CLOCKS_PER_SEC; //время работы алгоритма в секундах
                if(IsStepbystep)   printArr((char*)"after sort"); //выводим массив после сортировки
                std::cout<<"CurrentSize="<< CurrentSize <<"; Iteration "<<k<<" is complete"<<std::endl;
            }
            timeSeconds/=NumberOfRuns;
            delete[] Arr;
            printValue(CurrentSize, timeSeconds, filename);
       } 
    }
    void printArr(char* label)
    {
        std::cout<<"===Arr ("<< label<<"):==="<<std::endl;
        for(int i=0; i<CurrentSize; i++)
        {
            std::cout<<"Arr["<<i<<"]="<<Arr[i]<<std::endl;
        }
    }
    void printLabel(char* filename) //пишем подпись оси размера массива в файл
    {
        std::ofstream fd(filename, std::ios_base::out|std::ios_base::trunc); //для записи очистив
        fd<< "#filename="<< filename<<"; Edges Count ratio to max edges count="<<   <<"; WeightMax="<<WeightMax<<"; NumberOfRuns="<<NumberOfRuns<<std::endl;
        fd.close();
    }
    void printValue(int CurrentSize, double value, char* filename) //пишем время выполнения в файл
    {
        std::ofstream fd(filename, std::ios_base::app); //для записи в конец

        fd<< CurrentSize<< "\t"<<std::fixed <<std::setprecision(3)<<value<<std::endl;
       // fd<<std::endl;
        fd.close();
    }
};
#endif //STATISTICSGRAPH_INL_INCLUDED