#!/bin/bash

#pocet cisel bud zadam nebo 10 :)
#if [ $# -lt 1 ];then 
#    numbers=10;
#else
#    numbers=$1;
#fi;
numbers=16


#preklad cpp zdrojaku
#mpic++ --prefix /usr/local/share/OpenMPI -o oets odd-even.cpp
mpicc --prefix /usr/local/share/OpenMPI -o pms pms.c


#vyrobeni souboru s random cisly
dd if=/dev/random bs=1 count=$numbers of=numbers 2>/dev/null

#výpočet potřebného počtu procesorů
procesors=$(echo "l(${numbers})/l(2)" | bc -l)
procesors=${procesors/.*}
procesors=$((procesors+1))
#echo $procesors

#spusteni

mpirun -np $procesors pms $numbers --oversubscribe 2>/dev/null

#uklid
rm -f pms numbers

