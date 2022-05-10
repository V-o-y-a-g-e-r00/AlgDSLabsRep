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
mazeWeighted MazeWeighted(initn, initm, 1);

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
    std::vector<std::pair<int,int>> Way;
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
        int ModeT, ScaleT, IsWithValuesT, IsWeightsOverlapped;
        cg.GetVal(std::string("ModeT"), ModeT);
        cg.GetVal(std::string("ScaleT"), ScaleT);
        cg.GetVal(std::string("IsWithValuesT"), IsWithValuesT);
        cg.GetVal(std::string("IsWeightsOverlapped"), IsWeightsOverlapped);

        if(!IsWeightsOverlapped) MazeWeighted.ShowDecorate((char*)"cout", ModeT, ScaleT, (bool)IsWithValuesT);
        else MazeWeighted.ShowDecorate((char*)"cout", ModeT, ScaleT, (bool)IsWithValuesT, MazeWeighted.Weights);

        std::cout<<"n="<<MazeWeighted.n<<" m="<<MazeWeighted.m<<std::endl;
        break;
    case 4: //Сброс/Создание нового лабиринта
        int n, m;
        cg.GetVal(std::string("n"), n);
        cg.GetVal(std::string("m"), m);
        MazeWeighted=mazeWeighted(n, m, 1);
        break;

    case 5: //Уилсон
        std::cout<<"CurrentSeed="<<CurrentSeed<<std::endl;
    //    std::cout<<"PrHandler.Mode="<<PrHandler.Mode<<std::endl;
        Wilson(MazeWeighted, generator, PrHandler);
        break;
    case 6: //Уилсон (модификация с последовательным выбором ячеек)
        std::cout<<"CurrentSeed="<<CurrentSeed<<std::endl;
    //    std::cout<<"PrHandler.Mode="<<PrHandler.Mode<<std::endl;
        WilsonSerial(MazeWeighted, generator, PrHandler);
        break;
    case 7: //Олдос-Бродер
        std::cout<<"CurrentSeed="<<CurrentSeed<<std::endl;
    //    std::cout<<"PrHandler.Mode="<<PrHandler.Mode<<std::endl;
        AldousBroder(MazeWeighted, generator, PrHandler);
        break;
    case 8: //Бинарное дерево
        std::cout<<"CurrentSeed="<<CurrentSeed<<std::endl;
    //  std::cout<<"PrHandler.Mode="<<PrHandler.Mode<<std::endl;
        int alpha;
        cg.GetVal(std::string("alpha"), alpha);
        BinaryTree(MazeWeighted, generator, PrHandler, alpha);
        break;
    case 9: //Проредить стены
        double ReduceProb;
        cg.GetVal("ReduceProb", ReduceProb);
        WallsReduce(MazeWeighted, ReduceProb, generator);
        break;
    case 10: //Генерация весов с помощью кругов
        int CircminWeight, CircmaxWeight, CircmeanRadius;
        double CircProb, Circstddev;
        cg.GetVal("CircminWeight", CircminWeight);
        cg.GetVal("CircmaxWeight", CircmaxWeight);
        cg.GetVal("CircmeanRadius", CircmeanRadius);

        cg.GetVal("CircProb", CircProb);
        cg.GetVal("Circstddev", Circstddev);

        RandomCircules(MazeWeighted, generator, CircminWeight, CircmaxWeight, CircProb, CircmeanRadius, Circstddev);
        break;
    case 11: //Ли
        int Leestarti, Leestartj, Leefinishi, Leefinishj;
        cg.GetVal(std::string("Leestarti"), Leestarti);
        cg.GetVal(std::string("Leestartj"), Leestartj);
        cg.GetVal(std::string("Leefinishi"), Leefinishi);
        cg.GetVal(std::string("Leefinishj"), Leefinishj);

        
        Lee(MazeWeighted, Leestarti, Leestartj, Leefinishi, Leefinishj, Way, PrHandler);
        PrintVector1(Way, "Way");
        break;
    case 12: //Ли (модификация с двумя волнами)
        int Lee2starti, Lee2startj, Lee2finishi, Lee2finishj;
        cg.GetVal(std::string("Lee2starti"), Lee2starti);
        cg.GetVal(std::string("Lee2startj"), Lee2startj);
        cg.GetVal(std::string("Lee2finishi"), Lee2finishi);
        cg.GetVal(std::string("Lee2finishj"), Lee2finishj);

        
        Lee2Waves(MazeWeighted, Lee2starti, Lee2startj, Lee2finishi, Lee2finishj, Way, PrHandler);
        PrintVector1(Way, "Way");        
        break;
    case 13: //Дейкстра
        int Dijstarti, Dijstartj, Dijfinishi, Dijfinishj;
        cg.GetVal(std::string("Dijstarti"), Dijstarti);
        cg.GetVal(std::string("Dijstartj"), Dijstartj);
        cg.GetVal(std::string("Dijfinishi"), Dijfinishi);
        cg.GetVal(std::string("Dijfinishj"), Dijfinishj);

        Dijkstra(MazeWeighted, Dijstarti, Dijstartj, Dijfinishi, Dijfinishj, Way, PrHandler);
        PrintVector1(Way, "Way");
        break;
    case 14: //AStar
        int AStarstarti, AStarstartj, AStarfinishi, AStarfinishj;
        cg.GetVal(std::string("AStarstarti"), AStarstarti);
        cg.GetVal(std::string("AStarstartj"), AStarstartj);
        cg.GetVal(std::string("AStarfinishi"), AStarfinishi);
        cg.GetVal(std::string("AStarfinishj"), AStarfinishj);

        AStar(MazeWeighted, AStarstarti, AStarstartj, AStarfinishi, AStarfinishj, Way, PrHandler);
        PrintVector1(Way, "Way");
        break;
    case 15: //Выход
        IsQuited=true;
        break;
    case 16: //Справка
        PrintFile((char*)"Help.txt");
        break;
    case 17: //Показать меню ещё раз
        PrintFile((char*)"Menu.txt");
        break;
    case 18: //Показать текущую конфигурацию
        cg.Print();
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
