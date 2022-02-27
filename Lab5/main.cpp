#include <iostream>

#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip> //setprecision
//#include <string> //будем использовать для нахождения максимальной точности вероятности

#include <random> 

#define RADIUS 40
struct point
{
    int VertIndex=0;
    double x=0;
    double y=0;
};

void SetVertCoord(int N, int CenterX=0, int CenterY=0, const char* fname="pnts.dat")
{
    double r=RADIUS;
    double alpha=0;
    double dalpha=2*M_PI/N;
    
    double x, y;
    int CurrVertIndex=0;
    std::vector<point> pnts(N); 

    std::vector<point>::iterator iter; //вектор с информацией об индексах и координатах вершин
    for(int i=0; i<N; i++)
    {
        //(i%2==0) ? r/=1.5 : r*=1.5;
        
        pnts.at(i).VertIndex=CurrVertIndex;
        pnts.at(i).x=cos(alpha)*r;
        pnts.at(i).y=sin(alpha)*r;
        
        if(i%8<4) r-=RADIUS*0.15; //в виде звезды
        else r+=RADIUS*0.15;

        CurrVertIndex++;
        alpha+=dalpha;
    }

    iter=pnts.begin();
    while(iter!=pnts.end()) //выводим индексы и координаты вершин на экран
    {
        std::cout<< "pnts element:"<< std::distance(pnts.begin(),iter)<<" :VertIndex="<< iter->VertIndex<< "; x="<<iter->x<<"; y="<<iter->y<<std::endl;
        iter++;
    }

    std::ofstream fd(fname, std::ios_base::out|std::ios_base::trunc); //выводим индексы и координаты вершин в файлик
    iter=pnts.begin();
    while(iter!=pnts.end())
    {
        fd<< std::fixed <<std::setprecision(3)<<iter->VertIndex<< "\t"<<iter->x<<"\t"<<iter->y<<std::endl;
        iter++;
    }
    fd.close();
}
/*bool EventHappend(double probability, int precision) //Для хороших результатов здесь нужно не использовать большие percision
{
    
    if(pow(10, precision)>=RAND_MAX) //плохой способ. При больших precision (сопоставимых с RAND_MAX) события с меньшей вероятностью будут генерироваться в 2 раза чаще, чем с большей вероятностью.
    {
        std::cout<<"precision can not be reached!"<<std::endl;
        getchar();
        return;
    }
}*/
void GenerateAdjacencyMatrix(std::vector<std::vector<int>>& AdjacencyMatrix, int seed, double probability) //генерируем матрицу смежности
{
    //настраиваем генератор
    std::default_random_engine generator(seed);
    std::discrete_distribution<int> distribution {1-probability, probability}; //единички генерируются с вероятностью probability, а нолики с вероятностью 1-probability

    std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
    std::vector<int>::iterator iterj;
    for(int i=0; i<AdjacencyMatrix.size(); i++)
    {
        for(int j=0; j<AdjacencyMatrix.at(i).size();j++)
        {
            if(j>=i)
            {
                //int dice_roll = distribution(generator);
                AdjacencyMatrix.at(i).at(j)=distribution(generator); //генерируем ребро.
            }
            else
            {
                AdjacencyMatrix.at(i).at(j)=AdjacencyMatrix.at(j).at(i); //граф неориентированный
            }
        }
    }
    /*
    iteri=AdjacencyMatrix.begin(); //зануляем все элементы
    while(iteri !=AdjacencyMatrix.end())
    {
        iterj=iteri->begin();
        while(iterj!=iteri->end())
        {
            //int dice_roll = distribution(generator);
            *iterj=distribution(generator); //генерируем ребро.
            iterj++;
        }
        iteri++;
    }
    */


}
template<typename T>
void PrintMatrix(std::vector<std::vector<T>> Matrix, const char* MatrixName)
{
    typename std::vector<std::vector<T>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам) .Без typename вообще не компилируется, хотя казалось бы.
    typename std::vector<T>::iterator iterj;
    for(iteri=Matrix.begin(); iteri!=Matrix.end(); iteri++)
    {
        std::cout<< MatrixName<<"["<<std::distance(Matrix.begin(), iteri) <<"]=";
        for(iterj=iteri->begin(); iterj!=iteri->end(); iterj++)
        {
            std::cout<< (*iterj)<<"\t";
        }
        std::cout<<std::endl;
    }
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
   // int seed=time(0);
    int seed=0;

    int N=10;
    std::vector<std::vector<int>> AdjacencyMatrix(N);
    std::vector<std::vector<int>>::iterator iteri;
    for(iteri=AdjacencyMatrix.begin(); iteri!=AdjacencyMatrix.end(); iteri++)
    {
        iteri->resize(N);
        std::cout<< "iteri->size()"<<iteri->size()<<std::endl;
    }
  //  std::cout<< "AdjacencyMatrix.size()"<<AdjacencyMatrix.size()<<std::endl;
 //   std::cout<< "AdjacencyMatrix.at(0).size()"<<AdjacencyMatrix.at(0).size()<<std::endl;
  //  std::cout<< "AdjacencyMatrix[0][0]"<<AdjacencyMatrix.at(0).at(0)<<std::endl;
    GenerateAdjacencyMatrix(AdjacencyMatrix, seed, 0.66);
//   std::cout<< "AdjacencyMatrix[0][0]"<<AdjacencyMatrix.at(0).at(0)<<std::endl;

    PrintMatrix<int>(AdjacencyMatrix, "AdjacencyMatrix");
//   SetVertCoord(50);
//    system("./PlotGraph.gpi");

   /* int seed=0;
    seed=time(0);
    std::default_random_engine generator(seed);
    std::discrete_distribution<int> distribution {0,1};;
    
    int dice_roll = distribution(generator);  // generates number in the range 1..6
    int Arr[10];
    for(int i=0;i<10;i++)
    {
        int dice_roll = distribution(generator);
        std::cout << "dice_roll="<<dice_roll<<std::endl;   
    }
*/
}
