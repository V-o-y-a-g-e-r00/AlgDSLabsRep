#! /usr/bin/bash
filelistVar=$(gawk -F '\t' '{printf "%s", $2}' Plotfilelist.txt)


cat > PlotScript.gpi << HEREDOC1
#! /usr/bin/gnuplot -persist

# Будем этим скриптом строить графики
#Тут неизменяемые настройки
title_f(f,a,u,v,b)= sprintf('%s=%.12f*x*log2(%.12fx+%.12f)+%.12f', f, a, u,v, b)

set grid
set datafile separator '\t'

#set terminal png size 1024, 768
#set output "LabPlot.png"
#set terminal svg enhanced size 3,2
#set output 'file.svg'

#Этот способ рабочий. Потом нужно преобразовать к .PNG с помощью команды. and then use imagemagick to convert the vector format to a .png: convert -verbose -density 300 -trim file.pdf -quality 100 -flatten -sharpen 0x1.0 file.png
#set terminal pdfcairo size 6, 5 #этот неплохо работает. Размер в дюймах
#set output 'file.pdf'

#для графиков данных
set linestyle 1 lc rgb "#0000FF" lw 2.5
set linestyle 2 lc rgb "#00FF00" lw 2.5
set linestyle 3 lc rgb "#FF0000" lw 2.5
#для линий треда
set linestyle 11 lc rgb "#000080" lw 1.25 dashtype 2
set linestyle 12 lc rgb "#008000" lw 1.25 dashtype 2
set linestyle 13 lc rgb "#800000" lw 1.25 dashtype 2


#Тут изменяемые настройки
#Положение легенды
#set key left
set key below

set title "Lab5" font "Helvetica Bold, 14"
set xlabel "N - number of graph vertices"
set ylabel "Time - average executing time, seconds"

set yrange [0:*]
#set xrange[-pi:pi]


#plot sin(x) title "sinux"  lc rgb "red", cos(x)  title "cosinus" lc rgb "green"
#plot "HeapSortOut.txt" w lp lc 3 pt 7 ps 30 smooth bezier
#plot "HeapSortOut.txt" w lp lc 2 pt 1 ps 2 smooth acsplines

# The equation log(x) -логарифм натуральный
#f1(x) = a1*x*log(u1*x+v1)/log(2)+b1
#f1(x)=(a1*x*log(u1*x))/log(2)+b1
# The fit 
#fit f1(x) "HeapSortOut.txt" u 1:2 via a1,b1, u1

#f2(x) = a2*x*log(u2*x+v2)/log(2)+b2
#fit f2(x) "QuickSortHoareOut.txt" u 1:2 via a2,b2, u2, v2

#f3(x) = a3*x*log(u3*x+v3)/log(2)+b3
#fit f3(x) "ShellSortOut.txt" u 1:2 via a3,b3, u3, v3

#listsize=5

array filelist1[5]
filelist=$filelistVar
i=1
do for [file in filelist] {
#filelist(t)="FloydWarshellOut.txt"
#filelist(t)=gawk 'FNR=t{printf "%s", }' filelist.txt
filelist1[i]=sprintf('%s', file);

#plot file using 1:2 smooth csplines with lines linestyle i

i=i+1
}



#plot \ 	"FloydWarshellOut.txt" using 1:2 notitle smooth csplines with lines linestyle 1, \
#    1 / 0 title "FloydWarshell" with lines linestyle 1
#	f1(x) title title_f("f1", a1,u1, 0,b1) with lines linestyle 11,\
#	\
#	"QuickSortHoareOut.txt" using 1:2 notitle smooth csplines with lines linestyle 2, \
# 	1 / 0 title "QuickSortHoare" with lines linestyle 2, \
#	f2(x) title title_f("f2",a2, u2, v2,b2) with lines linestyle 12, \
#	\
#	"ShellSortOut.txt" using 1:2 notitle smooth csplines with lines linestyle 3, \
# 	1 / 0 title "ShellSort" with lines linestyle 3, \
#	 f3(x) title title_f("f3", a3,u3, v3, b3) with lines linestyle 13

plot for [j=1:i-1] filelist1[j] using 1:2 smooth csplines with lines linestyle j title filelist1[j]



#Справка
# \ позволяет записать одну строку как несколько
# -persist позволяет держать окно открытым после завершения скрипта
#
#
#
HEREDOC1
chmod +x PlotScript.gpi
./PlotScript.gpi