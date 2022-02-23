#ifndef HEAPSORT_INL_INCLUDED
#define HEAPSORT_INL_INCLUDED

template<typename T>
void printArr(T *Arr, int Length, const char* label, int reclvl) //
{
    for(int j=0; j<reclvl;j++) std::cout<<"\t-";
    std::cout<<"===Arr ("<< label<<"):==="<<std::endl;
    for(int i=0; i<Length;i++)
    {
        for(int j=0; j<reclvl;j++) std::cout<<"\t-";
        std::cout<<"Arr["<<i<<"]="<<Arr[i]<<std::endl;
    }
}
template<typename T>
void Heapify(T *Arr, int Length, int i, bool SortOrder, bool IsStepbystep, int reclvl) //Восстанавливает свойства кучи, начиная с корня i. Предполагается, что левое и правое деревья удовлетворяют куче. SortOrder - направление сортировки. по умолчанию - по возрастанию(т.е. в корне кучи стоит наибольший элемент).
{
    
    if(IsStepbystep)
    {
        for(int i=0; i<reclvl;i++) std::cout<<"\t-";
        std::cout<<"Heapify started!"<<std::endl;
        printArr(Arr, Length, (char*)"Before Heapify", reclvl);
        getchar();
    }
    reclvl++;
    int LargestLowest=i;
    if(!SortOrder) //по умолчанию сортировка по возрастанию
    {
        if(2*i+1<Length && Arr[2*i+1]>Arr[LargestLowest]) LargestLowest=2*i+1;
        if(2*i+2<Length && Arr[2*i+2]>Arr[LargestLowest]) LargestLowest=2*i+2;
    }
    else
    {
        if(2*i+1<Length && Arr[2*i+1]<Arr[LargestLowest]) LargestLowest=2*i+1;
        if(2*i+2<Length && Arr[2*i+2]<Arr[LargestLowest]) LargestLowest=2*i+2;
    }
    if(LargestLowest!=i)
    {
        T temp=Arr[LargestLowest];
        Arr[LargestLowest]=Arr[i];
        Arr[i]=temp;
        Heapify<T>(Arr, Length, LargestLowest, SortOrder, IsStepbystep, reclvl);
    }
    reclvl--;
    if(IsStepbystep)
    {
        for(int i=0; i<reclvl;i++) std::cout<<"\t-";
        std::cout<<"Heapify finished!"<<std::endl;
        printArr(Arr, Length, (char*)"After Heapify", reclvl);
        getchar();
    }
}
template<typename T>
void BuildHeap(T *Arr, int Length, bool SortOrder, bool IsStepbystep) //строит кучу из неупорядоченного массива SortOrder - направление сортировки. по умолчанию - по возрастанию.(т.е. в корне кучи стоит наибольший элемент).
{
    if(IsStepbystep) std::cout<<"BuildHeap Started!"<<std::endl;
    for(int i=Length/2; i>=0; i--)
    {
        if(IsStepbystep) std::cout<<"BuildHeap: element will be Heapified:"<<i<<std::endl;
        Heapify<T>(Arr, Length, i, SortOrder, IsStepbystep, 0);
    }
    if(IsStepbystep)
    {
        std::cout<<"BuildHeap Finished!"<<std::endl;
        printArr(Arr, Length, (char*)"After BuildHeap", 0);
        getchar();
    }
}

template<typename T>
void HeapSort(T *Arr, int Length, bool SortOrder, bool IsStepbystep, int reclvl) //сортировка кучей. По умолчанию - по возрастанию.
{
    BuildHeap<T>(Arr, Length, SortOrder, IsStepbystep);
    for(int i=0; i<Length-1; i++)
    {
        T temp=Arr[0];
        Arr[0]=Arr[Length-1-i];
        Arr[Length-1-i]=temp;
        Heapify<T>(Arr, Length-1-i, 0, SortOrder, IsStepbystep, 0);
    }
}
#endif //HEAPSORT_INL_INCLUDED