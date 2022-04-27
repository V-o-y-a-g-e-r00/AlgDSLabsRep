#ifndef MAZESEARCHALG_H
#define MAZESEARCHALG_H

#include "maze.h"
#include "presenthandler.h"
#include <vector>
#include <utility> //pair
#include <limits> //будем помечать максимальным возможным значением непосещенные ячейки.
//Постараемся реализовать волновой алг и, может быть, его модификацию с двумя волнами. Так же есть идея немного его ускорить без какого-либо влияния на функциональность путем сокращения области поиска ячеек фронта на этапе распространения волны.
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
        if(PrHandler.Mode==1) //Небольшие манипуляции, чтобы помочь отладить это.
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
            Maze.ShowDecorate();
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
            if(CellDist.at(i).at(j).second==CurrentDist-1) //Если данная ячейка - ячейка фронта волны
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
        std::cout<<"Wave1 CurrDist="<<CurrentDist<<std::endl;
        if((IsReachedfinish)||(!IsChanged)) break; //если достигли пересечения или если волна застряла
        WaveFrontIteration(Maze, CellDist, CurrentDist, mini2, maxi2, minj2, maxj2, IsReachedfinish, IsChanged, 2, Interseci, Intersecj);
        std::cout<<"Wave2 CurrDist="<<CurrentDist<<std::endl;
        if(PrHandler.Mode==1) //Небольшие манипуляции, чтобы помочь отладить это.
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
            Maze.ShowDecorate();
            std::cin.ignore();
        }
    }

    //Проверяем существование пути и восстанавливаем путь.
    if(!IsReachedfinish)
    {
        std::cout<<"The way between starti="<<starti<<" startj="<<startj<<" and finishi="<<finishi<<" finishj="<<finishj<<" does not exist!"<<std::endl; //you do not know de wey
        return;
    }
    else
    {
        std::cout<<"Intersection cell between waves: Interseci="<<Interseci<<" Intersecj="<<Intersecj<<std::endl;
    }
    //Будем идти от точки пересечения в обе стороны. Вначале дойдем до точки старта, потом до точки финиша.
    int Currenti=Interseci, Currentj=Intersecj;
    Way.clear();
    Way.insert(Way.begin(),std::make_pair(Currenti, Currentj));
    while(!((Currenti==starti)&&(Currentj==startj)))
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
                if(CellDist.at(Currenti+di).at(Currentj+dj).first==1) //Если ячейка принадлежит первой волне
                {
                    MinNeighbor=CellDist.at(Currenti+di).at(Currentj+dj).second;
                    Cutalpha=alpha; //альфа, при которой мы нашли первого встретившегося соседа, принадлежащего данной волне.
                    minalpha=alpha;
                    break;
                }
            }
        }
        std::cout<<"minalpha="<<minalpha<<std::endl;
        
        for(int alpha=Cutalpha+1; alpha<4;alpha++) //ищем минимального соседа из всех соседей, принадлежащих данной волне.
        {
            int di=(alpha%2)*((alpha%4)*(alpha%2)-2); //формулы получены из графиков
            int dj=((alpha-1)%2)*(((alpha-1)%4)*((alpha-1)%2)-2);
            if(!Maze.HasWall(Currenti,Currentj, alpha)) //Если нет стены
            {
                if((CellDist.at(Currenti+di).at(Currentj+dj).first==1)&&(CellDist.at(Currenti+di).at(Currentj+dj).second<MinNeighbor))
                {
                    MinNeighbor=CellDist.at(Currenti+di).at(Currentj+dj).second;
                    minalpha=alpha;
                }
            }
        }
        //Добавляем минимального соседа, принадлежащего данной волне, в путь, и переходим к нему.
        int di=(minalpha%2)*((minalpha%4)*(minalpha%2)-2); //формулы получены из графиков
        int dj=((minalpha-1)%2)*(((minalpha-1)%4)*((minalpha-1)%2)-2);
        Way.insert(Way.begin(), std::make_pair(Currenti+di, Currentj+dj));
        Currenti+=di;
        Currentj+=dj;

        PrintVector(Way, "Way");
    }

}



#endif /* MAZESEARCHALG_H */
