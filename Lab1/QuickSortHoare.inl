#ifndef QUICKSORTHOARE_INL_INCLUDED
#define QUICKSORTHOARE_INL_INCLUDED

#include <iostream>
//using namespace std;
/*template<typename T>
void printArr(T *Arr, int Length, char* label, int reclvl) //
{
    for(int j=0; j<reclvl;j++) std::cout<<"\t-";
    std::cout<<"===Arr ("<< label<<"):==="<<std::endl;
    for(int i=0; i<Length;i++)
    {
        for(int j=0; j<reclvl;j++) std::cout<<"\t-";
        std::cout<<"Arr["<<i<<"]="<<Arr[i]<<std::endl;
    }
}
*/

 
void QuickSortHoare(int *Arr, int size, bool SortOrder, bool IsStepbystep, int reclvl) {
    int i = 0, j = size-1; //номера элементов, движущиеся от концов к центру
    int temp, p;
    p = Arr[size>>1]; //берем средний элемент


   // std::cout<<"size>>1 ="<< (size>>1) <<std::endl;
    if(IsStepbystep)
    {
        std::cout<<"pivot is  Arr["<<(size>>1)<<"]=p="<< p <<std::endl;
    }


    do {
        while (Arr[i] < p) i++;
        while (Arr[j] > p) j--;

        if(IsStepbystep)
        {
            std::cout<<"Current i:(Arr[i] !< p) ="<< i <<"; Current j:(Arr[j] !> p) ="<< j << std::endl;
            getchar();
        }

        if (i <= j)
        {
            temp = Arr[i];
            Arr[i] = Arr[j];
            Arr[j] = temp;
            i++;
            j--;

            if(IsStepbystep)
            {
            printArr<int>(Arr, size, (char*)"After swap", reclvl);
            getchar();
            }
        }
    } while (i<=j);
    reclvl++;
    if (j >= 1) QuickSortHoare(Arr, j+1, SortOrder, IsStepbystep, reclvl);
    if (size-2 >= i) QuickSortHoare(Arr+i, size-i, SortOrder, IsStepbystep, reclvl);
    reclvl--;
}


#endif //QUICKSORTHOARE_INL_INCLUDED


/*
 
int main()
{
setlocale(LC_ALL,"Rus");
int size, i;
int *Arr;
srand(time(NULL));
//cout<<"Введите размер массива"<<endl;
//cin>>size;
size=8;

Arr=new int [size];


for (i=0; i<size; i++)
{
Arr[i]=i;
}
Arr[3]=1;



for (i=0; i<size; i++)
{
//Arr[i]=rand()%100;
cout<<Arr[i]<<" ";
}
cout<<endl;


QuickSortR(Arr, size);
cout<<"Отсортированный массив"<<endl;
for (i=0; i<size; i++)
{
cout<<Arr[i]<<" ";
}
delete[] Arr;
cout<<endl;
}
*/