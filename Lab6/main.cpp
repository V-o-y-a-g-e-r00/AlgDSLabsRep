#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define WALL '#'
#define NOWALL '?'
#define EMPTYCELL '.'
#define CORNER '+'

#define HORIZWALL "\u2500" // '-'
#define VERTWALL "\u2502" // '|'

#define CORTL "\u250C" // 'Г'
#define CORTR "\u2510" // '~.'
#define CORBL "\u2514" // 'L'
#define CORBR "\u2518" // '_|'

#define TOPWALL "\u252C" // '~.Г'
#define BOTTOMWALL "\u2534" // '_L'
#define LWALL "\u251C" // '|-'
#define RWALL "\u2524" // '-|'

#define FULLWALL "\u253C" // '-|-'
#define DOT "." //для случаев, когда нет всех четырех стен

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
    bool HasWall(int i, int j, int alpha) //прикол в том, что мы можем узнать, существуют ли стены у ячейки, даже если самой ячейки не существует. Главное, чтобы сами стены сущестововали в лабиринте.
    {
        int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
        int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
        if(BaseVector.at(i*2+1+di).at(j*2+1+dj)==WALL) return true;
        else return false;
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
    void CharFromWallFlags(std::stringstream& ss, std::string& WallFlags) //Вспомогательная функция для получения символа по флагу, т.е. по его описанию.
    {
        switch (std::stoi(WallFlags))
        {
        case 0000:
            ss<<DOT;
            break;
        case 0001:
            ss<<HORIZWALL;
            break;
        case 0010:
            ss<<VERTWALL;
            break;
        case 0011:
            ss<<CORBL;
            break;
        case 0100:
            ss<<HORIZWALL;
            break;
        case 0101:
            ss<<HORIZWALL;
            break;
        case 0110:
            ss<<CORBR;
            break;
        case 0111:
            ss<<BOTTOMWALL;
            break;
        case 1000:
            ss<<VERTWALL;
            break;
        case 1001:
            ss<<CORTL;
            break;
        case 1010:
            ss<<VERTWALL;
            break;
        case 1011:
            ss<<LWALL;
            break;
        case 1100:
            ss<<CORTR;
            break;
        case 1101:
            ss<<TOPWALL;
            break;
        case 1110:
            ss<<RWALL;
            break;
        case 1111:
            ss<<FULLWALL;
            break;
        default:
            break;
        }
    }
    void ShowDecorate(char* filename=(char*)"cin")
    {
        std::stringstream ss;
        std::string str;
    //    ss<<HORIZWALL<<VERTWALL<<CORTL<<CORTW<<CORBL<<CORBR<<TOPWALL<<BOTTOMWALL<<LWALL<<RWALL<<FULLWALL<< std::endl; //проверка отображения символов.
    //    std::cout<<ss.str();
        std::string WallFlags;


        for(int i=0; i<n; i++)
        {
            // Тут просто корректируем граничные условия
            WallFlags.clear();
            if(HasWall(i,0, 3)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            if(HasWall(i,0, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            WallFlags.insert(0,"0"); //слева ячеек нет, и значит стен, уходящих влево тоже нет
            if(i+1<n) if(HasWall(i+1,0, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0"); 
            CharFromWallFlags(ss, WallFlags);
            // /////   
            for(int j=0; j<m; j++)
            {
                ss<<HORIZWALL;
                WallFlags.clear();
                if ((i+1<n)&&(j+1<m)) if(HasWall(i+1,j+1, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0"); else WallFlags.insert(0,"1");
                if(HasWall(i,j, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(HasWall(i,j, 3)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if ((i+1<n)&&(j+1<m)) if(HasWall(i+1,j+1, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0"); else WallFlags.insert(0,"1");

                CharFromWallFlags(ss, WallFlags);
                
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
  //  std::string str = "\u256C\u265E";
// std::cout << str << std::endl;
    std::cout << "------------" << std::endl;
    Maze.ShowDecorate();
}
