#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define WALL '#'
#define NOWALL '?'
#define EMPTYCELL '.'
#define CORNER '+'

class maze
{
private:
    
    int n=0, m=0; //высота и ширина лабиринта
public:
    std::vector<std::vector<char>> BaseVector;
    maze()=default;
    maze(int Nn, int Nm): n(Nn), m(Nm)
    {
        BaseVector.resize(n*2+1);
        for(auto& i: BaseVector) i.resize(m*2+1);
        
        for(int i=0; i<BaseVector.size(); i+=2) //устанавливаем углы ячеек
            for(int j=0; j<BaseVector.at(i).size(); j+=2)
            {
                BaseVector.at(i).at(j)=CORNER;
            }
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                SetCellValue(i, j, EMPTYCELL);
                for(int alpha=0; alpha<4; alpha++)
                    SetCellWalls(i, j, alpha, true);
            }
    }
    void SetCellValue(int i, int j, char c)
    {
        BaseVector.at(i*2+1).at(j*2+1)=c;
    }
    void SetCellWalls(int i, int j, int alpha, bool HasWall)
    {
        int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
        int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
        (HasWall)? BaseVector.at(i*2+1+di).at(j*2+1+dj)=WALL : BaseVector.at(i*2+1+di).at(j*2+1+dj)=NOWALL;
    }
    void Show(char* filename=(char*)"cin")
    {
        std::stringstream ss;
        for(auto& i: BaseVector)
        {
            for(auto& j: i)
            {
                ss<<j;
            }
            ss<<std::endl;
        }
        std::cout<<ss.str();
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


}

int main(int, char**) {
    std::cout << "Hello, world!"<<(-1)%2<<std::endl;
    maze Maze(3,3);
    Maze.SetCellWalls(0,0,0,false);
    Maze.Show();
}
