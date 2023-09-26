# Mesh Multiplication=
Pomocí knihovny Open MPI implementujte v jazyce '''C++''' algoritmus Mesh Multiplication.

## Vstup a výstup==
Vstupem jsou textové soubory mat1 a mat2. 

Výsledná matice, která je získána operací mat1*mat2, bude vypsána na standardní výstup ve formátu specifikovaném níže.

Jako oddělovač čísel na řádku použijte mezeru (na vstupu i výstupu), jako oddělovač jednotlivých řádků pak znak nového řádku "\n".
### mat1===
První řádek mat1 obsahuje počet řádků.
```
3
1 -1
2  2
3  3
```

### mat2===
První řádek mat2 udává počet sloupců.
```
4
1  -2 -2 -8
-1 -2  7  10
```

### Výstup obecně===
```
a b c
d e f
g h i
```

### Příklad výstupu===
```
2:3 
1 2 3
4 5 6
```

## Postup==
### test.sh ===

<syntaxhighlight lang="bash">
#!/bin/bash

mat1=$(head -n1 mat1)
mat2=$(head -n1 mat2)

cpus=$((mat1*mat2))

mpic++ --prefix /usr/local/share/OpenMPI -o mm mm.cpp -std=c++0x
mpirun --prefix /usr/local/share/OpenMPI -np $cpus mm
rm -f mm
</syntaxhighlight>

Užijte dodaný skript test.sh. Výsledný '''program nebude přijímat žádné parametry''' (jména souborů s maticemi zná a nic více nepotřebuje, načítání velikosti matic řešte v programu).

## Dokumentace==
*Obdobné jako v 1. projektu 
*Hodnotí se i vzhled a jazyková úroveň.
*Obvyklý rozsah 3 strany (nepište zadání, úvodní stranu, obsah, pseudokódy).


### Obsah===
*Rozbor a analýza algoritmu Mesh Multiplication, teoretická složitost - prostorová, časová náročnost a cena, sekvenční diagram (popis zasílání zpráv mezi procesy - jednoduchý a obecný).
*Experimenty s různě velkými maticemi pro ověření časové složitosti (očekává se graf, nikoliv tabulka), nikoliv měření počtu kroků algoritmu
*Graf - osa x (vodorovná) bude počet procesorů/prvků a osa y (svislá) bude čas, pozor na měřítka obou os, graf bude mít popisky os a bude z něj na první pohled zřejmý závěr
*Závěr - zhodnocení experimentů, zamyšlení nad reálnou složitostí.

## Implementace==
*'''C++ (přeložitelné pomocí mpic++ kvůli jednotnému skriptu test.sh, ne nutně objektově)'''
*Open MPI
*nic jiného

## Odevzdání==
Do WISu se odevzdává jeden archiv xlogin00.{tar|tgz|zip}, který nepřesáhne 1MB a obsahuje:
* zdrojový kód: mm.cpp
* hlavička: mm.h (pokud ji využijete) 
* dokumentaci: xlogin00.pdf 
* nic jiného (binárky, obrázky, matice, test[.sh], ...) 

## Doplňkové informace==
*Výstupy programu budou strojově kontrolovány, mějte to prosím na paměti při implementaci.
*Budou testovány především korektní vstupy.
*Při implementaci se zaměřte zejména na důkladné pochopení toho, jak algoritmus funguje a co jednotlivé procesy dělají.
