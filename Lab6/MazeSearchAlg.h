#ifndef MAZESEARCHALG_H
#define MAZESEARCHALG_H

#include "maze.h"
#include "presenthandler.h"
#include <vector>
#include <utility> //pair
#include <limits> //будем помечать максимальным возможным значением непосещенные ячейки.

#include <queue>
#include "Funcs.h"
#include <cmath>
#define NOTVISITED '~'


void DebugHandler(maze& Maze, std::vector<std::vector<std::pair<char, int>>>& CellDist, presenthandler& PrHandler); //Небольшие манипуляции, чтобы помочь отладить это.

//Постараемся реализовать волновой алг и, может быть, его модификацию с двумя волнами. Так же есть идея немного его ускорить без какого-либо влияния на функциональность путем сокращения области поиска ячеек фронта на этапе распространения волны. Алг не зависит от значений в ячейках.
void Lee(maze& Maze, int starti, int startj, int finishi, int finishj, std::vector<std::pair<int,int>>& Way, presenthandler& PrHandler)
{
    std::vector<std::vector<int>> CellDist(Maze.n); //В векторах нулевые значения в стандартных контейнерах будут зануленными. Смотри value-initialization и тому подобное.
    for(int i=0; i<CellDist.size(); i++) //Храним в этой матрице веса во время распространения волны.
    {
        CellDist.at(i).resize(Maze.m, std::numeric_limits<int>::max()); //Макс значением int помечаем ещё не пройденные ячейки.
    }
    int CurrentDist=0;
    bool IsReachedfinish=false;
    //Распространяем волну, пока не попадем в точку назначения
    CellDist.at(starti).at(startj)=CurrentDist;
    if((starti==finishi)&&(startj==finishj)) IsReachedfinish=true;
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
        if(PrHandler.Mode==2) //Небольшие манипуляции, чтобы помочь отладить это.
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
            Maze.ShowDecorate((char*)"cout", 1, 2, true);
            std::cin.ignore();
        }
    }
    //Проверяем существование пути и восстанавливаем путь.
    if(!IsReachedfinish)
    {
        std::cout<<"The way between starti="<<starti<<" startj="<<startj<<" and finishi="<<finishi<<" finishj="<<finishj<<" does not exist!"<<std::endl; //you do not know de wey
        return;
    }
    //пока не дойдем до начала
    int Currenti=finishi, Currentj=finishj;
    Way.clear();
    Way.insert(Way.begin(),std::make_pair(Currenti, Currentj));
    while(!((Currenti==starti)&&(Currentj==startj)))
    {
        for(int alpha=0; alpha<4;alpha++)
        {
            int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
            int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
            if(!Maze.HasWall(Currenti,Currentj, alpha)) //Если нет стены
            {
                if(CellDist.at(Currenti+di).at(Currentj+dj)==CellDist.at(Currenti).at(Currentj)-1)
                {
                    Way.insert(Way.begin(), std::make_pair(Currenti+di, Currentj+dj));
                    Currenti+=di;
                    Currentj+=dj;
                    break;
                }
            }
        }
    }
}

