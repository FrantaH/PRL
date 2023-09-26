=Implementace algoritmu "Pipeline merge sort"=
Pomocí knihovny Open MPI implementujte v jazyce C/C++ algoritmus Pipeline-Merge sort tak, jak byl uveden na přednášce PRL.

==Deadline==
9. 4. 2021

==Vstup==
Vstupem je posloupnost šestnácti náhodných čísel uložených v souboru.

===Soubor numbers===
Soubor ''numbers'' obsahující čísla velikosti 1 byte, která jdou bez mezery za sebou. Pro příklad vytvoření tohoto souboru prostudujte soubor ''test'' (sekce  [[PRL:1. Projekt#ukázkové zdrojové kódy]]), ve kterém je ukázáno vytvoření takovéto posloupnosti náhodných čísel a její uložení do souboru pomocí utility ''dd''. V případě tohoto projektu nastavíte "numbers" napevno na 16. Tato utilita generuje náhodná čísla v rozsahu určeném velikostí bloku. Při bloku 1B jsou hodnoty v rozsahu 0-255. Vygenerovaná čísla jsou pak přesměrována do souboru. Vznikne tedy další soubor s náhodnými znaky jdoucími bez mezery za sebou. Po otevření v libovolném textovém editoru se hodnoty tváří jako náhodné ascii znaky, které by však měly být chápany jako celá čísla. Soubor je v tomto případě chápan jako binární.

==Výstup==
Výstup na ''stdout'' se skládá ze dvou částí:
# Jednotlivé načtené neseřazené hodnoty v jednom řádku oddělené mezerou (vypsat po načtení prvním procesorem).
# Jednotlivé seřazené hodnoty oddělené novým řádkem (od nejmenšího po největší).

===Příklad výstupu===

 <code>4 68 1 54 ... </code>
 <code>1</code>
 <code>4</code>
 <code>54</code>
 <code>68</code>
 ...

==Postup==
Vytvořte testovací skript ''test'', který bude řídit testování. Tento skript bude mít tyto vlastnosti:
* Bude pojmenován ''test'' nebo ''test.sh''.


Skript vytvoří soubor ''numbers'' s 16ti náhodnými čísly a následně spustí program se správným počtem procesorů. Skript nakonec smaže vytvořenou binárku a soubor ''numbers''. Vzhledem ke strojové kontrole výsledků se v odevzdané verzi kódu '''nebudou vyskytovat žádné jiné výstupy''' než uvedené a ze stejných důvodů je třeba dodržet výše uvedené body týkající se testovacího skriptu. Za nedodržení těchto požadavků budou strhávány body.

==Implementace==
Algoritmus implementujte v jazyce C/C++ pomocí knihovny Open MPI.


==Dokumentace==
Součástí řešení je dokumentace, která bude o rozsahu '''maximálně 3 strany''' (rozumné a odůvodněné překročení limitu stran není důvod k bodové srážce) funkčního textu.

Do dokumentace '''nedávejte''':
* Úvodní stranu, obsah, popis zadání.

V dokumentaci '''popište''':
* Rozbor a analýzu algoritmu, odvoďte jeho teoretickou složitost (časovou a prostorovou složitost, celkovou cenu). Uvedené vzorce slovně popište, včetně jejich proměnných.
* Implementaci.
* Komunikační protokol, jak si "procesy" zasílají zprávy. Pro vizualizaci použijte sekvenční diagram ([http://en.wikipedia.org/wiki/Sequence_diagram]). Nezapomeňte, že protokol musí být obecný, tedy pro ''n'' procesů.
* Závěr, ve kterém zhodnotíte dosažené výsledky.
* Pozor, hodnotí se i to, jak dokumentace působí! (Zejména vzhled, správná čeština/slovenština/angličtina.)

Knihovna Open MPI je navržena na praktické použití, proto neobsahuje žádné implicitní metody pro měření složitosti algoritmů. Je tedy třeba vymyslet nějaký explicitní způsob jejího měření a ten pak co nejdetailněji popsat v dokumentaci!

==Odevzdání==
Do wisu se odevzdává jeden archiv xlogin00.{tar|tgz|zip}, který bude velký do 1MB, a který obsahuje:
* zdrojový kód- pms.{c|cpp},
* hlavička- pms.h (pokud ji využijete),
* testovací shellový skript- {test|test.sh},
* dokumentaci- xlogin00.pdf,
* nic jiného...


Platí, že kvalita každé z části vzhledem k požadavkům má vliv na bodové ohodnocení . Počítejte s tím, že veškerá uvedená jména souborů jsou ''case sensitive''.

==Hodnocení==
Způsob možné reklamace projektu bude zveřejněn později.

<!--
==Hodnocení==
V této podkapitole jsou shrnuty nejčastější chyby a prohřešky, kterých jste se v 1. projektu dopustili. Prosím, dříve, než nám budete psát a dotazovat se nás, za co jsme právě Vám strhli body, přečtěte si celou podkapitolu, případně si stáhněte svůj odevzdaný projekt a překontrolujte si jej.

Ne za všechny chyby vám byly hned strhnuty body, u některých jsme vám snižovali bodové hodnocení, až když jejich počet překročil hranici tolerance:


===Programová část (0-4 body):===

Některé projekty se nám vůbec nepodařilo spustit, případně jsme pro jejich spuštění museli přepisovat testovací skripty. Je proto nutné, abyste přesně dodržovali zadání, počet parametrů při spuštění programu, význam těchto parametrů a způsob komprimace. Projekty musí fungovat minimálně na školním serveru merlin.

V případě, že jsme váš projekt vůbec nespustili, hodnotili jsme jej srážkou 4 bodů. Pokud program řadil v opačném pořadí, srážka byla 2 body. Za nutnou úpravu skriptu jsme sráželi 1 bod.

Testovali jsme s následujícími parametry:
 <code>testik "$test" 3 7</code>
 <code>testik "$test" 4 7</code>
 <code>testik "$test" 6 15</code>
 <code>testik "$test" 8 15</code>
 <code>testik "$test" 2 3</code>


===Dokumentace (0-4 body):===

Vedle funkčnosti programu byla hodnocena i dokumentace, přehlednost zdrojového kódu, komentáře, pojmenování souborů.

V dokumentaci byl kladen důraz na správnou analýzu složitosti vámi implementovaného algoritmu, zejména časové složitosti, správné odvození počtu procesorů, celkové ceny.
Dále byl kladen důraz na komunikační protokol a způsob testování/experimentování.

==== Komunikační protokol ====
*Komunikační protokol musí být obecný, tedy pro ''n'' procesorů. Taktéž z něj musí být zřejmý způsob zasílání zpráv mezi všemi procesory, jejich počet, pořadí. Špatný komunikační protokol, či jeho absenci, jsme hodnotili srážkou 1 bodu.

*Snažte se příště o jednoduché znázornění principu, ne složitý obrázek na stránku. Také je nutné, aby protokol byl obecný v tom smyslu, že pokud si vezmete jeden procesor, podíváte se na jeho ID, je vám jasné, komu zprávy zasílá, čí zprávy přijímá. Tedy pokud máte v protokole pouze popis otec/levý/pravý syn, je to špatně. Je nutné, abyste do protokolu (či jeho legendy) dopsali např. levý syn ID = ''2n + 1'', pravý syn ID = ''2n + 2'', rodič ID = ''n''. Či něco podobného, co by přesně identifikovalo kterýkoli procesor. 

==== Experimenty ====
*U experimentů je dobré si předem stanovit cíl testování, pak zhodnotit výsledky. Jestliže jste chtěli experimentováním ověřit časovou složitost algoritmu a měřili jste čas jeho chodu, je nutné, abyste opravdu měřili pouze chod tohoto algoritmu bez režie inicializace procesorů, načítaní obsahu souborů, rozesílání dat jednotlivým procesorům, bez výpisů na terminál a podobně. Zvláště načítání čísel ze souboru a rozesílání jednotlivých hodnot konkrétním procesorům velmi zkresluje výslednou složitost.

*Někteří měřili počet kroků v algoritmu. Pokud jste si stanovili jako cíl experimentů otestovat správnou implementaci, pak je to v pořádku. Počet kroků by tak měl odpovídat odvozené teoretické složitosti a tyto experimenty jsme akceptovali. Nicméně berte na vědomí, že tímto způsobem není možné ověřit časovou složitost v reálném použití, kde vám vznikají časové prodlevy způsobené režií přepínání procesů, jejich inicializací a podobně. V nejhorším případě paralelní výpočet vůbec nemusí potvrdit teoretickou složitost a může mít i horší výsledky než použití sekvenčního výpočtu. V dalším projektu proto raději své experimenty zaměřte na zjištění chování v praxi, a tedy měřte čas běhu samotného algoritmu.

*Jestliže jste si dali za cíl ověřit časovou složitost v praxi a měřili jste počet kroků, či jste měřili běh i s režií, pak jsme vám strhli 1 bod.

==== Výsledky experimentů ====
*Výsledky testů musí být vhodně reprezentovány, např. grafem.  Z desítek hodnot umístěných v tabulce se složitost ověří jen velmi obtížně. V případě, že v grafu zvolíte u osy reprezentující počet řazených čísel log. měřítko, výsledný průběh by se pak měl podobat exponenciále, ne přímce. Naopak, pokud máte měřítka lineární, vyjít by měla zhruba přímka. Pokud tomu tak není, je to v pořádku, testování prostě nevyšlo dle očekávání. Nelze pak však v závěru napsat, že výsledky experimentů potvrzují předem odvozenou složitost. Reprezentaci výsledků, či jejich zhodnocení, jsme taktéž hodnotili 1 bodem.

*Pro lepší interpretaci výsledků se zkuste v dalším projektu zaměřit i na vhodnou volbu měřítek jednotlivých os. Například při testování na hodnotách mocnin 2 se hodí použít log. měřítko o základu 2, ne 10. Také se snažte neplést si osy, tedy pokud měříte čas v závislosti na počtu prvků, pak na vodorovné ose by měl být počet prvků, na svislé ose čas. Osy popisujte a pište k ním i jednotky.

Do dokumentace nemusíte psát pseudokódy, ty si dohledáme v materiálech z přednášky.

Za dokumentaci jste mohli získat až 4 body. Některé dokumentace však vůbec nebylo možné otevřít, či jste je neodevzdali.



===Zbytek (0-2 body):===

Podle hlaviček souborů poměrně mnoho projektů vypracoval Jakub Žák, který psal ukázkové projekty a které jste evidentně použili jako šablony vašich projektů. Zkuste tedy přiřadit i správné hlavičky, ať to nevypadá, že si projekty necháváte napsat někým jiným.

Zdrojový kód byl hodnocen 1 bodem a stejně tak správný formát odevzdání byl hodnocen 1 bodem.
