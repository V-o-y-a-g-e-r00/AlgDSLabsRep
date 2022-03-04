#ifndef VISUAL_H_INCLUDED
#define VISUAL_H_INCLUDED
//Тут будет все, что относится к отображению
#include "vertices.h"
#include "edges.h"



void SetVarsForScript(edges& Edges, bool IsOriented, bool IsWithVerticesWeights, bool IsSavePictureToFile, std::string PictureName,const char* filename) //Эти величины будет читать bash скрипт. Edges, чтобы мы могли вывести число вершин и ребер 
{
    int m=0; //число ребер в графе
    for(int i=0; i<Edges.Vector.size(); i++)
        for(int j=i; j<Edges.Vector.at(i).size(); j++)
        {
            m+=Edges.Vector.at(i).at(j).Adjacency;
        }
    std::ofstream fd(filename);
    fd<<"#nmtitle IsOriented IsSavePictureToFile PictureName IsWithVerticesWeights"<<std::endl;
    fd<<"\"n="<<Edges.Vector.size()<<"; m="<<m<< "\"\t"<<IsOriented<<"\t"<<IsSavePictureToFile<<"\t"<<PictureName<<"\t"<<IsWithVerticesWeights<<std::endl;
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
    std::cout<<"----------"<<std::endl;
} 
/*template<typename T>
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
}*/
void ShowPlot(vertices& Vertices, edges& Edges, bool IsWithVerticesWeights, bool IsSavePictureToFile, std::string PictureName) //PictureName без расширения
{
    Vertices.SetVertXYForPlot();
    Vertices.PrintVertices("Vertices.dat");
    Edges.SetEdgesForPlot(); //Вывод в файл для рисования графа 
    Edges.PrintEdges("Edges.txt"); //вывод информации о ребрах для наглядности. Не используется для рисования графа

    SetVarsForScript(Edges, false, IsWithVerticesWeights, IsSavePictureToFile, PictureName, "VarsForScript.dat"); //число вершин и ребер в файл
    system("./PlotGraph.bash");
}


#endif //VISUAL_H_INCLUDED