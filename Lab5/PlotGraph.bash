#! /usr/bin/bash
#Скрипт генерирует скрипт для gnuplot. Это необходимо, т.к. gnuplot не достаточно хорошо умеет работать с переменными.
#Тут будут переменные, которые влияют на генерацию.
# -F разделитель полей
nmtitle=$(gawk -F "\t" 'FNR==2{printf "%s", $1}' VarsForScript.dat)
IsOriented=$(gawk -F "\t" 'FNR==2{printf "%s", $2}' VarsForScript.dat)
IsSavePictureToFile=$(gawk -F "\t" 'FNR==2{printf "%s", $3}' VarsForScript.dat)
PictureName=$(gawk -F "\t" 'FNR==2{printf "%s", $4}' VarsForScript.dat)
IsWithVerticesWeights=$(gawk -F "\t" 'FNR==2{printf "%s", $5}' VarsForScript.dat)

#gawk передать переменную gnuplot не удастся, наверное. Проще сделать так.
VerticesRadius=2
VerticesWeightsOffset=$VerticesRadius+2

if [[ $IsOriented -eq 0 ]]
then
#Граф неориентированный
WeightPosVar=0.5
else
WeightPosVar=0.7
fi

#Чтобы можно было отключать показ весов вершин.
loadVerticesWeightsVar="loadVerticesWeights= \"1 / 0\""
if [[ $IsWithVerticesWeights -ne 0 ]]
then
#Если нужно с весами
read -r -d '' loadVerticesWeightsVar<<HEREDOCWEIGHTS1
loadVerticesWeights = sprintf('< gawk '' {printf "%%f\t%%f\t%%s\n", \$2, \$3 + $VerticesWeightsOffset, \$5} '' %s', flePnts);
HEREDOCWEIGHTS1
else
#Отправляем читать gawk заведомо пустой столбец 10
read -r -d '' loadVerticesWeightsVar<<HEREDOCWEIGHTS2
loadVerticesWeights = sprintf('< gawk '' {printf "%%f\t%%f\t%%s\n", \$2, \$3 + $VerticesWeightsOffset, \$10} '' %s', flePnts);
HEREDOCWEIGHTS2
fi


SavePictureVar=""
if [[ $IsSavePictureToFile -ne 0 ]]
then
read -r -d '' SavePictureVar<<ADDTEXT0
set terminal pdfcairo size 6, 5 #этот неплохо работает. Размер в дюймах
set output "$PictureName.pdf"
ADDTEXT0
fi

if [[ $IsOriented -eq 0 ]]
then
#Граф неориентированный
#HereDoc помещаем в перемнную. По read: -r Не позволять экранировать символы обратным слешем -d delimiter разделитель между вводимыми величинами
read -r -d '' plotvar<<ADDTEXT1
#loadEdges=x первой веришны; y первой вершины; Color; x второй веришны; y второй вершины; Color
loadEdges = sprintf('< gawk '' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;}   {printf "%%f\t%%f\t%%d\n%%f\t%%f\t%%d\n\n", x[\$1], y[\$1], \$4, x[\$2], y[\$2], \$4;} '' %s %s', flePnts, fleEdges);




plot \
    loadEdgesLoops using 1:2:(EdgesLoopRadius):3 with circles lc var notitle, \
    loadEdges using 1:2:3 with lines lc var notitle, \
    flePnts using 2:3:($VerticesRadius):4 with circles fill solid lc var notitle, \
    flePnts using 2:3:($VerticesRadius) with circles lc rgb "black" notitle, \
    flePnts using 2:3:1 with labels tc rgb "black" font "Arial Bold" notitle, \
    loadWeightsNoLoops using 1:2 with points pt 5 lc rgb "white" notitle, \
    loadWeightsNoLoops using 1:2:3 with labels tc rgb "black" center font "Arial Bold" notitle, \
    loadWeightsLoops using 1:2 with points pt 5 lc rgb "white" notitle, \
    loadWeightsLoops using 1:2:3 with labels tc rgb "black" center font "Arial Bold" notitle, \
    loadVerticesWeights using 1:2:3 with labels tc rgb "black" center font "Arial Bold" notitle, \
    1 / 0 title $nmtitle with points lc rgb "white", \
    1 / 0 title "$IsOriented" with points lc rgb "white", \
    1 / 0 title "$IsSavePictureToFile" with points lc rgb "white"


