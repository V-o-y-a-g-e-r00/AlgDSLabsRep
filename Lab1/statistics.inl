#ifndef STATISTICS_INL_INCLUDED
#define STATISTICS_INL_INCLUDED

#include <limits> //для определения максимального числа в типе
#include <time.h> //для измерения времени
#include <fstream> //для файлов
#include <iomanip>      // std::setprecision

template<typename T>
class statistics
{
private:
    int CurrentSize=0; //текущее число элементов в массиве
    T* Arr=nullptr;
    int NStart=0, NEnd=0, NStep=0;
    int RandMax=-1; //-1  случ значения в массиве будут генерироваться на всем допустимом диапазоне для данного типа.
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
        fd<< "#filename="<< filename<<"; RandMax="<<RandMax<<"; NumberOfRuns="<<NumberOfRuns<<std::endl;
     /*   for(int i=NStart; i<=NEnd;i+=NStep)
        {
            fd<<i<<" ";
        }
        fd<<std::endl; */
        fd.close();
    }
    void printValue(int CurrentSize, double value, char* filename) //пишем время выполнения в файл
    {
        std::ofstream fd(filename, std::ios_base::app); //для записи в конец

        fd<< CurrentSize<< "\t"<<std::fixed <<std::setprecision(9)<<value<<std::endl;
       // fd<<std::endl;
        fd.close();
    }
};
#endif //STATISTICS_INL_INCLUDED