Copiaza-l intr-un proiect separat de github.
Intai trebuie sa-l pui in proiect daca lucrezi in codeblocks:
In codeblocks, in stanga la proiect, click dreapta pe proiect
	> add files > object_finder003.h
Include-l cu #include "object_finder003.h"


Este o singura clasa pe care o poti folosi:
clasa Map<tip de date>

Map este ca un array, doar ca in loc de indici de la 0 la N, are cuvinte.
Momentan, din pacate, este doar ceva foarte basic si va trebui sa folosesti functiile date, ca in exemplu:

Map<int> myMap;	//initializeaza un obiect Map care contine doar elemente de tip int
myMap.create();	//face niste initializari inauntru, nu merge fara
myMap.setNullElementTo(*ce vrei tu*);
/* cand vrei sa iei date din map de la un key si acel key nu exista,
*  iti returneaza automat *ce vrei tu*.
*  De exemplu, myMap.setNullElementTo(0) sau myMap.setNullElementTo("key not defined").
*  Nota: *ce vrei tu* trebuie sa aiba acelasi tip cu Mapul.
* (daca ai Map<int>, setNullElementTo(*un int*) )
*/

Apoi ai doar 2 metode pe care le folosesti:
	void myMap.push(string key, T date)
	T myMap.getData(string key)

Exemple:
myMap<float> mapAlcohol;
mapAlcohol.create();
mapAlcohol.setNullElementTo(0.00000089);

mapAlcohol.push("GicaBetivul", 0.013);
mapAlcohol.push("NeaNelu", 0.009);
mapAlcohol.push("PreotulVasile", 0);

cout<< mapAlcohol.getData("NeaNelu");	//o sa returneze 0.009
cout<< mapAlcohol.getData("dinozaur");  //o sa returneze 0.00000089

Nota: caracterele acceptate de key sunt doar a-z, A-Z, 0-9 si _
Nota: Map retine obiecte in sine, chestiile pe care le returneaza nu sunt pointeri, sunt direct referinte.
Nota: incearca combinatii atipice, pointeri, orice crezi ca nu ar mereg si ar trebui sa mearga

:)