ADDTEXT1
else
#Граф ориентированный
read -r -d '' plotvar<<ADDTEXT2
#loadEdges=x первой веришны; y первой вершины; Color; dx(векторы требуют такой формат); dy; Color       x[\$2]-x[\$1] -это координата векторов без учета радиуса вершины графа. +0.01 нужно, чтобы в случае, когда вершини лежат друг на друге, не было деления на 0. 
loadEdges = sprintf('< gawk '' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;}   {printf "%%f\t%%f\t%%f\t%%f\t%%d\n\n", x[\$1], y[\$1], (x[\$2]-x[\$1])*(1-$VerticesRadius/sqrt((x[\$2]-x[\$1])*(x[\$2]-x[\$1])+(y[\$2]-y[\$1])*(y[\$2]-y[\$1])+0.01)), (y[\$2]-y[\$1])*(1-$VerticesRadius/sqrt((x[\$2]-x[\$1])*(x[\$2]-x[\$1])+(y[\$2]-y[\$1])*(y[\$2]-y[\$1])+0.01)), \$4;} '' %s %s', flePnts, fleEdges);

plot loadEdgesLoops using 1:2:(EdgesLoopRadius):3 with circles lc var notitle, \
    loadEdges using 1:2:3:4:5 with vectors arrowstyle var  notitle, \
    flePnts using 2:3:($VerticesRadius):4 with circles fill solid lc var notitle, \
    flePnts using 2:3:($VerticesRadius) with circles lc rgb "black" notitle, \
    flePnts using 2:3:1 with labels tc rgb "black" font "Arial Bold" notitle, \
    loadWeightsNoLoops using 1:2 with points pt 5 lc rgb "white" notitle, \
    loadWeightsNoLoops using 1:2:3 with labels tc rgb "black" center font "Arial Bold" notitle, \
    loadWeightsLoops using 1:2 with points pt 5 lc rgb "white" notitle, \
    loadWeightsLoops using 1:2:3 with labels tc rgb "black" center font "Arial Bold" notitle, \
    loadVerticesWeights using 1:2:3 with labels tc rgb "black" center font "Arial Bold" notitle, \
    1 / 0 title $nmtitle with points lc rgb "white", \
    1 / 0 title "$IsOriented" with points lc rgb "white", \
    1 / 0 title "$IsSavePictureToFile" with points lc rgb "white"
ADDTEXT2
fi

cat > PlotGraph.gpi <<ADDTEXT3
#! /usr/bin/gnuplot -persist
#Константы
LOOPOFFSET='5'
LOOPWEIGHTOFFSET='10'
EdgesLoopRadius=5;

set style line 1 lc rgb '#000000' lw 1   #Для ребер
set style line 2 lc rgb "green" lw 1
set style line 3 lc rgb "blue" lw 1
set style line 4 lc rgb "red" lw 1

set style arrow 1 head filled size 4,12,36 ls 1
set style arrow 2 head filled size 4,12,36 ls 2
set style arrow 3 head filled size 4,12,36 ls 3
set style arrow 4 head filled size 4,12,36 ls 4

set style line 11 lc rgb "white" #Для узлов
set style line 12 lc rgb "green"
set style line 13 lc rgb "blue"
set style line 14 lc rgb "red"

WeightOffset='0' #на петли не виляет


#Имена файлов с индексами и координатами точек; с информацией о ребрах; с легендой
flePnts = 'Vertices.dat'
fleEdges = 'EdgesForPlot.dat'
#GraphInfo= 'GraphInfo.dat'

#Отображаемая область xrange
x1=50
y1=50
set xr [-x1:x1]   
set yr [-y1:y1]

#Возможность читать стили из файла. (Чтобы определять, какими цветами будут окрашены узлы извне. Сами цвета устанавливаются тут)
set style increment user

#Устанавливаем одинаковый масштаб по осям
set size square   



