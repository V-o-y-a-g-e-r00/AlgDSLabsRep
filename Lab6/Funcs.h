#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "maze.h"
#include "MazeGenerationAlgs.h"
#include <iomanip>


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
//Print будем перегружать для разных случаев
void Print(std::pair<int,int> Pair);
void Print(std::pair<int, std::pair<int, int>> Item);
void Print(std::pair<std::string, int> Item);
void Print(std::pair<std::string, std::string> Item);
template<typename T>
void PrintVector(std::vector<T>& Vector, const char* VectorName)
{
    typename std::vector<T>::iterator iteri=Vector.begin();
        std::cout<< VectorName<<"="<<std::endl;
        for(iteri=Vector.begin(); iteri!=Vector.end(); iteri++)
        {
      //      std::cout<<std::setw(3);
        //    std::cout<< (*iteri)<<"\t";
        //    std::cout<< (*iteri);
            Print(*iteri);
        }
    //    std::cout<<std::endl;
//    std::cout<<"----------"<<std::endl;
}
void Print(std::pair<int,int> Pair)
{
    std::cout<<"("<<Pair.first<<", "<<Pair.second<<")";
}
void Print(std::pair<int, std::pair<int, int>> Item)
{
    std::cout<<"("<<Item.first<<", ("<<Item.second.first<<", "<<Item.second.second<<"))";
}
void Print(std::pair<std::string, int> Item)
{
    std::cout<<Item.first<<"="<<Item.second<<std::endl;
}
void Print(std::pair<std::string, std::string> Item)
{
    std::cout<<Item.first<<"="<<Item.second<<std::endl;
}

//
void PrintFile(char* filename)
{
    std::ifstream fin(filename);
    if(!fin.is_open()) //проверка на успешность открытия файла
    {
        std::stringstream ss;
        ss << "Can not open file:"<<filename<<std::endl;
        throw(ss.str());
    }
    std::string str;
    while(std::getline(fin, str))
    {
        std::cout<<str<<std::endl;
    }
}

//Функция ввода целых чисел из потока, основанная на cin. Целые числа могут быть окружены whitespace -ами, но строка из череды чисел будет отклонена.
int ValidInput(char * name=(char*)"")
{
    std::string str;
    bool IsGood=false;
    while(!IsGood)
    {
        //Вводим используя стандартный поток ввода. (мерзкая штука)
        std::cin.clear(); //Очищаем флаги
        std::cin.ignore(std::cin.rdbuf()->in_avail()-1); //Пропускаем все символы в буфере. in_avail() возвращает число символов+1 . В EOF мы здесь упереться не можем, между прочим (только если Ctrl+D нажмем).

        std::cout<<"Введите "<<name<<":";
        std::cin>>str;
    //    std::cout<<"str="<<str<<std::endl;

        IsGood=true;
        //Проверяем на недопустимые симоволы
        if(str.find_first_not_of("0123456789")!=std::string::npos)
        {
            IsGood=false;
        }
        //Проверяем на лишние символы в потоке
            
    //    std::cout<<"before isspace"<<std::endl;
        while(std::isspace(std::cin.peek()) && std::cin.rdbuf()->in_avail()-1!=0) std::cin.ignore(1); //отбрасываем whitespace -ы
    //    std::cout<<"after isspace"<<std::endl;
        if(std::cin.rdbuf()->in_avail()-1!=0)
        {
            IsGood=false;
        }
        if(!IsGood) std::cout<<"Ввод неверный! ";
    }
    return std::stoi(str);
}
class Config
{
public:
    std::vector<std::pair<std::string, int>> intBase;
    std::vector<std::pair<std::string, std::string>> strBase;

    Config()=default;
    bool getstr(std::ifstream& fin, std::string& str) //Пытается прочесть строку, пропустив комментарии и пустые строки. Если это невозомжно, то возвращает false, при этом возвращает в строке что удалось прочесть.
    {
        bool IsSatisf=false; //fasle строку нужно пропустить. Т.е. не пускать её в данные.
        do{
            
            if(std::getline(fin, str)) //чтение прошло успешно //getline возвращает указатель потока. Указатель потока при перегрузке в bool в "хорошем" состоянии перегружается в true в "плохом" в false. Т.е. если чтение было удачным, то вернется true
            {
                if(str=="")
                {
                    std::cout<<"getstr: Unexpected empty string in file. Do you sure about your array size in file? The data will be read anyway"<<std::endl;
                    IsSatisf=false;
                }
                else if(str.at(0)=='#')
                {
                    IsSatisf=false;
                }
                else IsSatisf=true;
            }
    //    std::cout<<"fin.good()="<<fin.good()<<"!IsSatisf="<<!IsSatisf<<std::endl;
        }while(fin.good() && !IsSatisf);
        if(!fin.good()&&!IsSatisf)
        {
            if(fin.eof())
            {
            //    std::cout<<"getstr: Unexpected end of file. Do you sure about your array size in file? The data will be read anyway"<<std::endl; //Полезно, если мы заранее знаем число строк, но что-то пошло не так
            }
            else
            {
                std::cout<<"getstr: Unexpected error"<<std::endl;
            }
            return false; //выходим из итеративного цикла
        }
    //    std::cout<<"str="<<str<<std::endl;
        return true;
    }
 /*   template<typename ...args>
    void divstr(std::string& str, args&... Args)
    {
        const std::size_t count = sizeof...(args);
        for(auto& p: {Args...})
        {
            p=5;
            std::cout << p << std::endl;
        }
    }
*/
/*    void getstrItem(std::ifstream fin)
    {

    }*/
    void Read(char* filename)
    {
        //Открываем файл
        std::ifstream fin(filename);
        if(!fin.is_open()) //проверка на успешность открытия файла
        {
            std::stringstream ss;
            ss << "Can not open file:"<<filename<<std::endl;
            throw(ss.str());
        }
        //Читаем построчно с учетом комментариев
        std::string str, Var, Val;
        std::stringstream ss, ss2;
        
        while(getstr(fin, str))
        {
            ss.clear();
            ss<<str;
            std::getline(ss, Var, '=');
            std::getline(ss, Val, '=');
            if(Val.find_first_not_of("0123456789-.")!=std::string::npos) //Если нашли не числовой символ
            {
                strBase.push_back(std::make_pair(Var,Val));
            }
            else
            {
                intBase.push_back(std::make_pair(Var,std::stoi(Val)));
            }
        }
    }
    void Print()
    {
        PrintVector(intBase, (char*) "intBase");
        PrintVector(strBase, (char*) "strBase");
    }
};

#endif /* FUNCS_H */