//Модификация алг Ли с 2 волнами (от стартовой и финишной точек)
//Итерацию движения фронта нужно выделить в отдельную функцию. Фронты будут двигаться поочередно, пока не встретятся друг с другом. При встрече фронтов в ячейку, в которой они пересекутся, поместим наибольший вес из весов, которые соответствуют первой и второй волне.
//Возвращает 2 значения: пересеклись ли волны и не застряла ли волна.
inline void WaveFrontIteration(maze& Maze, std::vector<std::vector<std::pair<char, int>>>& CellDist, int CurrentDist, int& mini, int& maxi, int& minj, int& maxj, bool& IsReachedfinish, bool& IsChanged, char WaveID, int& Interseci, int& Intersecj)
{
    IsChanged=false; //если застряла хотя бы одна волна, то поиск можно прекращать.
    for(int i=mini; (i<=maxi)&&(!IsReachedfinish); i++) //Пробегаем все ячейки фронта волны
    {
        for(int j=minj; (j<=maxj)&&(!IsReachedfinish); j++)
        {
            if((CellDist.at(i).at(j).second==CurrentDist-1)&&(CellDist.at(i).at(j).first==WaveID)) //Если данная ячейка - ячейка фронта волны
            {
                for(int alpha=0; (alpha<4)&&(!IsReachedfinish); alpha++) //Пытаемся распространить волну на соседние ячейки 
                {
                    if(!Maze.HasWall(i, j, alpha)) //Если нет стенки
                    {
                        int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
                        int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
                        if(CellDist.at(i+di).at(j+dj).first!=WaveID) //если волна ещё не проходила через эти ячейки. Т.е. в эту ячейку можно распространить волну. Можно ли объединить этот цикл с тем, в который он вложен, не ясно. Т.к. мы можем попадать в ячейки, которых не сущетсвует.
                        {
                            if(CellDist.at(i+di).at(j+dj).first!=0) //если волна дошла до пересечения с другой волной, то прекращаем распространение волны. За 0 обозначим ячейки, по которым не прошла ни одна волна
                            {
                                IsReachedfinish=true;
                                Interseci=i+di;
                                Intersecj=j+dj;
                                CellDist.at(i+di).at(j+dj).second=std::max(CurrentDist, CellDist.at(i+di).at(j+dj).second); //Для определенности назначим ячейке пересечения наибольший вес
                            }
                            else
                            {
                                CellDist.at(i+di).at(j+dj).second=CurrentDist;
                                CellDist.at(i+di).at(j+dj).first=WaveID;
                            }
                            //для сужения области поиска ячеек фронта волны на поле лабиринта
                            if(i+di<mini) mini=i+di;
                            if(i+di>maxi) maxi=i+di;
                            if(j+dj<minj) minj=j+dj;
                            if(j+dj>maxj) maxj=j+dj;
                            // /////

                            IsChanged=true;
                        }
                        
                    }
                }
            }
        }
    }
}
//Инициализация волны. Отмечает ячейку, из которой распространяется волна. Если ячейка была посещена другой волной, то выставляет флаг IsReachedfinish. Присваивает начальные значения min/max/i/j для сужения области поиска ячеек фронта волны
inline void WaveFrontInit(maze& Maze, std::vector<std::vector<std::pair<char, int>>>& CellDist, int CurrentDist, int& mini, int& maxi, int& minj, int& maxj, bool& IsReachedfinish, char WaveID, int& Interseci, int& Intersecj, int Initi, int Initj)
{
    if(CellDist.at(Initi).at(Initj).first!=0) //Если встретились с другой волной. Т.е. случай, когда начальная и конечная ячейки сопадают
    {
        IsReachedfinish=true;
        Interseci=Initi;
        Intersecj=Initj;
        CellDist.at(Initi).at(Initj).second=std::max(CurrentDist, CellDist.at(Initi).at(Initj).second); //Для определенности назначим ячейке пересечения наибольший вес
    }
    else
    {
        CellDist.at(Initi).at(Initj).second=CurrentDist;
        CellDist.at(Initi).at(Initj).first=WaveID;
    }
    mini=Initi;
    maxi=Initi;
    minj=Initj;
    maxj=Initj;
}
inline void ReconstructWay(maze& Maze, std::vector<std::vector<std::pair<char, int>>>& CellDist, char WaveID, int Interseci, int Intersecj, int Initi, int Initj, std::vector<std::pair<int, int>>& Way, bool Direction) //Восстановение пути после пересечения волн. WaveID-по какой волне идем; Interseci, Intersecj точка пересечения волн. int Initi, int Initj точка инициации волны; bool Direction - направление построение пути (false - начало пути true - конец пути).
{
    int Currenti=Interseci, Currentj=Intersecj;
    while(!((Currenti==Initi)&&(Currentj==Initj)))
    {
        if((Currenti==Interseci)&&(Currentj==Intersecj)) //Такой поиск предыдущей ячейки в пути нужен только для ячейки пересечения. Для остальных ячеек поиск будет аналогичным поиску в немодифицированном алг Ли.
        {
            //Ищем соседа с минимальным весом из всех соседей для данной WaveID.
            int MinNeighbor=0;
            int minalpha=0; //Альфа, указывающая на минимального соседа.
            int Cutalpha=0; //Чуть чуть ускорим алг. Помимо поиска первого соседа, из которого могла быть распространена волна, мы ищем соответствующую ему альфу, чтобы вдальнейшем не перебирать варианты, в которых заведомо нет соседей.
            for(int alpha=0; alpha<4;alpha++) //Ищем первого попавшегося соседа, принадлежащего данной волне.
            {
                int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
                int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
                if(!Maze.HasWall(Currenti,Currentj, alpha)) //Если нет стены
                {
                    if(CellDist.at(Currenti+di).at(Currentj+dj).first==WaveID) //Если ячейка принадлежит волне WaveID
                    {
                        MinNeighbor=CellDist.at(Currenti+di).at(Currentj+dj).second;
                        Cutalpha=alpha; //альфа, при которой мы нашли первого встретившегося соседа, принадлежащего данной волне.
                        minalpha=alpha;
                        break;
                    }
                }
            }
        //    std::cout<<"minalpha="<<minalpha<<std::endl;
            
            for(int alpha=Cutalpha+1; alpha<4;alpha++) //ищем минимального соседа из всех соседей, принадлежащих данной волне.
            {
                int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
                int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
                if(!Maze.HasWall(Currenti,Currentj, alpha)) //Если нет стены
                {
                    if((CellDist.at(Currenti+di).at(Currentj+dj).first==WaveID)&&(CellDist.at(Currenti+di).at(Currentj+dj).second<MinNeighbor))
                    {
                        MinNeighbor=CellDist.at(Currenti+di).at(Currentj+dj).second;
                        minalpha=alpha;
                    }
                }
            }
            //Добавляем минимального соседа, принадлежащего данной волне, в путь, и переходим к нему.
            int di=(minalpha%2)*((minalpha%4)*(minalpha%2)-2); //формулы получены из графиков
            int dj=((minalpha-1)%2)*(((minalpha-1)%4)*((minalpha-1)%2)-2);

            if(Direction) //Для конечного участка пути
            {
                Way.push_back(std::make_pair(Currenti+di, Currentj+dj));
            }
            else //Для начального участка пути
            {
                Way.insert(Way.begin(), std::make_pair(Currenti+di, Currentj+dj));
            }
            Currenti+=di;
            Currentj+=dj;
        }
        else
        {
            for(int alpha=0; alpha<4;alpha++)
            {
                int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
                int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
                if(!Maze.HasWall(Currenti,Currentj, alpha)) //Если нет стены
                {
                    if((CellDist.at(Currenti+di).at(Currentj+dj).first==WaveID)&&(CellDist.at(Currenti+di).at(Currentj+dj).second==CellDist.at(Currenti).at(Currentj).second-1))
                    {
                        if(Direction) //Для конечного участка пути
                        {
                            Way.push_back(std::make_pair(Currenti+di, Currentj+dj));
                        }
                        else //Для начального участка пути
                        {
                            Way.insert(Way.begin(), std::make_pair(Currenti+di, Currentj+dj));
                        }
                        Currenti+=di;
                        Currentj+=dj;
                        break;
                    }
                }
            }
        }
    }
}
	
