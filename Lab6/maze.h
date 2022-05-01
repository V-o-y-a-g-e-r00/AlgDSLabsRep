#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <type_traits> //Будем сравнивать типы в шаблонном методе
#include <cassert>

#define WALL '#' //Стена присутствует
#define NOWALL '?' //Стена отсутствует (половина строк содержит только информацию о стенах)
#define EMPTYCELL '.' //Сама ячейка
#define CORNER '+' //Не несет смысла. Стоит по углам ячеек.

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
#define NOHORIZ " "

class maze
{
private:
public:
    int n=0, m=0; //высота и ширина лабиринта
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
    void ResetValues()
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                SetCellValue(i,j, EMPTYCELL);
            }
        }
    }
    char GetCellValue(int i, int j)
    {
        return BaseVector.at(i*2+1).at(j*2+1);
    }
    void SetValuesByStr(std::string str)
    {
        int k=0;
        for(int i=0; i<n && k<str.size(); i++)
        {
            for(int j=0; j<m && k<str.size(); j++)
            {
                if (str.at(k)!=' ') SetCellValue(i,j, str.at(k));
                k++;
            }
        }
    }
    void SetCellWalls(int i, int j, int alpha, bool HasWall, bool Protected=false) //alpha - угол, под которым находится радиус вектор, указывающий на данную стену из центра ячейки. (как в тригонометрии). Значения от 0 до 3. Protected защищать ли стены области. true - не позволять убирать стенки области лабиринта.
    {
        int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
        int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
        if(Protected)
        {
            if((i+di<n)&&(i+di>=0)&&(j+dj<m)&&(j+dj>=0)) //если смежная по этой стене ячейка находится внутри области лабиринта
            {
                (HasWall)? BaseVector.at(i*2+1+di).at(j*2+1+dj)=WALL : BaseVector.at(i*2+1+di).at(j*2+1+dj)=NOWALL;
            }
        }
        else
        {
            (HasWall)? BaseVector.at(i*2+1+di).at(j*2+1+dj)=WALL : BaseVector.at(i*2+1+di).at(j*2+1+dj)=NOWALL;
        }
    }
    //Если будем обращаться к несуществующим стенам (из несуществующих ячеек), то будем возвращать false, т.е. что такой стены нет. Это позволит пробегать все стены, итерируясь по несуществующим ячейкам
    bool HasWall(int i, int j, int alpha) //прикол в том, что мы можем узнать, существуют ли стены у ячейки, даже если самой ячейки не существует. Главное, чтобы сами стены сущестововали в лабиринте.
    {
        int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
        int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
        if((i*2+1+di>=0) && (i*2+1+di<n*2+1) && (j*2+1+dj>=0) && (j*2+1+dj<m*2+1)) //Лишние условные операторы программе производительности не прибавляют, но так будет легче выводит лабиринт в графическом виде. Другой способ - создание лишних ячеек по углам
        {
            if(BaseVector.at(i*2+1+di).at(j*2+1+dj)==WALL) return true;
            else return false;
        }
        else
        {
            return false;
        }
    }
    int GetNeighborI(int i, int alpha)
    {
        int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
        return i+di;
    }
    int GetNeighborJ(int j, int alpha)
    {
        int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
        return j+dj;
    }
    std::string Show(char* filename=(char*)"cin")
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
        return ss.str();
    }
    void CharFromWallFlags(std::stringstream& ss, std::string& WallFlags) //Вспомогательная функция для получения символа по флагу, т.е. по его описанию.
    {
        switch (std::stoi(WallFlags))
        {
        case 0:
            ss<<DOT;
            break;
        case 1:
            ss<<HORIZWALL;
            break;
        case 10:
            ss<<BOTTOMWALL;
            break;
        case 11:
            ss<<CORBL;
          //  std::cout<<"char:CORBL"<<std::endl;
            break;
        case 100:
            ss<<HORIZWALL;
            break;
        case 101:
            ss<<HORIZWALL;
            break;
        case 110:
            ss<<CORBR;
            break;
        case 111:
            ss<<BOTTOMWALL;
            break;
        case 1000:
            ss<<TOPWALL; //если ставить вертикальную черту, то может возникнуть ситуация, когда закроется проход
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
     //Сейчас попробуем переделать это, чтобы scale работал.
    void ShowDecorateOld(char* filename=(char*)"cout", int Mode=0, int Scale=1, bool IsWithValues=false) //Mode - 0 выводить внутреннее представление лабиринта и его декоративный вариант. 1 - только декоративный. Scale 1 и 2 возможные масштабы лабиринта. bool IsWithValues Для масштаба 2 можно вывести значения в ячейках
    {
        std::stringstream ss;
        std::string str;
    //    ss<<HORIZWALL<<VERTWALL<<CORTL<<CORTW<<CORBL<<CORBR<<TOPWALL<<BOTTOMWALL<<LWALL<<RWALL<<FULLWALL<< std::endl; //проверка отображения символов.
    //    std::cout<<ss.str();
        std::string WallFlags;

        WallFlags.clear();
        // Тут просто корректируем граничные условия
        if(HasWall(0,0, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
        WallFlags.insert(0,"0"); // наверх стены не продолжаются
        WallFlags.insert(0,"0");
        if(HasWall(0,0, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
        CharFromWallFlags(ss, WallFlags);
        

        for(int j=0;j<m-1;j++)
        {
            if(HasWall(0,0, 1)) ss<<HORIZWALL; else ss<<NOHORIZ;
            WallFlags.clear();
            if(HasWall(0,j+1, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            WallFlags.insert(0,"0"); // наверх стены не продолжаются
            if(HasWall(0,j, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            if(HasWall(0,j, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            CharFromWallFlags(ss, WallFlags);
        }

        if(HasWall(0,0, 1)) ss<<HORIZWALL; else ss<<NOHORIZ;
        WallFlags.clear();
        WallFlags.insert(0,"0"); // вправо и наверх стены не продолжаются
        WallFlags.insert(0,"0");
        if(HasWall(0,m-1, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
        if(HasWall(0,m-1, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
        CharFromWallFlags(ss, WallFlags);

        ss<<std::endl;
        // /////
        for(int i=0; i<n; i++)
        {
            // Тут просто корректируем граничные условия
            WallFlags.clear();
            if(HasWall(i,0, 3)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            if(HasWall(i,0, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            WallFlags.insert(0,"0"); //слева ячеек нет, и значит стен, уходящих влево тоже нет
            if(i+1<n) if(HasWall(i+1,0, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0"); 
            CharFromWallFlags(ss, WallFlags);
          //  std::cout<<"i="<<i<<" WallFlags="<<WallFlags<<" "<< std::stoi(WallFlags)<<" HasWall(i,0, 2)="<<HasWall(i,0, 2)<<CORBL<<std::endl;
            // /////   
            for(int j=0; j<m-1; j++)
            {
                if(HasWall(i,j, 3)) ss<<HORIZWALL; else ss<<NOHORIZ;
                WallFlags.clear();
                if(HasWall(i+1,j+1, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(HasWall(i,j, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(HasWall(i,j, 3)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(i+1<n) if(HasWall(i+1,j+1, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0"); else WallFlags.insert(0,"0");

                CharFromWallFlags(ss, WallFlags);
                
            }
            // Тут просто корректируем граничные условия
            if(HasWall(i,m-1, 3)) ss<<HORIZWALL; else ss<<NOHORIZ;
            WallFlags.clear();
            WallFlags.insert(0,"0"); //справа ячеек нет, и значит стен, уходящих вправо тоже нет
            if(HasWall(i,m-1, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            if(HasWall(i,m-1, 3)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
            if(i+1<n) if(HasWall(i+1,m-1, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0"); 
            CharFromWallFlags(ss, WallFlags);
            // /////
            ss<<std::endl;
        }
        if(filename==(char*)"cout") //пошел вывод в терминал или файл
        {
            switch(Mode)
            {
                case 0:
                {
                    std::stringstream ss1;
                    for(auto& i: BaseVector)
                    {
                        for(auto& j: i)
                        {
                            ss1<<j;
                        }
                        ss1<<std::endl;
                    }
                    std::cout<<ss1.str();
                    std::cout<<"------------"<<std::endl;
                    std::cout<<ss.str();
                }break;
                case 1:
                {
                    std::cout<<ss.str();
                }break;
            }
        }
        else
        {
            std::ofstream fout(filename);
            if(!fout.is_open())
            {
                std::stringstream ss;
                ss << "Can not open file:"<<filename<<std::endl;
                throw(ss.str());
            }
            switch(Mode)
            {
                case 0:
                {
                    std::stringstream ss1;
                    for(auto& i: BaseVector)
                    {
                        for(auto& j: i)
                        {
                            ss1<<j;
                        }
                        ss1<<std::endl;
                    }
                    fout<<ss1.str();
                    fout<<"------------"<<std::endl;
                    fout<<ss.str();
                }break;
                case 1:
                {
                    fout<<ss.str();
                }break;
                
            }
            fout.close();

        }
    }
    

    char GetCellValueFromStruct(int i, int j, const std::string& str, int member) //перегрузки. 
    {
        //
        if(str==std::string("GetCellValue"))
            return GetCellValue(i, j);
        assert(false);
        return -1;
    }
    int GetCellValueFromStruct(int i, int j, std::vector<std::vector<int>>& Weights, int member)
    {
        return Weights.at(i).at(j);
    }
    int GetCellValueFromStruct(int i, int j, std::vector<std::vector<std::pair<char, int>>> PathCoordWeights, int member) //member - какой член выбрать в PathCoordWeights
    {
        switch (member)
        {
        case 1:
            return PathCoordWeights.at(i).at(j).first;
            break;
        case 2:
            return PathCoordWeights.at(i).at(j).second % 1000;
            break;
        default:
            break;
        }
        assert(false);
        return -1;
    }
    template<typename T>
    std::string StrFromInt(T value)
    {
        std::stringstream ss1, ss2;
        ss1<<value;
        switch (ss1.str().length())
        {
        case 1:
            ss2<<NOHORIZ<<ss1.str()<<NOHORIZ;  
            break;
        case 2:
            ss2<<ss1.str()<<NOHORIZ;  
            break;
        case 3:
            ss2<<ss1.str();  
            break;        
        default:
            ss2<<NOHORIZ<<'?'<<NOHORIZ;
            break;
        }
        return ss2.str();
    }
    template <typename T=const std::string> //константные ссылки могут быть привязаны к временным объектам, причем время жизни объекта расширяется до времени жизни константной ссылки
    void ShowDecorate(char* filename=(char*)"cout", int Mode=0, int Scale=1, bool IsWithValues=false, T& Values=std::string("GetCellValue"), int member=0) //Mode - 0 выводить внутреннее представление лабиринта и его декоративный вариант. 1 - только декоративный. Scale 1 и 2 возможные масштабы лабиринта. bool IsWithValues Для масштаба 2 можно вывести значения в ячейках
    {
        std::stringstream ss;
        std::string str;
    //    ss<<HORIZWALL<<VERTWALL<<CORTL<<CORTW<<CORBL<<CORBR<<TOPWALL<<BOTTOMWALL<<LWALL<<RWALL<<FULLWALL<< std::endl; //проверка отображения символов.
    //    std::cout<<ss.str();
        std::string WallFlags;

        for(int i=0; i<n+1; i++)
        {

            for(int j=0; j<m+1; j++)
            {
                //рисуем левый вехний угл ячейки
                WallFlags.clear();
                if(HasWall(i,j, 1)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(HasWall(i-1,j-1, 0)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(HasWall(i-1,j-1, 3)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");
                if(HasWall(i,j, 2)) WallFlags.insert(0,"1"); else WallFlags.insert(0,"0");

                if(Scale==1)
                {
                    CharFromWallFlags(ss, WallFlags);
                    //рисуем верхнюю стену ячейки
                    if(HasWall(i,j, 1)) ss<<HORIZWALL; else ss<<NOHORIZ;
                }
                else if(Scale==2)
                {
                    CharFromWallFlags(ss, WallFlags);
                    //рисуем верхнюю стену ячейки
                    if(HasWall(i,j, 1)) ss<<HORIZWALL<<HORIZWALL<<HORIZWALL; else ss<<NOHORIZ<<NOHORIZ<<NOHORIZ;
                }
            }
            ss<<std::endl;
            if(Scale==2 && i!=n)
            {
                //рисуем левые стенки
                for(int j=0; j<m; j++)
                {
                    if(HasWall(i,j, 2)) ss<<VERTWALL; else ss<<NOHORIZ;
                //    if(IsWithValues) ss<<NOHORIZ<<GetCellValue(i, j)<<NOHORIZ;
                if(IsWithValues)
                {
                    ss<<StrFromInt(GetCellValueFromStruct(i,j, Values, member));
                //    std::cout<<"GetCellValueFromStruct(i,j, Values)="<<GetCellValueFromStruct(i,j, Values)<<std::endl;
                }
                else ss<<NOHORIZ<<NOHORIZ<<NOHORIZ;
                }
                //Граничные условия
                if(HasWall(i, m, 2)) ss<<VERTWALL; else ss<<NOHORIZ;
                ss<<std::endl;
            }
        }

        if(filename==(char*)"cout") //пошел вывод в терминал или файл
        {
            switch(Mode)
            {
                case 0:
                {
                    std::stringstream ss1;
                    for(auto& i: BaseVector)
                    {
                        for(auto& j: i)
                        {
                            ss1<<j;
                        }
                        ss1<<std::endl;
                    }
                    std::cout<<ss1.str();
                    std::cout<<"------------"<<std::endl;
                    std::cout<<ss.str();
                }break;
                case 1:
                {
                    std::cout<<ss.str();
                }break;
            }
        }
        else
        {
            std::ofstream fout(filename);
            if(!fout.is_open())
            {
                std::stringstream ss;
                ss << "Can not open file:"<<filename<<std::endl;
                throw(ss.str());
            }
            switch(Mode)
            {
                case 0:
                {
                    std::stringstream ss1;
                    for(auto& i: BaseVector)
                    {
                        for(auto& j: i)
                        {
                            ss1<<j;
                        }
                        ss1<<std::endl;
                    }
                    fout<<ss1.str();
                    fout<<"------------"<<std::endl;
                    fout<<ss.str();
                }break;
                case 1:
                {
                    fout<<ss.str();
                }break;
                
            }
            fout.close();

        }
    }
};

class mazeWeighted : public maze
{
public:
    std::vector<std::vector<int>> Weights;
    mazeWeighted()=default;
    mazeWeighted(int Nn, int Nm, int FillWeight=0): maze(Nn, Nm) //FillWeight заливка всего поля этим весом
    {
        Weights.resize(Nn); 
        for(auto& i : Weights)
        {
            i.resize(Nm, FillWeight); //Должны быть нулевые значения (если без второго аргумента). Это связано с реализацией вектора.
        }
    }
    void WeightsToValues() //Копирует веса в значения ячеек для удобного представления.
    {
        for(int i=0;i<Weights.size(); i++)
        {
            for (int j=0;j<Weights.at(i).size(); j++)
            {
                SetCellValue(i, j, Weights.at(i).at(j)+48);
            }
        }
    }
};


#endif /* MAZE_H */
