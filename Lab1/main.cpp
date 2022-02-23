#include <iostream>

#include "statistics.inl"
#include "HeapSort.inl"
#include "QuickSortHoare.inl"
#include "ShellSort.inl"

int main(int, char**) {

    srand(time(0));
//Аргументы подставлены для пошагового выполнения    
/*    std::cout<<"HeapSort:"<<std::endl;
    statistics<int> s1(HeapSort<int>, 5, 5, 10000, false, true, 100, 1,(char*)"HeapSortOut.txt");
    std::cout<<"QuickSortHoare:"<<std::endl;
    statistics<int> s2(QuickSortHoare, 5, 5, 10000, false, true, 100, 1,(char*)"QuickSortHoareOut.txt");
    std::cout<<"ShellSort:"<<std::endl;
    statistics<int> s3(ShellSort, 5, 5, 10000, false, true, 100, 1,(char*)"ShellSortOut.txt");
*/
//Агрументы для массивов больших размеров
    std::cout<<"HeapSort:"<<std::endl;
    statistics<int> s1(HeapSort<int>, 100, 1000, 100, false, false, -1, 1000,(char*)"HeapSortOut.txt");
    std::cout<<"QuickSortHoare:"<<std::endl;
    statistics<int> s2(QuickSortHoare, 100, 1000, 100, false, false, -1, 1000,(char*)"QuickSortHoareOut.txt");
    std::cout<<"ShellSort:"<<std::endl;
    statistics<int> s3(ShellSort, 100, 1000, 100, false, false, -1, 1000,(char*)"ShellSortOut.txt");
    system("./PlotScript.gpi");



/*
    int Arr[10];
    Arr[0]=132;
    Arr[1]=97;
    Arr[2]=93;
    Arr[3]=170;
    Arr[4]=176;
    Arr[5]=131;
    Arr[6]=48;
    Arr[7]=32;
    Arr[8]=92;
    Arr[9]=114;

    QuickSortHoare(Arr, 10, false, true, 0);
    printArr(Arr, 10, (char *)"AfterSort", 0); */
}
