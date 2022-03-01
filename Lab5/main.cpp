#include <iostream>

#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip> //setprecision
//#include <string> //будем использовать для нахождения максимальной точности вероятности

#include <random> 

#define RADIUS 40
struct vertex
{
    int VertIndex=0;
    double x=0;
    double y=0;
    int Color=11; //Определяет стиль в gnuplot. 11 белый; 12 зеленый; 13 голубой; 14 красный

};
struct edge
{
    int Color=1; //1 черный 2 зеленый; 3 голубой; 4 красный

    int Adjacency=0; //существование ребра
    int Weight=0; //вес ребра
};

void SetVertXYForPlot(std::vector<vertex> Vertices, int CenterX=0, int CenterY=0, const char* fname="Vertices.dat")
{
    double r=RADIUS;
    double alpha=0;
    double dalpha=2*M_PI/Vertices.size();
    
    double x, y;
    int CurrVertIndex=0;
   // std::vector<point> pnts(N); 

 //   std::vector<point>::iterator iter; //вектор с информацией об индексах и координатах вершин
 //   std::vector<vertex>::iterator iter;
    for(int i=0; i<Vertices.size(); i++)
    {
        //(i%2==0) ? r/=1.5 : r*=1.5;
        
        Vertices.at(i).VertIndex=i;
        Vertices.at(i).x=cos(alpha)*r;
        Vertices.at(i).y=sin(alpha)*r;
        
        if(i%8<4) r-=RADIUS*0.15; //в виде звезды
        else r+=RADIUS*0.15;

     //   CurrVertIndex++;
        alpha+=dalpha;
    }

    std::vector<vertex>::iterator iter=Vertices.begin();
    for(iter=Vertices.begin();iter!=Vertices.end();iter++) //выводим индексы и координаты вершин на экран
    {
        std::cout<< "vertices element:"<< std::distance(Vertices.begin(),iter)<<" :VertIndex="<< iter->VertIndex<< "; x="<<iter->x<<"; y="<<iter->y<<"; Color="<<iter->y<<iter->Color<<std::endl;
    }

    std::ofstream fd(fname, std::ios_base::out|std::ios_base::trunc); //выводим индексы и координаты вершин в файлик
    fd<<"#VertIndex; x; y; color"<<std::endl;
    for(iter=Vertices.begin();iter!=Vertices.end();iter++)
    {
        fd<< std::fixed <<std::setprecision(3)<<iter->VertIndex<< "\t"<<iter->x<<"\t"<<iter->y<<"\t"<<iter->Color<<std::endl;
    }
    fd.close();
}
void SetEdgesForPlot(std::vector<std::vector<edge>>& Edges, const char* fname="EdgesForPlot.dat")
{
//    std::vector<edgeForPlot> VecedgeForPlot;
    std::ofstream fd(fname);
    for(int i=0; i<Edges.size(); i++)
        for(int j=i; j<Edges.at(i).size(); j++) //просматриваем только верхний угл. Граф у нас неориентированный! Тут заполняется вектор с ребрами
        {
          //  edgeForPlot tempedgeForPlot;
            std::cout<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
            if(Edges.at(i).at(j).Adjacency==1)
            {
            //    Edges.at(i).at(j).VertIndex1=i;
            //    Edges.at(i).at(j).VertIndex2=j;
          //      Edges.at(i).at(j).Weight=WeightMatrix.at(i).at(j);
         //       tempedgeForPlot.OffsetX=0; //тут пока оставим так (0 значение). Тут ничего ставить не будем. Постараемся все "графические" величины указать в файле со скриптом.
            //    if(i==j) tempedgeForPlot.OffsetY=-3.5; //примерно на столько нужно сместить, чтобы не на петлях надписи не перекрывали номера узлов
             //   VecedgeForPlot.push_back(tempedgeForPlot);
                fd<<i<<"\t"<<j<<"\t"<<Edges.at(i).at(j).Weight<<"\t"<<Edges.at(i).at(j).Color<<std::endl;
            }
        }
    
/*    for(auto& Viter: VecedgeForPlot)
    {
        fd<<Viter.VertIndex1<<"\t"<<Viter.VertIndex2<<"\t"<<Viter.Weight<<"\t"<<Viter.color<<std::endl;
    }
    fd<<"#VertIndex1;VertIndex2;Weight;color"<<std::endl;*/
    fd.close();

/*    
    auto Witeri=WeightMatrix.begin();
    for(auto& Aiteri: AdjacencyMatrix)
    {
        auto Witerj=Witeri->begin();
        for(auto& Aiterj: Aiteri)
        {
            VecedgeForPlot
            Witerj++;
        }
        Witeri++;
    }
*/
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
void GenerateAdjacencyProb(std::vector<std::vector<edge>>& Edges, int seed, double probability) //генерируем матрицу смежности. probability -вероятность появления ребра
{
    //настраиваем генератор
    std::default_random_engine generator(seed);
    std::discrete_distribution<int> distribution {1-probability, probability}; //единички генерируются с вероятностью probability, а нолики с вероятностью 1-probability

    std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
    std::vector<int>::iterator iterj;
    for(int i=0; i<Edges.size(); i++)
    {
        for(int j=0; j<Edges.at(i).size();j++)
        {
            if(j>=i)
            {
                //int dice_roll = distribution(generator);
                Edges.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
            }
            else
            {
                Edges.at(i).at(j).Adjacency=Edges.at(i).at(j).Adjacency; //граф неориентированный
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

void GenerateAdjacencyMNumber(std::vector<std::vector<edge>>& Edges, int seed, int m) //генерируем матрицу смежности. m -число ребер в случайном графе
{

    //настраиваем генератор
    std::default_random_engine generator(seed);

    int n=(Edges.size()+1)*Edges.size()/2; //общее число случаев в классическом определении вероятности (пользуемся формулой арфиметической прогрессии для нахождения числа ячеек)
    //проверка на одз
    if(m>n)
    {
        std::string str;
        std::stringstream ss;
        ss << "m=" <<m<<" is too big! (max m=n="<<n<<")"<<std::endl;
        throw(ss.str());
    }

    std::vector<std::vector<int>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам)
    std::vector<int>::iterator iterj;
    for(int i=0; i<Edges.size(); i++)
    {
        for(int j=0; j<Edges.at(i).size();j++)
        {
            if(j>=i)
            {
                std::discrete_distribution<int> distribution {1-(double)m/n, (double)m/n}; //
                //int dice_roll = distribution(generator);
                Edges.at(i).at(j).Adjacency=distribution(generator); //генерируем ребро.
                if(Edges.at(i).at(j).Adjacency!=0) //пользуемся классическим определением вероятности
                {
                    m--;
                    n--;
                }
                else
                {
                    n--;
                }
            }
            else
            {
                Edges.at(i).at(j).Adjacency=Edges.at(j).at(i).Adjacency; //граф неориентированный
            }
        }
    }
}

void SetGraphInfo(std::vector<std::vector<edge>>& Edges, const char* filename) //число вершин и ребер в файл
{
    int m=0; //число ребер в графе
    for(int i=0; i<Edges.size(); i++)
        for(int j=i; j<Edges.at(i).size(); j++)
        {
            m+=Edges.at(i).at(j).Adjacency;
        }
    std::ofstream fd(filename);
  //  fd<<AdjacencyMatrix.size()<<"\t"<<m<<std::endl;
    fd<<"\"n="<<Edges.size()<<";m="<<m<< "\""<<std::endl;
    fd.close();
}
template<typename T>
void PrintMatrix(std::vector<std::vector<T>>& Matrix, const char* MatrixName)
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
template<typename T>
void PrintMatrixToFile(std::vector<std::vector<T>>& Matrix, const char* MatrixName, const char* filename)
{
    std::ofstream fd(filename);
    typename std::vector<std::vector<T>>::iterator iteri; //два итератора, для итерации по строкам и ячейкам(столбцам) .Без typename вообще не компилируется, хотя казалось бы.
    typename std::vector<T>::iterator iterj;
    for(iteri=Matrix.begin(); iteri!=Matrix.end(); iteri++)
    {
       // fd<< MatrixName<<"["<<std::distance(Matrix.begin(), iteri) <<"]=";
        for(iterj=iteri->begin(); iterj!=iteri->end(); iterj++)
        {
            fd<< (*iterj)<<"\t";
        }
        fd<<std::endl;
    }
    fd.close();
}

bool DFSConnectivityCheck(std::vector<std::vector<int>>& AdjacencyMatrix, std::vector<vertex>& vertices) //Проверка связности графа с помощью обхода в глубину
{
    return false;
}

/*

// visited — массив цветов вершин  
                             
int dfs(u: int, visited: bool[]):              
    int visitedVertices = 1
    visited[u] = true                           // помечаем вершину как пройденную
    for v: uv ∈ E                               // проходим по смежным с u вершинам
        if not visited[v]                       // проверяем, не находились ли мы ранее в выбранной вершине
            visitedVertices += dfs(v, visited)
    return visitedVertices

    */
//}

int main(int, char**) {
//    std::cout << "Hello, world!\n";
    int seed=time(0);
    //int seed=0; 

    int N=5;
    std::vector<vertex> Vertices(N);
    std::vector<std::vector<edge>> Edges(N);
 //   std::vector<std::vector<edge>>::iterator iteri;
 //   for(iteri=AdjacencyMatrix.begin(); iteri!=AdjacencyMatrix.end(); iteri++)
  //  {
 //       iteri->resize(N);
 //       std::cout<< "iteri->size()"<<iteri->size()<<std::endl;
 //   }
    for(auto& iter: Edges)
        iter.resize(N);

//    GenerateAdjacencyProb(Edges, seed, 0.5);
    try {GenerateAdjacencyMNumber(Edges, seed, 3);}
    catch(std::string str)
    {
        std::cout<<"exeption:"<<str<<std::endl;
        return -1;
    }

//    PrintMatrix<int>(AdjacencyMatrix, "AdjacencyMatrix");
//    PrintMatrixToFile(AdjacencyMatrix, "AdjacencyMatrix", "AdjacencyMatrixOut.txt");
    SetEdgesForPlot(Edges);
    SetVertXYForPlot(Vertices);
    SetGraphInfo(Edges, "GraphInfo.dat"); //число вершин и ребер в файл
    system("./PlotGraph.gpi");

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