void Lee2Waves(maze& Maze, int starti, int startj, int finishi, int finishj, std::vector<std::pair<int,int>>& Way, presenthandler& PrHandler)
{
    //Содзаем контейнер, в котором будем индекс волны, прошедшей через ячейки и веса ячеек при движении этой волны. Поле внутри Maze для хранения состояния ячейки не будем использоать в этом алгоритма, дабы избежать путаницы. Оно будет использоваться только для наглядного представления при отладке.
    std::vector<std::vector<std::pair<char, int>>> CellDist(Maze.n); //В векторах нулевые значения в стандартных контейнерах будут зануленными. Смотри value-initialization и тому подобное.
    for(int i=0; i<CellDist.size(); i++) //Храним в этой матрице веса во время распространения волны.
    {
        CellDist.at(i).resize(Maze.m, std::make_pair(0, std::numeric_limits<int>::max())); //Макс значением int помечаем ещё не пройденные ячейки.
    }
    int CurrentDist=0;
    bool IsReachedfinish=false;
    bool IsChanged=true; //Проверяем, продвинулась ли волна хотя бы на одну ячейку. Если нет, то значит, что пути не существует.
    int Interseci=std::numeric_limits<int>::max(), Intersecj=std::numeric_limits<int>::max();//Для упрощения отладки инициализируем самым большим числом
    int mini1, maxi1, minj1, maxj1; //Для сужения области поиска ячеек фронта волны. Больше ни для чего не будем эти переменные использовать
    WaveFrontInit(Maze, CellDist, CurrentDist, mini1, maxi1, minj1, maxj1, IsReachedfinish, 1, Interseci, Intersecj, starti, startj);
    int mini2, maxi2, minj2, maxj2;
    WaveFrontInit(Maze, CellDist, CurrentDist, mini2, maxi2, minj2, maxj2, IsReachedfinish, 2, Interseci, Intersecj, finishi, finishj);
    
    while((!IsReachedfinish)&&IsChanged) //одна итерация-одно продвижение фронта волны. Пока волны не встретятся или не застрянут.
    {
        CurrentDist++;
        WaveFrontIteration(Maze, CellDist, CurrentDist, mini1, maxi1, minj1, maxj1, IsReachedfinish, IsChanged, 1, Interseci, Intersecj);
        if(PrHandler.Mode==2) std::cout<<"Wave1 CurrDist="<<CurrentDist<<std::endl;
        if((IsReachedfinish)||(!IsChanged)) 
        {
            DebugHandler(Maze, CellDist, PrHandler);
            break; //если достигли пересечения или если волна застряла
        }
        WaveFrontIteration(Maze, CellDist, CurrentDist, mini2, maxi2, minj2, maxj2, IsReachedfinish, IsChanged, 2, Interseci, Intersecj);
        if(PrHandler.Mode==2) std::cout<<"Wave2 CurrDist="<<CurrentDist<<std::endl;
        DebugHandler(Maze, CellDist, PrHandler);
    }

    //Проверяем существование пути и восстанавливаем путь.
    if(!IsReachedfinish)
    {
        std::cout<<"The way between starti="<<starti<<" startj="<<startj<<" and finishi="<<finishi<<" finishj="<<finishj<<" does not exist!"<<std::endl; //you do not know de wey
        return;
    }
    else
    {
        if(PrHandler.Mode==2) std::cout<<"Intersection cell between waves: Interseci="<<Interseci<<" Intersecj="<<Intersecj<<std::endl;
    }
    //Будем идти от точки пересечения в обе стороны. Вначале дойдем до точки старта, потом до точки финиша.
    int Currenti=Interseci, Currentj=Intersecj;
    Way.clear();
    Way.insert(Way.begin(),std::make_pair(Currenti, Currentj));
    //Восстанавливаем участок пути от стартовой ячейки до ячейки пересечения волн.
    ReconstructWay(Maze, CellDist, 1, Interseci, Intersecj, starti, startj, Way, false);
    // Теперь то же самое для конечного участка, т.е. для второй волны. Т.е. восстанавливаем второй кусок пути.
    ReconstructWay(Maze, CellDist, 2, Interseci, Intersecj, finishi, finishj, Way, true);

}

