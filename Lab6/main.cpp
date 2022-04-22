#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define WALL '#'
#define NOWALL '?'
#define EMPTYCELL '.'

class maze
{
private:
    std::vector<std::vector<char>> BaseVector;
public:
    maze(int n, int m)
    {
        BaseVector.resize(n);
        for(auto& i: BaseVector) i.resize(m);
        for(int i=0; i<BaseVector.size(); i++)
            for(int j=0; j<BaseVector.at(i).size(); j++)
            {
                SetCellValue(i, j, EMPTYCELL);
                
            }
    }
    void SetCellValue(int i, int j, char c)
    {
        BaseVector.at(i*2+1).at(j*2+1)=c;
    }
    void SetCellWalls(int i, int j, int di, int dj, bool HasWall)
    {
        (HasWall)? BaseVector.at(i*2+1+di).at(j*2+1+dj)=WALL : BaseVector.at(i*2+1+di).at(j*2+1+dj)=NOWALL;
    }
};
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

    {
        std::cout<<"MazeFromFile: bad read"<<std::endl;
        getchar();
    }
    ss<<str;
    ss>>
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
}
