#! /usr/bin/bash
#start="Hello everybody"
#end="Good Luck"
start=$(gawk 'FNR==2{printf "%s", $1}' varsforscript.dat)

#gawk '' FNR==NR{x[$1]=$2;y[$1]=$3;next;} {if($1!=$2 && $2!="") printf "%%f\t%%f\t%%s\n", (x[$1]+x[$2])/2, (y[$1]+y[$2])/2 - %s, $3} '' %s %s',WeightOffset,

cat > test.gpi <<ADDTEXT3
$start
Welcome to Linux Blog Site.
$end
ADDTEXT3
chmod +x test.gpi
./test.gpi