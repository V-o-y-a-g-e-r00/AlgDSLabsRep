#ifndef MAZEGENERATIONALGS_H
#define MAZEGENERATIONALGS_H

#include "maze.h"
#include "random"

#define VISITED '1'

void AldousBroder(maze& Maze, std::default_random_engine& generator)
{
    std::uniform_int_distribution<int> DistrI(0, Maze.n-1);
    std::uniform_int_distribution<int> DistrJ(0,Maze.m-1);
    std::uniform_int_distribution<int> Distrdidj(0,3);
    int randI=DistrI(generator);
    int randJ=DistrJ(generator);

    Maze.SetCellValue(randI, randJ, VISITED);
    int k=1;
    int di=0, dj=0;
    bool IsSatisfying=true; //когда у стены некотрые случайные значения не подходят
    int randcase=0;
    while(k!=Maze.n*Maze.m)
    {
        randcase=Distrdidj(generator);
        switch (randcase)
        {
        case 0:
            if(randJ<Maze.m-1)
            {
                di=0;
                dj=1;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;
        case 1:
            if(randI>0)
            {
                di=-1;
                dj=0;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;
        case 2:
            if(randJ>0)
            {
                di=0;
                dj=-1;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;
        case 3:
            if(randI<Maze.n-1)
            {
                di=1;
                dj=0;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;        
        
        default:
            break;
        }
        if(IsSatisfying) //если не уперлись в стену
        {
            if(Maze.GetCellValue(randI+di, randJ+dj)!=VISITED)
            {
                Maze.SetCellWalls(randI, randJ, randcase, false);
                randI+=di;
                randJ+=dj;
                Maze.SetCellValue(randI, randJ, VISITED);    
                k++;
            }
            else
            {
                randI+=di;
                randJ+=dj;
            }
        }
    }

}


#endif /* MAZEGENERATIONALGS_H */
