#include <iostream>


#include "maze.h"
#include "Funcs.h"
#include "MazeGenerationAlgs.h"
#include <random>
#include "presenthandler.h"
#include "MazeSearchAlg.h"

int main(int, char**) {

std::cin.sync_with_stdio(false); //Синхронизируем с вводом stdio. Без этого не работает in_avail() Важно вызвать эту функцию до первого чтения или ввода. Иначе последсвия будут непредсказуемыми. Нужно для работы ValidInput()

PrintFile((char *)"Welcome.txt");
PrintFile((char *)"Menu.txt");


bool IsQuited=false;
int Choice=0;

//Читаем конфигурацию
Config cg;
try 
{
    cg.Read((char*)"Config.txt");
}
catch(const std::string e)
{
    std::cout << e << std::endl;
    std::cin.ignore();
    return -1;
}

//Инициализируем лабиринт
int initn, initm;
cg.GetVal(std::string("n"), initn);
cg.GetVal(std::string("m"), initm);
mazeWeighted MazeWeighted(initn, initm);

//Инициализируем генератор случайных чисел
int seed;
int CurrentSeed; //Со временем или по конфигурации
cg.GetVal(std::string("seed"), seed);

if(seed!=-1) CurrentSeed=seed;
else CurrentSeed=time(0);
std::default_random_engine generator(CurrentSeed);

presenthandler PrHandler;

while(!IsQuited)
{
    int Choice=ValidInput((char*)"пункт меню");
 //   std::cout<<"Выбран пункт меню="<<Choice<<std::endl;

    //Читаем конфигурацию после выбора пункта меню
    Config cg;
    try 
    {
        cg.Read((char*)"Config.txt");
    }
    catch(const std::string e)
    {
        std::cout << e << std::endl;
        std::cin.ignore();
        return -1;
    }
    //Измеряем некоторые величины
    int tempseed; //Сбрасываем генератор, если поменяли зерно
    cg.GetVal(std::string("seed"), tempseed);
    if(tempseed!=seed)
    {
        if(tempseed!=-1) CurrentSeed=tempseed;
        else CurrentSeed=time(0);
        generator=std::default_random_engine(CurrentSeed);
        seed=tempseed;
    }
    //Обновляем режим PrHandler
    int PrHandlerMode;
    cg.GetVal(std::string("PrHandlerMode"), PrHandlerMode);
    PrHandler.Mode=PrHandlerMode;

    //Выбранный пункт меню
    std::string strVal;
    bool IsFound=false;
    switch (Choice)
    {
    case 1: //Ввод лабиринта из файла
        IsFound=cg.GetVal(std::string("filenameFin"), strVal);
        if(!IsFound) std::cout<<"intVal does not exist! "<<std::endl; 
        try
        {
            MazeFromFile(MazeWeighted, (char *)strVal.c_str());
        }
        catch(const std::string e)
        {
            std::cout << e << '\n';
        }
        
       
        break;
    case 2: //Вывод лабиринта в файл
        int ModeF, ScaleF, IsWithValuesF;
        cg.GetVal(std::string("filenameFout"), strVal);
        cg.GetVal(std::string("ModeF"), ModeF);
        cg.GetVal(std::string("ScaleF"), ScaleF);
        cg.GetVal(std::string("IsWithValuesF"), IsWithValuesF);
        MazeWeighted.ShowDecorate((char*)strVal.c_str(), ModeF, ScaleF, (bool)IsWithValuesF);
        break;
    case 3: //Вывод лабиринта в терминал
        int ModeT, ScaleT, IsWithValuesT;
        cg.GetVal(std::string("ModeT"), ModeT);
        cg.GetVal(std::string("ScaleT"), ScaleT);
        cg.GetVal(std::string("IsWithValuesT"), IsWithValuesT);
        MazeWeighted.ShowDecorate((char*)"cout", ModeT, ScaleT, (bool)IsWithValuesT);
        std::cout<<"n="<<MazeWeighted.n<<" m="<<MazeWeighted.m<<std::endl;
        break;
    case 4: //Сброс/Создание нового лабиринта
        int n, m;
        cg.GetVal(std::string("n"), n);
        cg.GetVal(std::string("m"), m);
        MazeWeighted=mazeWeighted(n, m);
        break;

    case 5: //Уилсон
    //    std::cout<<"seed="<<seed<<std::endl;
    //    std::cout<<"PrHandler.Mode="<<PrHandler.Mode<<std::endl;
        Wilson(MazeWeighted, generator, PrHandler);
        break;
    case 6: //Уилсон (модификация с последовательным выбором ячеек)
        
        break;
    case 7: //Олдос-Бродер
        
        break;
    case 8: //Бинарное дерево
        
        break;
    case 9: //Ли
        
        break;
    case 10: //Ли (модификация с двумя волнами)
        
        break;
    case 11: //Дейкстра
        
        break;
    case 12: //AStar
        
        break;
    case 13: //Выход
        IsQuited=true;
        break;
    case 14: //Справка
        PrintFile((char*)"Help.txt");
        break;
    case 15: //Показать меню ещё раз
        PrintFile((char*)"Menu.txt");
        break;
    default:
        std::cout<<"Нет такого пункта меню"<<std::endl;
        break;
    }
}


/*


std::cin.clear();
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
std::cin.ignore(std::cin.rdbuf()->in_avail()-1);


std::cout<<"Ввод:"<<std::endl;
std::cin>>str;
std::cout<<"str="<<str<<std::endl;
std::cout<<"std::cin.rdbuf()->in_avail()="<<std::cin.rdbuf()->in_avail()<<std::endl;
*/
return 0;
}
