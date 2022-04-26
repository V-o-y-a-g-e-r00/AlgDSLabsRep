#ifndef MAZESEARCHALG_H
#define MAZESEARCHALG_H

#include "maze.h"
#include "presenthandler.h"
#include <vector>
#include <limits> //будем помечать максимальным возомжным значением непосещенные ячейки.
//Постараемся реализовать волновой алг и, может быть, его модификацию с двумя волнами. Так же есть идея немного его ускорить без какого-либо влияния на функциональность путем сокращения области поиска ячеек фронта на этапе распространения волны.
void Lee(maze& Maze, int starti, int startj, int finishi, int finishj, presenthandler& PrHandler)
{
    std::vector<std::vector<int>> CellDist(Maze.n); //В векторах нулевые значения в стандартных контейнерах будут зануленными. Смотри value-initialization и тому подобное.
    for(int i=0; i<CellDist.size(); i++) //Храним в этой матрице веса во время распространения волны.
    {
        CellDist.at(i).resize(Maze.m, std::numeric_limits<int>::max()); //Макс значением int помечаем ещё не пройденные ячейки.
    }
    int CurrentDist=0;
    CellDist.at(starti).at(startj)=CurrentDist; //не обязательно, у нас и так нули.
    //Распространяем волну, пока не попадем в точку назначения
    bool IsReachedfinish=false;
    bool IsChanged=true; //Проверяем, продвинулась ли волна хотя бы на одну ячейку. Если нет, то значит, что пути не существует.

    int mini=starti, maxi=starti, minj=startj, maxj=startj; //Для сужения области поиска ячеек фронта волны. Больше ни для чего не будем эти переменные использовать
    while((!IsReachedfinish)&&IsChanged) //одна итерация-одно продвижение фронта волны. Пока не дойдем до финишной ячейки или пока есть куда ходить
    {
        
        IsChanged=false;
        CurrentDist++;
        for(int i=mini; (i<=maxi)&&(!IsReachedfinish); i++) //Пробегаем все ячейки фронта волны
        {
            for(int j=minj; (j<=maxj)&&(!IsReachedfinish); j++)
            {
                if(CellDist.at(i).at(j)==CurrentDist-1) //Если данная ячейка - ячейка фронта волны
                {
                    for(int alpha=0; (alpha<4)&&(!IsReachedfinish); alpha++) //Пытаемся распространить волну на соседние ячейки 
                    {
                        if(!Maze.HasWall(i, j, alpha)) //Если нет стенки
                        {
                            int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
                            int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
                            if(CellDist.at(i+di).at(j+dj)==std::numeric_limits<int>::max()) //если волна ещё не проходила через эти ячейки. Можно ли объединить этот цикл с тем, в который он вложен, не ясно. Т.к. мы можем попадать в ячейки, которых не сущетсвует.
                            {
                                CellDist.at(i+di).at(j+dj)=CurrentDist;
                                //для сужения области поиска ячеек фронта волны на поле лабиринта
                                if(i+di<mini) mini=i+di;
                                if(i+di>maxi) maxi=i+di;
                                if(j+dj<minj) minj=j+dj;
                                if(j+dj>maxj) maxj=j+dj;
                                // /////
                                if((i+di==finishi)&&(j+dj==finishj)) //если волна дошла до финишной ячейки, то прекращаем распространение волны
                                {
                                    IsReachedfinish=true;
                                }
                                IsChanged=true;
                            }
                            
                        }
                    }
                }
            }
        }
        if(PrHandler.Mode==1) //Небольшие манипуляции, чтобы помочь отладить это.
        {
            for(int i=0; i<Maze.n; i++)
            {
                for(int j=0; j<Maze.m; j++)
                {
                    if(CellDist.at(i).at(j)==std::numeric_limits<int>::max())
                    {
                        Maze.SetCellValue(i, j, '~');
                    }
                    else
                    {
                        Maze.SetCellValue(i, j, (char)CellDist.at(i).at(j)+48); //Если CellDist будет иметь большие значения, то в char они не влезут. Но для отладки подойдет.
                    }
                }
            }
            Maze.ShowDecorate();
            std::cin.ignore();
        }
    }
    //Восстанавливаем путь.
}





#endif /* MAZESEARCHALG_H */
