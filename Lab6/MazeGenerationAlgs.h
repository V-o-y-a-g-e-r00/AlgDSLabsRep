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

//PresentHandler.Mode 0-не влиять; 1-выводить лабиринт в файл каждые 30 секунд; 2-пошаговый вывод лабиринта

void AldousBroder(maze& Maze, std::default_random_engine& generator, presenthandler& PrHandler)
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
        if(PrHandler.Mode==1)
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
void Wilson(maze& Maze, std::default_random_engine& generator, presenthandler& PrHandler) 
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

void WilsonSerial(maze& Maze, std::default_random_engine& generator, presenthandler& PrHandler) //более простая модификация, где выбирается первая неотмеченная ячейка вместо случайной.
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
        //Выбираем первую попавшуюся ячейку, которой ещё нет в UST
        int randI=0, randJ=0; //координаты искомой ячейки
        bool IsReached=false;
        for(int i=0; (i<Maze.n)&&(!IsReached); i++)
        {
            for(int j=0; (j<Maze.m)&&(!IsReached); j++)
            {
                if(Maze.GetCellValue(i, j)!=UST)
                {
                    randI=i;
                    randJ=j;
                    IsReached=true;
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

void BinaryTree(maze& Maze, std::default_random_engine& generator, presenthandler& PrHandler, int& alpha) //Хорошо бы сделать универсальность без использования условий. Только за счет использования %. Это, скорее всего, можно сделать(нечто подобное получилось сделать в классе maze), но из соображений читабельности и ограниченности времени оставим как есть.
{
    std::discrete_distribution<int> distr{0.5, 0.5};
    int StartI=0;
    int StartJ=0;
    switch (alpha%4) //направление вырезания стены. Вторую стену вырезаем против часовой стрелки
    {
    case 0: // L
        StartI=0;
        StartJ=Maze.m-1;
        for(int j=Maze.m-1-1; j>=0; j--) //крайние строку и столбец отдельно, чтобы было читабельно
        {
            Maze.SetCellWalls(0, j, alpha, false);
        }
        for(int i=1; i<Maze.n; i++)
        {
            Maze.SetCellWalls(i, Maze.m-1, alpha+1, false);
        }
        for(int i=1; i<Maze.n; i++)
        {
            for(int j=Maze.m-1-1; j>=0; j--)
            {
                Maze.SetCellWalls(i, j, alpha+distr(generator), false);
            }
        }
        break;
    case 1: // _|
        StartI=0;
        StartJ=0;
        for(int j=1; j<Maze.m; j++) //крайние строку и столбец отдельно, чтобы было читабельно
        {
            Maze.SetCellWalls(0, j, alpha+1, false);
        }
        for(int i=1; i<Maze.n; i++)
        {
            Maze.SetCellWalls(i, 0, alpha, false);
        }
        for(int i=1; i<Maze.n; i++)
        {
            for(int j=1; j<Maze.m; j++)
            {
                Maze.SetCellWalls(i, j, alpha+distr(generator), false);
            }
        }
        break;
    case 2: // 7
        StartI=Maze.n-1;
        StartJ=0;
        for(int j=1; j<Maze.m; j++) //крайние строку и столбец отдельно, чтобы было читабельно
        {
            Maze.SetCellWalls(Maze.n-1, j, alpha, false);
        }
        for(int i=Maze.n-1-1; i>=0; i--)
        {
            Maze.SetCellWalls(i, 0, alpha+1, false);
        }
        for(int i=Maze.n-1-1; i>=0; i--)
        {
            for(int j=1; j<Maze.m; j++)
            {
                Maze.SetCellWalls(i, j, alpha+distr(generator), false);
            }
        }
        break;
    case 3: // Г
        StartI=Maze.n-1;
        StartJ=Maze.m-1;
        for(int j=Maze.m-1-1; j>=0; j--) //крайние строку и столбец отдельно, чтобы было читабельно
        {
            Maze.SetCellWalls(Maze.n-1, j, alpha+1, false);
        }
        for(int i=Maze.n-1-1; i>=0; i--)
        {
            Maze.SetCellWalls(i, Maze.m-1, alpha, false);
        }
        for(int i=Maze.n-1-1; i>=0; i--)
        {
            for(int j=Maze.m-1-1; j>=0; j--)
            {
                Maze.SetCellWalls(i, j, alpha+distr(generator), false);
            }
        }
        break;
    }

}

//Есть идея по созданию алгоритма, который бы генерировал лабиринт от случайной точки до неизвестной заранее точки без тупиков. Т.е. змеевидного. При этом лабиринт должен охватывать все выделенное поле.
//Это можно сделать, если взять за основу алгоритм DFS. Т.е. пытающийся закончить начатое решение. (каждая пройденная ячейка будет содержать множество направлений, по которым из неё выходили, их количество(т.е. мы вернулись назад и выбрали другое возможное направление из 3 доступных. Исключение составит лишь исходная ячейка, из которой можно ходить во все 4 стороны, с этим случаем нужно отдельно подумать))
//Очевидно, что если ограничится только этим, то
//время алгоритма начнет быстро расти при увеличении поля. Поэтому нужно ввести дополнительные меры для отсечения заведомо не приводящих к решению варианты.
//Реализуем самое очевидное: если путь коснулся двух стен, то нужно определить, в каком состоянии находятся ячейки от линии, которыми лабиринт разбил поле на 2 области.
//В одной из областей ячейки либо должны все принадлежать лабиринту, либо, если есть ячейки, которые ему не принадлежат, то компонента связности этих ячеек должна иметь мощность, совпадающую с мощностью всех ячеек, которых нет в лабиринте.
//Аналогично можно поступить с ситуацией, когда лабиринт берет в петлю ячейки, которые не принадлежат лабиринту.
//Как только лабиринт коснулся себя, нужно взять эту ячейку и пройти по стрелке вперед, помечая ячейки на этом пути. Как только петля оказалось помеченой, нужно начать проверять состояние ячеек внутри петли аналогично случаю со стенами.
//Оказалось, что на все это добро не требуется дополнительная память. 8 бит, выделенных на состояние каждой ячейки достаточно, чтобы все это организовать.
//Действительно пусть есть один байт: 76543210 .Чтобы закодиновать множество всех уже совершенных переходов из данной ячейки(всего из ячейки можно ходить в 3 направления, в 4 направлении находится ячейка, из которой мы пришли, поэтому это направление не нужно кодировать)
//Нужно всего 4 бита (Всего 14 вариантов уже совершенных переходов: 4 варианта, когда мы совершили один переход из ячейки, 6 вариантов, когда 2 перехода из ячейки, и 4 варианта, когда совершили 3 перехода из ячейки. 4 перехода мы совершить уже не можем, т.к. одно из направлений занимет ячейка, из которой мы пришли)
//Поскольку 4 бита дают 16 вариантов, то у нас остается 2 неиспользованных вариантов. одним из этих вариантов закодируем случай, когда переходов небыло. Например, возьмем для этого код 0000. (Изначальная ячейка единственная, для которой нужно знать случай, когда мы совершали все 4 перехода и не смогли найти решение. Поэтому можем выделить ещё один свободный код под этот случай, например, код 1111. Действительно возьмем лабиринт 3х3. Выберем в качестве исходной ячейки левую среднюю. Не существует лабиринта, который бы являлся решением нашей задачи. Т.е. не для всехо полей существуют такие решения для каждой ячейки. Но если
// взять угловую ячейку, то для неё на любом поле можно найти решение.)
//Таким образом, у нас остается ещё 4 пустых бита. Их можно отвести на пометку ячеек во время провекри на связность (когда встречаем стены или образуем петлю.)
//В общем, алгоритм получается непростым, но вышесказаного достаточно, чтобы его реализовать, как мне кажется. Эффективность его, конечно, будет ещё ниже, чтем алгоритма Уилсона.
//Т.е. 1000х1000 сгенерировать им не получится, скорее всего. алг Уилсона работал для этого около 2х часов. Тут нужно добавлять ещё какие-то условия, помимо проверки на связность, как мне кажется.
//Например, проем в одну ячейку между лабиринтом и стеной или частями лабиринта - такая себе ситуация. Такое возможно только если в этом проеме находится конец всего лабиринта.
//Значит нужно отыскать конец этого единичного проема и строить кусок лабиринта с этого конца в обратном направлении.
//Что это значит? Начальный и конечный куски не могут соединяться, пока есть ячейки, не принадлежащие лабиринту. Значит это мы должны проверять. 
//Мы не можем занимать ячейку перед конечным куском лабиринта, пока у нас ещё есть не принадлежащие лабиринту ячейки.
//Нужно ли всвязи с конечным куском лабиринта делать проверку связности я пока не понял. Возможно, того, что перед конечным куском должна быть незанятая ячейка достаточно, чтобы с этим справлялать проверка связности, о которой написано выша.
//Очевидно, что лабиринт не может иметь 2 конца. Поэтому если у нас уже образовался один конец, то дальнейший поиск решения должен осуществляться так, чтобы не образовывался ещё один конец.
//Поскольку на состояние ячейки у нас аж 4 бита (4 бита заняты под множество совершенных переходов), то для этого доп памяти так же не потребуется.

//Вообще, если мы упираемся в память, мы можем хранить лабиринт каким-то другим образом. Например, если хранить в ячейке информацию о станах только одного угла (с добавлением фиктивных ячеек с угла всей области лабиринта), то экономия памяти стремиться к уменьшению в 2 раза. Так, для лабиринта 10х10 экономия 1,408 раза, для 100х100 экономия в 1,923 раза. Для 1000х1000 1,992 раза. (общая формула 1/(1/2+2/n+1/n^2))
//где n - сторона квадратного лабиринта.

//Посмотрел, какие бывают алгоритмы для генерирования таких лабиринтов: вставка стен в идеальный лабиринт (вход и выход рядом). С какой-то хитростью - вход и выход в противоположных концах. Ещё можно использовать Context-based Space Filling Curves, что бы это не значило.
// //////////////////////////////////////

//Алгоритм для проряжения стен лабиринта. Нужен, чтобы мы могли использовать с этим лабиринтом алгоритмы поиска кратчайшего пути. Фактически, если изначальный лабиринт идеальный, то происходит соединение случайных узлов дерева друг с другом, за счет чего оно перестает быть деревом.
void WallsReduce(maze& Maze, double probability, std::default_random_engine& generator) //probability - вероятность разрушения каждой из стен. 1 - лабиринт без внутренних стен.
{
    std::discrete_distribution<int> distr{probability, 1-probability};
    for(int i=0; i<Maze.n; i++)
    {
        for(int j=0; j<Maze.m; j++)
        {
            if(!distr(generator)) //Если стену нужно убрать
                Maze.SetCellWalls(i,j, 0, false, true);
            if(!distr(generator))
                Maze.SetCellWalls(i,j, 3, false, true);
        }
    }
}

//просто одна строка кода вместо двух строк кода.
void WilsonReduced(maze& Maze, std::default_random_engine& generator, presenthandler& PrHandler, double probability)
{
    Wilson(Maze, generator, PrHandler);
    WallsReduce(Maze, probability, generator);
}

//Вспомогательная функция. Тут все попростому. Дискретизация, как я понимаю, это отдельный вопрос.
inline void WeightCircule(mazeWeighted& MazeWeighted, int Oi, int Oj, int Radius, int Weight)
{
    for(int i=Oi-Radius; i<=Oi+Radius; i++)
    {
        for(int j=Oj-Radius; j<=Oj+Radius; j++)
        {
            if((i-Oi)*(i-Oi)+(j-Oj)*(j-Oj)<=Radius*Radius && i<MazeWeighted.Weights.size())
            {   if(j<MazeWeighted.Weights.at(i).size())
                    MazeWeighted.Weights.at(i).at(j)=Weight;
            }
        }
    }
    std::cout<<"Radius="<<Radius<<std::endl;
}
//Генерация весов ячеек для лабиринта с весами
//Генерация меня сильно озадачила. Вначале я хотел сделать, чтобы генерация зависела от размеров лабиринта, но сейчас мне это не кажется хорошей идеей.
void RandomCircules(mazeWeighted& MazeWeighted, std::default_random_engine& generator, int minWeight, int maxWeight, double probability, int meanRadius, double stddevRadiusRatio) //Генерируем круги. probability вероятность, что из данной ячейки будет построен круг с текущим весом. RadiusRatio - отношение радиуса генерируемых кругов к максимальному измерению лабиринта. Т.е. при RadiusRatio=1 матожидание радиуса будет равно половине максимального измерения лабиринта. при 0-нулю. stddevRatio чем меньше, тем меньше отклонение от матожидания
{
//    std::uniform_int_distribution<int> distr();
    std::normal_distribution<double> distrRadius(meanRadius, stddevRadiusRatio*meanRadius); //для генерации радиусов кругов
    std::discrete_distribution<int> distrAppearance{1-probability, probability}; //для принятия решения о генерации круга в ячейке

    auto PositiveRadius{[](int Radius)->int
        {
            if(Radius<0) Radius=0;
            return Radius;
        }};
    WeightCircule(MazeWeighted, 5, 5, PositiveRadius(distrRadius(generator)), 1);



}
#endif /* MAZEGENERATIONALGS_H */
