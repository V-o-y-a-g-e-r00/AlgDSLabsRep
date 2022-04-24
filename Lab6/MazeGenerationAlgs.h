#ifndef MAZEGENERATIONALGS_H
#define MAZEGENERATIONALGS_H

#include "maze.h"
#include "random"
#include "presenthandler.h"

#define VISITED '1' //Для AldousBroder

#define UST '1' //Для Wilson
#define ARROWUP '^'
#define ARROWDOWN 'v'
#define ARROWLEFT '<'
#define ARROWRIGHT '>'

void AldousBroder(maze& Maze, std::default_random_engine& generator, presenthandler PrHandler)
{
    std::uniform_int_distribution<int> DistrI(0, Maze.n-1);
    std::uniform_int_distribution<int> DistrJ(0,Maze.m-1);
    std::uniform_int_distribution<int> Distrdidj(0,3);
    int randI=DistrI(generator);
    int randJ=DistrJ(generator);

    Maze.SetCellValue(randI, randJ, VISITED);
    int k=1;
    int di=0, dj=0;
    bool IsSatisfying=true; //когда у стены некотрые случайные значения не подходят
    int randcase=0;
    int t1=time(0);
    int t2=time(0);
    while(k!=Maze.n*Maze.m)
    {
        //Maze.ShowDecorate((char*)"cout", 1);
        if(PrHandler.Mode>=1)
        {
        if(t2-t1>=30)
        {
            Maze.ShowDecorate((char*)"MazeOut.txt", 1);
            t1=t2;
        }
        }
        randcase=Distrdidj(generator);
        switch (randcase)
        {
        case 0:
            if(randJ<Maze.m-1)
            {
                di=0;
                dj=1;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;
        case 1:
            if(randI>0)
            {
                di=-1;
                dj=0;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;
        case 2:
            if(randJ>0)
            {
                di=0;
                dj=-1;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;
        case 3:
            if(randI<Maze.n-1)
            {
                di=1;
                dj=0;
                IsSatisfying=true;
            }
            else IsSatisfying=false;
            break;        
        
        default:
            break;
        }
        if(IsSatisfying) //если не уперлись в стену
        {
            if(Maze.GetCellValue(randI+di, randJ+dj)!=VISITED)
            {
                Maze.SetCellWalls(randI, randJ, randcase, false);
                randI+=di;
                randJ+=dj;
                Maze.SetCellValue(randI, randJ, VISITED);    
                k++;
            }
            else
            {
                randI+=di;
                randJ+=dj;
            }
        }
        t2=time(0);
    }
}
//Реализацию нашел только на питоне. На си++ нету. Поэтому придется изобретать все велосипеды самостаятельно.
//Итак, доп память нам нужно только для возможности случайного выбора ячейки из ещё невыбранных, поскольку мы должны выбрать диапазон, в котором генерируется случайное число
//И как-то определять какая ячейка соответствуюет какому числу
//UPD сначала для этих целей я думал взять вектор или map (решил, что map более мне подходит, чем вектор, т.к. тормоза будут только при выборе случайной ячейки, но не при извлечении из него ячеек, как у вектора) 
//Но сейчас я понял ---что все идет по плану--- что можно не использовать дополнительную память: Максимальное генерируемое число будет определятся счетчиком оставшихся ячеек(изначально n*m , далее каждая пометка ячейки о пройденности в лабиринте сопровождается уменьшением счетчика на единицу)
//А выбор ячейки будем осуществлять так: будем последовательно пробегать строки и считать число встретившихся ячеек, которые мы ещё не посетили. Когда это число станет равным нашему сгенерированному числу мы и попадем в соответствующую этому числу ячейку.
//Таким образом, мой алгоритм не требует дополнительной памяти! Кроме той, которая нужна для хранения самого лабиринта.
//В методичке написано, что он потребляеть память O(N^2). Я думаю, что речь идет о хранении информации о направлении стрелочек в ячейке. У меня на информацию о ячейке отведен отдельный символ.
//Причем каждая стена кодируется отдельным символом, что позволяет хранить 256 состояний ячейки. Не считая информации о стенах, её окружающих.
//На самом деле, для хранения информации о ячейке достаточно всего одного символа. Ведь всего может быть 16 ситуаций со стенами для кажной ячейки.
//Т.е. если мы храним лабиринт в виде символов, где каждым символом закодирована ячейка, то мы помимо информации о стенах можем кодировать этими символом и состояние самой ячейки.
//более того, в каждой ячейке мы можем хранить лишь информацию о половине стен. (тут сложность будет в хранении информации о стенах по краям лабиринта. Можно ввести дополнительную строку и дополнительный столбец. В этом случае мы все равно экономим память. (на больших лабиринтах экономия до двух раз))
//Мы же используем избыточное число символов для наглядности. Так мы легко можем редактировать лабиринт вручную, просматривать его состояние.
//Если бы было 1 ячейка - 1 символ, то это было бы намного сложнее.
//В общем, с реальным расоходом алгоритмом памяти в O(N^2) мы можем встретиться только в экзотических ситуациях: при жесткой экономии памяти для ячеек(например, по 2(не по 4, а по 2) бита на ячейку. Либо же структура данных, отведенная под лабиринт содержит в себе ещё сторонюю информацию). Или при экзотической геометрии ячеек. 
//В методичке они очищают информацию о стрелках после каждого блуждания. Мы этого не делаем, поскольку это ни на что не влияет. (единственное, так было бы проще отлаживать: лишние стрелки будут сбивать с толку)
void Wilson(maze& Maze, std::default_random_engine& generator, presenthandler PrHandler) 
{
    std::uniform_int_distribution<int> InitDistrI(0, Maze.n-1);
    std::uniform_int_distribution<int> InitDistrJ(0,Maze.m-1);
    int InitrandI=InitDistrI(generator); //выбираем первую случайную ячейку.
    int InitrandJ=InitDistrJ(generator);

    int t1=time(0);
    int t2=time(0);

    Maze.SetCellValue(InitrandI, InitrandJ, UST);
    int USTCount=1; //число ячеек в UST
    while(USTCount != Maze.n*Maze.m) //Каждая итерация включает в UST новую ветвь.
    {
        //Наглядное отображение
        if(PrHandler.Mode==2)
        {
            Maze.ShowDecorate();
            std::cin.ignore();
        }
        //Случайным образом выбираем ячейку, которой ещё нет в UST
        std::uniform_int_distribution<int> DistrIter(0, Maze.n*Maze.m-1-USTCount); //Maze.n*Maze.m-1 номер последей ячейки во всем лабиринте при счете с нуля.
        int randIter=DistrIter(generator); //выбираем случайный номер ячейки.
        int k=0;
        int randI=0, randJ=0; //координаты искомой ячейки
        bool IsReached=false;
        for(int i=0; (i<Maze.n)&& (!IsReached); i++)
        {
            for(int j=0; (j<Maze.m)&& (!IsReached); j++)
            {
                if(Maze.GetCellValue(i, j)!=UST) //Тут позволим небольшой изврат, чтобы k не инициировать отрицательным числом.
                {
                    if(randIter==k)
                    {
                        randI=i;
                        randJ=j;
                        IsReached=true;
                    }
                    k++; //увеличиваем потом, а не в начале.
                }
            }
        }
        //Теперь блуждаем от этой ячейки, пока не уткнемся в UST
        std::uniform_int_distribution<int> Distrdidj(0,3);
        int di=0, dj=0;
        bool IsSatisfying=true; //когда у стены некотрые случайные значения не подходят
        int randcase=0;
        int WanderI, WanderJ; //Текущие i j
        WanderI=randI;
        WanderJ=randJ;
        while(Maze.GetCellValue(WanderI, WanderJ)!=UST) //Пока не дойдем до области UST
        {
            //Наглядное отображение
            if(PrHandler.Mode==1)
            {
            t2=time(0);
            if(t2-t1>=30)
            {
                Maze.ShowDecorate((char*)"MazeOut.txt", 1);
                std::cout<<"presenthandler: file has been rewrited"<<std::endl;
                t1=t2;
            }
            }
            randcase=Distrdidj(generator);
            switch (randcase) //выбираем направление движения с учетом внешних стен лабиринта
            {
            case 0:
                if(WanderJ<Maze.m-1)
                {
                    di=0;
                    dj=1;
                    IsSatisfying=true;
                }
                else IsSatisfying=false;
                break;
            case 1:
                if(WanderI>0)
                {
                    di=-1;
                    dj=0;
                    IsSatisfying=true;
                }
                else IsSatisfying=false;
                break;
            case 2:
                if(WanderJ>0)
                {
                    di=0;
                    dj=-1;
                    IsSatisfying=true;
                }
                else IsSatisfying=false;
                break;
            case 3:
                if(WanderI<Maze.n-1)
                {
                    di=1;
                    dj=0;
                    IsSatisfying=true;
                }
                else IsSatisfying=false;
                break;        
            
            default:
                break;
            }
            if(IsSatisfying) //если не уперлись в стену, то ставим стрелку и переходим в соответствии с di dj
            {
                switch (randcase)
                {
                case 0:
                    Maze.SetCellValue(WanderI, WanderJ, ARROWRIGHT);
                    break;
                case 1:
                    Maze.SetCellValue(WanderI, WanderJ, ARROWUP);
                    break;
                case 2:
                    Maze.SetCellValue(WanderI, WanderJ, ARROWLEFT);
                    break;
                case 3:
                    Maze.SetCellValue(WanderI, WanderJ, ARROWDOWN);
                    break;
                default:
                    break;
                }
                WanderI+=di;
                WanderJ+=dj;
            }
        }
        //Теперь возвращаемся к ячейке, с которой начали блуждания и строим уже окончательную ветвь по стрелкам.
        WanderI=randI;
        WanderJ=randJ;
        while(Maze.GetCellValue(WanderI, WanderJ)!=UST) //Пока не дойдем до области UST
        {
            switch (Maze.GetCellValue(WanderI, WanderJ)) //Убираем стрелку на символ UST и переходим в ячейку по стрелке. Увеличиваем счетчик ячеек в UST.
            {
            case ARROWRIGHT:
                Maze.SetCellValue(WanderI, WanderJ, UST);
                Maze.SetCellWalls(WanderI, WanderJ, 0, false);
                USTCount++;
                WanderJ++;
                break;
            case ARROWUP:
                Maze.SetCellValue(WanderI, WanderJ, UST);
                Maze.SetCellWalls(WanderI, WanderJ, 1, false);
                USTCount++;
                WanderI--;
                break;
            case ARROWLEFT:
                Maze.SetCellValue(WanderI, WanderJ, UST);
                Maze.SetCellWalls(WanderI, WanderJ, 2, false);
                USTCount++;
                WanderJ--;
                break;
            case ARROWDOWN:
                Maze.SetCellValue(WanderI, WanderJ, UST);
                Maze.SetCellWalls(WanderI, WanderJ, 3, false);
                USTCount++;
                WanderI++;
                break;
            }
        }
    }

}




#endif /* MAZEGENERATIONALGS_H */