void DebugHandler(maze& Maze, std::vector<std::vector<std::pair<char, int>>>& CellDist, presenthandler& PrHandler) //Небольшие манипуляции, чтобы помочь отладить это.
{
    if(PrHandler.Mode==2) //Небольшие манипуляции, чтобы помочь отладить это.
    {
        for(int i=0; i<Maze.n; i++)
        {
            for(int j=0; j<Maze.m; j++)
            {
                if(CellDist.at(i).at(j).second==std::numeric_limits<int>::max())
                {
                    Maze.SetCellValue(i, j, '~');
                }
                else
                {
                    Maze.SetCellValue(i, j, (char)CellDist.at(i).at(j).second+48); //Если CellDist будет иметь большие значения, то в char они не влезут. Но для отладки подойдет.
                }
            }
        } 
        Maze.ShowDecorate((char*)"cout", 1, 2, true);
        std::cin.ignore(); 
    }
}

//Для алг АStar Dijkstra
inline void DijkstraReconstructWay(mazeWeighted& MazeWeighted, std::vector<std::vector<std::pair<char, int>>>& PathCoordWeights, int finishi, int finishj, int starti, int startj, std::vector<std::pair<int, int>>& Path) //Восстановение пути.
{
    int Currenti=finishi, Currentj=finishj;
    Path.insert(Path.begin(), std::make_pair(Currenti, Currentj));

    while(!((Currenti==starti)&&(Currentj==startj)))
    {
     //   std::cout<<"Currenti="<<Currenti<<" Currentj="<<Currentj<<std::endl;
        int tempCurrenti=MazeWeighted.GetNeighborI(Currenti, PathCoordWeights.at(Currenti).at(Currentj).first+2); //Идем в противоположную сторону, из которой пришли
        Currentj=MazeWeighted.GetNeighborJ(Currentj, PathCoordWeights.at(Currenti).at(Currentj).first+2);
        Currenti=tempCurrenti;

        Path.insert(Path.begin(), std::make_pair(Currenti, Currentj));
    }
}
//
void Dijkstra(mazeWeighted& MazeWeighted, int starti, int startj, int finishi, int finishj, std::vector<std::pair<int, int>>& Path, presenthandler& PrHandler)
{
    std::vector<std::vector<std::pair<char, int>>> PathCoordWeights(MazeWeighted.n); //Путевые координаты и веса пути у ячеек
    for(auto& i:PathCoordWeights)
    {
        i.resize(MazeWeighted.m, std::make_pair(NOTVISITED, 0)); //NOTVISITED Будем так помечать непосещенные ячейки
    //    for(auto& j:i) j.first=NOTVISITED; 
    }

    //Очередь с приоритетом. Хранит ячейки, которые нужно посетить. В качестве приоритета будем брать расстояние от ячейки старта + эвристика, зависящая от расстояния(на плоскости) до финишной ячейки
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> PriorQueue; //пара- приоритет(вес пути); координаты ячейки
    
/*  //Тестируем очередь с приоритетами
    std::vector<std::pair<int, std::pair<int, int>>> testVector;
    std::pair<int, std::pair<int, int>> testItem1, testItem2;
    
    testItem1.first=3;
    testItem1.second.first=1;
    testItem1.second.second=2;
    PriorQueue.emplace(testItem1);

    testItem1.first=0;
    testItem1.second.first=4;
    testItem1.second.second=5;
    PriorQueue.emplace(testItem1);
    while(!PriorQueue.empty())
    {
        testVector.push_back(PriorQueue.top());
        PriorQueue.pop();
    }
    PrintVector(testVector, "testVector");
*/
    //Устанавливаем атрибуты стартовой ячейки
    PathCoordWeights.at(starti).at(startj).first=4; //Путевые координаты пусть будут такими 0-3 значения alpha, если смотреть из ячейки, из которой мы пришли. 4 - отстуствие координат(только для исходной ячейки). NOTVISITED='~' ячейка не была посещена.
    PathCoordWeights.at(starti).at(startj).second=0; //Вес пути
    //Записываем в очередь стартовую ячейку
    PriorQueue.push(std::make_pair(PathCoordWeights.at(starti).at(startj).second, std::make_pair(starti, startj)));

    //Каждая итерация - просмотр одного элемента из очереди.
    bool IsFinishReached=false; //Достигли ли финишной ячейки
    if(PrHandler.Mode==1)
    {
        std::cout<<"PriorQueue all items:"<<std::endl;
    }
    while(!PriorQueue.empty())
    {
        //Извлекаем наиближайший элемент из очереди. (т.е. элемент, вес пути которого минимален из всех элементов в очереди)
        std::pair<int, std::pair<int, int>> CellFromQueue; //Для элемента, извлеченного из очереди
        CellFromQueue=PriorQueue.top();
        
        if(PrHandler.Mode==1)
        {
        std::cout<<"PriorQueue.top()=";
        Print(PriorQueue.top());
        std::cout<<std::endl;
        }
        PriorQueue.pop();

        //Если извлеченным элементом оказалась финишная ячейка, то прекращаем дальнейший обход ячеек (т.е. если это произошло, то значит в других ячейках веса путей не меньше, чем в финишной, а значит, с меньшим весом путь до финишной ячейки уже никак не может быть (случай с отрицательными весами ребер исходного графа мы здесь не рассматриваем))
        if(CellFromQueue.second==std::make_pair(finishi,finishj))
        {
            IsFinishReached=true;
            break;
        }

        //Просматриваем всех соседов извлеченной ячейки.
        for(int alpha=0; alpha<4; alpha++)
        {
            int NeighborI=MazeWeighted.GetNeighborI(CellFromQueue.second.first, alpha);
            int NeighborJ=MazeWeighted.GetNeighborJ(CellFromQueue.second.second, alpha);
         //   std::cout<<"NeighborI="<<NeighborI<<"NeighborJ"<<NeighborJ<<std::endl;
            if(!MazeWeighted.HasWall(CellFromQueue.second.first, CellFromQueue.second.second, alpha) ) //Если у текущая ячейка не отделена от соседней стеной
            {
                if(PathCoordWeights.at(NeighborI).at(NeighborJ).first==NOTVISITED) //Если этот сосед не был посещен ни разу
                {
                    PathCoordWeights.at(NeighborI).at(NeighborJ).first=alpha; //устанавливаем путевые координаты
                    PathCoordWeights.at(NeighborI).at(NeighborJ).second=PathCoordWeights.at(CellFromQueue.second.first).at(CellFromQueue.second.second).second + MazeWeighted.Weights.at(NeighborI).at(NeighborJ); //Вес пути в соседней ячейке равен весу пути в текущей ячейке+вес исходный в соседней ячейке
                    PriorQueue.emplace(std::make_pair(PathCoordWeights.at(NeighborI).at(NeighborJ).second, std::make_pair(NeighborI, NeighborJ))); //Помещаем в очередь (вес_он_же_приоритет, (i, j))
                
                    if(PrHandler.Mode==2)
                    {
                        std::cout<<"PathWeights % 1000:"<<std::endl;
                        MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true, PathCoordWeights, 2);
                        //Наглядное представление путевых координат
                        for(int i=0; i<MazeWeighted.n; i++) 
                        {
                            for(int j=0; j<MazeWeighted.m; j++)
                            {
                            //    if(PathCoordWeights.at(i).at(j).first>=0 &&PathCoordWeights.at(i).at(j).first<=9) MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first+48);
                            //    else MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                                switch (PathCoordWeights.at(i).at(j).first)
                                {
                                case 0:
                                    MazeWeighted.SetCellValue(i, j, '>');
                                    break;
                                case 1:
                                    MazeWeighted.SetCellValue(i, j, '^');
                                    break;
                                case 2:
                                    MazeWeighted.SetCellValue(i, j, '<');
                                    break;
                                case 3:
                                    MazeWeighted.SetCellValue(i, j, 'v');
                                    break;
                                case 4:
                                    MazeWeighted.SetCellValue(i, j, 's');
                                    break;
                                default:
                                    MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                                    break;
                                }
                            }
                        }
                        std::cout<<"PathCoordinates:"<<std::endl;
                        MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true);
                        std::cin.ignore();
                    }
                }
                else //Если сосед уже был посещен
                {
                    int NewPathWeight=PathCoordWeights.at(CellFromQueue.second.first).at(CellFromQueue.second.second).second + MazeWeighted.Weights.at(NeighborI).at(NeighborJ);
                    if(NewPathWeight<PathCoordWeights.at(NeighborI).at(NeighborJ).second) //Если вес пути оказался меньше, чем уже найденный
                    {
                        //Делаем то же самое
                        PathCoordWeights.at(NeighborI).at(NeighborJ).first=alpha; //устанавливаем путевые координаты
                        PathCoordWeights.at(NeighborI).at(NeighborJ).second=PathCoordWeights.at(CellFromQueue.second.first).at(CellFromQueue.second.second).second + MazeWeighted.Weights.at(NeighborI).at(NeighborJ); //Вес пути в соседней ячейке равен весу пути в текущей ячейке+вес исходный в соседней ячейке
                        PriorQueue.emplace(std::make_pair(PathCoordWeights.at(NeighborI).at(NeighborJ).second, std::make_pair(NeighborI, NeighborJ))); //Помещаем в очередь (вес_он_же_приоритет, (i, j))
                        if(PrHandler.Mode==2)
                        {
                            std::cout<<"PathWeights % 1000:"<<std::endl;
                            MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true, PathCoordWeights, 2);
                            //Наглядное представление путевых координат
                            for(int i=0; i<MazeWeighted.n; i++) 
                            {
                                for(int j=0; j<MazeWeighted.m; j++)
                                {
                                //    if(PathCoordWeights.at(i).at(j).first>=0 &&PathCoordWeights.at(i).at(j).first<=9) MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first+48);
                                //    else MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                                    switch (PathCoordWeights.at(i).at(j).first)
                                    {
                                    case 0:
                                        MazeWeighted.SetCellValue(i, j, '>');
                                        break;
                                    case 1:
                                        MazeWeighted.SetCellValue(i, j, '^');
                                        break;
                                    case 2:
                                        MazeWeighted.SetCellValue(i, j, '<');
                                        break;
                                    case 3:
                                        MazeWeighted.SetCellValue(i, j, 'v');
                                        break;
                                    case 4:
                                        MazeWeighted.SetCellValue(i, j, 's');
                                        break;
                                    default:
                                        MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                                        break;
                                    }
                                }
                            }
                            std::cout<<"PathCoordinates:"<<std::endl;
                            MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true);
                            std::cin.ignore();
                        }
                    }
                }
            }
        }
    }

    if(PrHandler.Mode==1)
    {
        //Вывод изначальных весов ячеек.
    //    MazeWeighted.WeightsToValues();
        std::cout<<"Weights:"<<std::endl;
        MazeWeighted.ShowDecorate((char*)"cout",1, 2, true, MazeWeighted.Weights);
        
        //Наглядное представление путевых весов
       /* for(int i=0; i<MazeWeighted.n; i++) 
        {
            for(int j=0; j<MazeWeighted.m; j++)
            {
                MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).second%10+48);
            //    if(PathCoordWeights.at(i).at(j).first>=0 &&PathCoordWeights.at(i).at(j).first<=9) MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first+48);
            //    else MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
            }
        }*/
        std::cout<<"PathWeights % 1000:"<<std::endl;
        MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true, PathCoordWeights, 2);
    
        //Наглядное представление путевых координат
        for(int i=0; i<MazeWeighted.n; i++) 
        {
            for(int j=0; j<MazeWeighted.m; j++)
            {
            //    if(PathCoordWeights.at(i).at(j).first>=0 &&PathCoordWeights.at(i).at(j).first<=9) MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first+48);
            //    else MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                switch (PathCoordWeights.at(i).at(j).first)
                {
                case 0:
                    MazeWeighted.SetCellValue(i, j, '>');
                    break;
                case 1:
                    MazeWeighted.SetCellValue(i, j, '^');
                    break;
                case 2:
                    MazeWeighted.SetCellValue(i, j, '<');
                    break;
                case 3:
                    MazeWeighted.SetCellValue(i, j, 'v');
                    break;
                case 4:
                    MazeWeighted.SetCellValue(i, j, 's');
                    break;
                default:
                    MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                    break;
                }
            }
        }
        std::cout<<"PathCoordinates:"<<std::endl;
        MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true);
    }

    //Проверяем, достигли ли мы финишной ячейки
    if(!IsFinishReached)
    {
        std::cout<<"The path from ("<<starti<<", "<<startj<< ") to ("<<finishi<<", "<<finishj<< ") does not exist!"<<std::endl;
        return;
    }
    if(PrHandler.Mode==1)
    {
        std::cout<<"The finish cell is reached!"<<std::endl;
    }
    Path.clear();
    DijkstraReconstructWay(MazeWeighted, PathCoordWeights, finishi, finishj, starti, startj, Path);
}
//Эвристическая функция для алг A*
int HeuristicAStar(int Currenti, int Currentj, int finishi, int finishj)
{
    return abs(finishi-Currenti)+abs(finishj-Currentj);
}
void AStar(mazeWeighted& MazeWeighted, int starti, int startj, int finishi, int finishj, std::vector<std::pair<int, int>>& Path, presenthandler& PrHandler)
{
    std::vector<std::vector<std::pair<char, int>>> PathCoordWeights(MazeWeighted.n); //Путевые координаты и веса пути у ячеек
    for(auto& i:PathCoordWeights)
    {
        i.resize(MazeWeighted.m, std::make_pair(NOTVISITED, 0)); //NOTVISITED Будем так помечать непосещенные ячейки
    //    for(auto& j:i) j.first=NOTVISITED; 
    }

    //Очередь с приоритетом. Хранит ячейки, которые нужно посетить. В качестве приоритета будем брать расстояние от ячейки старта + эвристика, зависящая от расстояния(на плоскости) до финишной ячейки
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> PriorQueue; //пара- приоритет(вес пути); координаты ячейки
    
/*  //Тестируем очередь с приоритетами
    std::vector<std::pair<int, std::pair<int, int>>> testVector;
    std::pair<int, std::pair<int, int>> testItem1, testItem2;
    
    testItem1.first=3;
    testItem1.second.first=1;
    testItem1.second.second=2;
    PriorQueue.emplace(testItem1);

    testItem1.first=0;
    testItem1.second.first=4;
    testItem1.second.second=5;
    PriorQueue.emplace(testItem1);
    while(!PriorQueue.empty())
    {
        testVector.push_back(PriorQueue.top());
        PriorQueue.pop();
    }
    PrintVector(testVector, "testVector");
*/
    //Устанавливаем атрибуты стартовой ячейки
    PathCoordWeights.at(starti).at(startj).first=4; //Путевые координаты пусть будут такими 0-3 значения alpha, если смотреть из ячейки, из которой мы пришли. 4 - отстуствие координат(только для исходной ячейки). NOTVISITED='~' ячейка не была посещена.
    PathCoordWeights.at(starti).at(startj).second=0; //Вес пути
    //Записываем в очередь стартовую ячейку
    PriorQueue.push(std::make_pair(PathCoordWeights.at(starti).at(startj).second+HeuristicAStar(starti, startj, finishi, finishj), std::make_pair(starti, startj)));

    //Каждая итерация - просмотр одного элемента из очереди.
    bool IsFinishReached=false; //Достигли ли финишной ячейки
    if(PrHandler.Mode==1)
    {
        std::cout<<"PriorQueue all items:"<<std::endl;
    }
    while(!PriorQueue.empty())
    {
        //Извлекаем наиближайший элемент из очереди. (т.е. элемент, вес пути=вес дейкстры+эвирстика  которого минимален из всех элементов в очереди)
        std::pair<int, std::pair<int, int>> CellFromQueue; //Для элемента, извлеченного из очереди
        CellFromQueue=PriorQueue.top();
        
        if(PrHandler.Mode==1)
        {
        std::cout<<"PriorQueue.top()=";
        Print(PriorQueue.top());
        std::cout<<std::endl;
        }
        PriorQueue.pop();

        //Если извлеченным элементом оказалась финишная ячейка, то прекращаем дальнейший обход ячеек (т.е. если это произошло, то значит в других ячейках веса путей не меньше, чем в финишной, а значит, с меньшим весом путь до финишной ячейки уже никак не может быть (случай с отрицательными весами ребер исходного графа мы здесь не рассматриваем))
        if(CellFromQueue.second==std::make_pair(finishi,finishj))
        {
            IsFinishReached=true;
            break;
        }

        //Просматриваем всех соседов извлеченной ячейки.
        for(int alpha=0; alpha<4; alpha++)
        {
            int NeighborI=MazeWeighted.GetNeighborI(CellFromQueue.second.first, alpha);
            int NeighborJ=MazeWeighted.GetNeighborJ(CellFromQueue.second.second, alpha);
         //   std::cout<<"NeighborI="<<NeighborI<<"NeighborJ"<<NeighborJ<<std::endl;
            if(!MazeWeighted.HasWall(CellFromQueue.second.first, CellFromQueue.second.second, alpha) ) //Если у текущая ячейка не отделена от соседней стеной
            {
                if(PathCoordWeights.at(NeighborI).at(NeighborJ).first==NOTVISITED) //Если этот сосед не был посещен ни разу
                {
                    PathCoordWeights.at(NeighborI).at(NeighborJ).first=alpha; //устанавливаем путевые координаты
                    PathCoordWeights.at(NeighborI).at(NeighborJ).second=PathCoordWeights.at(CellFromQueue.second.first).at(CellFromQueue.second.second).second + MazeWeighted.Weights.at(NeighborI).at(NeighborJ); //Вес пути в соседней ячейке равен весу пути в текущей ячейке+вес исходный в соседней ячейке
                    PriorQueue.emplace(std::make_pair(PathCoordWeights.at(NeighborI).at(NeighborJ).second+HeuristicAStar(NeighborI, NeighborJ, finishi, finishj), std::make_pair(NeighborI, NeighborJ))); //Помещаем в очередь (вес_он_же_приоритет, (i, j))
                }
                else //Если сосед уже был посещен
                {
                    int NewPathWeight=PathCoordWeights.at(CellFromQueue.second.first).at(CellFromQueue.second.second).second + MazeWeighted.Weights.at(NeighborI).at(NeighborJ);
                    if(NewPathWeight<PathCoordWeights.at(NeighborI).at(NeighborJ).second) //Если вес пути оказался меньше, чем уже найденный
                    {
                        //Делаем то же самое
                        PathCoordWeights.at(NeighborI).at(NeighborJ).first=alpha; //устанавливаем путевые координаты
                        PathCoordWeights.at(NeighborI).at(NeighborJ).second=NewPathWeight; //Вес пути в соседней ячейке равен весу пути в текущей ячейке+вес исходный в соседней ячейке
                        PriorQueue.emplace(std::make_pair(PathCoordWeights.at(NeighborI).at(NeighborJ).second+HeuristicAStar(NeighborI, NeighborJ, finishi, finishj), std::make_pair(NeighborI, NeighborJ))); //Помещаем в очередь (вес_он_же_приоритет, (i, j))
                    }
                }
            }
        }
    }

    if(PrHandler.Mode==1)
    {
        //Вывод изначальных весов ячеек.
    //    MazeWeighted.WeightsToValues();
        std::cout<<"Weights:"<<std::endl;
        MazeWeighted.ShowDecorate((char*)"cout",1, 2, true, MazeWeighted.Weights);
        
        //Наглядное представление путевых весов
       /* for(int i=0; i<MazeWeighted.n; i++) 
        {
            for(int j=0; j<MazeWeighted.m; j++)
            {
                MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).second%10+48);
            //    if(PathCoordWeights.at(i).at(j).first>=0 &&PathCoordWeights.at(i).at(j).first<=9) MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first+48);
            //    else MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
            }
        }*/
        std::cout<<"PathWeights % 1000:"<<std::endl;
        MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true, PathCoordWeights, 2);
    
        //Наглядное представление путевых координат
        for(int i=0; i<MazeWeighted.n; i++) 
        {
            for(int j=0; j<MazeWeighted.m; j++)
            {
            //    if(PathCoordWeights.at(i).at(j).first>=0 &&PathCoordWeights.at(i).at(j).first<=9) MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first+48);
            //    else MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                switch (PathCoordWeights.at(i).at(j).first)
                {
                case 0:
                    MazeWeighted.SetCellValue(i, j, '>');
                    break;
                case 1:
                    MazeWeighted.SetCellValue(i, j, '^');
                    break;
                case 2:
                    MazeWeighted.SetCellValue(i, j, '<');
                    break;
                case 3:
                    MazeWeighted.SetCellValue(i, j, 'v');
                    break;
                case 4:
                    MazeWeighted.SetCellValue(i, j, 's');
                    break;
                default:
                    MazeWeighted.SetCellValue(i, j, PathCoordWeights.at(i).at(j).first);
                    break;
                }
            }
        }
        std::cout<<"PathCoordinates:"<<std::endl;
        MazeWeighted.ShowDecorate((char*)"cout", 1, 2, true);
    }

    //Проверяем, достигли ли мы финишной ячейки
    if(!IsFinishReached)
    {
        std::cout<<"The path from ("<<starti<<", "<<startj<< ") to ("<<finishi<<", "<<finishj<< ") does not exist!"<<std::endl;
        return;
    }
    if(PrHandler.Mode==1)
    {
        std::cout<<"The finish cell is reached!"<<std::endl;
    }
    Path.clear();
    DijkstraReconstructWay(MazeWeighted, PathCoordWeights, finishi, finishj, starti, startj, Path);
}

#endif /* MAZESEARCHALG_H */