#вот тут сложно. sprintf здесь это команда gnuplot. '' здесь кодируют одниночную кавычку.  '< gawk '' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;}   {printf "%%f\t%%f\n%%f\t%%f\n\n", x[\$1], y[\$1], x[\$2], y[\$2];} '' %s %s'
#-здесь это форматная строка sprintf, которая как и положено заключена в одинарные кавычки. %s %s это, собственно, спецификаторы формата в этой строке (больше спецификаторов формата эта строка не имеет)
#flePnt fleEdges - это аргументы, подставляемые вместо спецификаторов формата.
#остальные команды относится сугубо к утилите gawk. (при построении графика вся вот эта длинная строчка вызывается в теримнале). 
#FNR==NR сравнение числа обработанных строк из текущего файла с числом строк, обработанных за все время работы. Вместе с командой next позволяет выполнять действие x[\$1]=\$2;y[\$1]=\$3; только для первого файла в списке файлов
#Т.е. x[\$1]=\$2;y[\$1]=\$3; заполняет массивы x и y значениями 2 и 3 столбцов файла pnts.dat Запись x[\$1] означает, что индексы берутся из 1 столбца файла.После чего выполняется действие {printf "%%f\t%%f\n%%f\t%%f\n\n", x[\$1], y[\$1], x[\$2], y[\$2];} уже для второго файла
#Во втором файле у нас в 1 и 2 строках номера вершин, связянных друг с другом. т.е. в выходной строке у нас координаты начала и конца линий. Причем отдельные линии раделяются между собой пустой строкой
#printf в данном случае также команда gawk, а не bush или gnuplot


loadEdgesLoops = sprintf('< gawk '' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;}   {if(\$1==\$2) printf "%%f\t%%f\t%%d\n", x[\$1], y[\$1]-%s, \$4;} '' %s %s', LOOPOFFSET, flePnts, fleEdges);  

$loadVerticesWeightsVar

# gawk ' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;}   {printf "%%f\t%%f\n%%f\t%%f\n\n", x[\$1], y[\$1], x[\$2], y[\$2];} ' pnts.dat edges.dat

loadWeightsNoLoops = sprintf('< gawk '' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;} {if(\$1!=\$2 && \$2!="") printf "%%f\t%%f\t%%s\n", x[\$1]+(x[\$2]-x[\$1])*$WeightPosVar, y[\$1]+(y[\$2]-y[\$1])*$WeightPosVar - %s, \$3} '' %s %s',WeightOffset, flePnts, fleEdges);
  loadWeightsLoops = sprintf('< gawk '' FNR==NR{x[\$1]=\$2;y[\$1]=\$3;next;} {if(\$1==\$2) printf "%%f\t%%f\t%%s\n", (x[\$1]+x[\$2])/2, (y[\$1]+y[\$2])/2 - %s, \$3} '' %s %s',LOOPWEIGHTOFFSET, flePnts, fleEdges);
#loadGraphInfo = sprintf('< gawk '' {n=\$1;m=\$2;} {printf "n=%%d\tm=%%d", n, m} '' %s', GraphInfo);

#Тут номера столбцов не везде совпадают с номерами столбцов в исходном файле. Т.к. gawk формирует строку, которая воспринимается как файл. И у неё свои столбцы

#Будем ли выводить в файл. (полезно для серии изображений)
$SavePictureVar

#Немного через , но сойдет.
$plotvar

#plot \
#    loadEdges using 1:2 with lines lc rgb "black" lw 2 notitle, \ #рисуем
#    flePnts using 2:3:(0.6) with circles fill solid lc rgb "black" notitle, \ #рисуем кружки(узлы) (0.6) размер кружков
#    flePnts using 2:3:1 with labels tc rgb "white" font "Arial Bold" notitle, \ #рисуем текст в кружочках(узлах)
#    loadWeights using 1:2:3 with labels tc rgb "red" center font "Arial Bold" notitle


#Справка
# \ позволяет записать одну строку как несколько
# -persist позволяет держать окно открытым после завершения скрипта
# gawk -утилита для работы с файлами
#
#
ADDTEXT3
chmod +x PlotGraph.gpi
#Избавляемся от надоедливых варнингов, перенаправляя вывод в этот файл.
#./PlotGraph.gpi 2>/dev/null
./PlotGraph.gpi
#Конвертируем картинку
if [[ $IsSavePictureToFile -eq 1 ]]
then
convert -verbose -density 300 -trim $PictureName.pdf -quality 100 -flatten -sharpen 0x1.0 $PictureName.png
fi