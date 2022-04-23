#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "maze.h"
#include "MazeGenerationAlgs.h"


void MazeFromFile(maze& Maze, char* filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) //проверка на успешность открытия файла
    {
        std::stringstream ss;
        ss << "Can not open file:"<<filename<<std::endl;
        throw(ss.str());
    }
    std::string str;
    std::stringstream ss;
    int n=0, m=0; //определяем размеры лабиринта
    while(std::getline(fin, str)) n++;
    if (n%2==0)
    {
        std::cout<<"MazeFromFile: bad n: n%2==0"<<std::endl;
        getchar();
    }
    n=(n-1)/2;
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
    std::getline(fin, str);
    m=str.length();
    if (m%2==0)
    {
        std::cout<<"MazeFromFile: bad m: m%2==0"<<std::endl;
        getchar();
    }
    m=(m-1)/2;
    Maze=maze(n,m);
    fin.clear();
    fin.seekg(0, std::ios_base::beg);
    for(int i=0; i<n*2+1; i++)
    {
       std::getline(fin, str);
       for(int j=0; j<m*2+1; j++)
       {
           Maze.BaseVector.at(i).at(j)=str.at(j);
       }
    }
    fin.close();

}



#endif /* FUNCS_H */
