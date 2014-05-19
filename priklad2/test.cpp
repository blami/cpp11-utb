/*
 * test.cpp: test implementace tridy AsciiKontext
 */

#include <iostream>
#include "asciikontext.h"
#include "kruh.h"
#include "polygony.h"
#include "trojuhelnik.h"
#include "ctverec.h"

using namespace std;

int main()
{
	// Nastaveni rozmeru
	int pocetRadku = 20;
	int pocetSloupcu = 20;
	Bod T;
	float S;

	// Inicializace AsciiKontext s nastavenymi rozmery
	AsciiKontext kontext(pocetRadku, pocetSloupcu);

	cout << "Teziste a obsahy jsou vypocteny bez zvetseni a posunuti:" << endl;

	// Kruh
	Kruh kruh = Kruh();
	kruh.ZadejPolomerAStred(2,2,2);
	kruh.ZadejZvetseni(1.5);
	kruh.ZadejPosunuti(2,2);
	kruh.Vykresli(&kontext);
	// Vypocitej a vypis teziste a plochu
	T = kruh.VypoctiTeziste();
	S = kruh.VypoctiObsah();
	cout << "Kruh (r=2, x=2, y=2) Z=1.5 P=2,2  " <<
		"T=" << T.x << "," << T.y << " " <<
		"S=" << S
		<< endl;

	// Ctverec
	Ctverec ctverec = Ctverec();
	ctverec.ZadejDelkuStranyAStred(3,12,2);
	ctverec.ZadejZvetseni(2);
	ctverec.ZadejPosunuti(2,2);
	ctverec.Vykresli(&kontext);
	// Vypocitej a vypis teziste a plochu
	T = ctverec.VypoctiTeziste();
	S = ctverec.VypoctiObsah();
	cout << "Ctverec (a=3, x=12, y=2) Z=2 P=2,2 " <<
		"T=" << T.x << "," << T.y << " " <<
		"S=" << S
		<< endl;

	// Trojuhelnik
	Trojuhelnik trojuhelnik = Trojuhelnik();
	trojuhelnik.ZadejBody(1,10, 12,19, 0,17);
	trojuhelnik.Vykresli(&kontext);
	// Vypocitej a vypis teziste a plochu
	T = trojuhelnik.VypoctiTeziste();
	S = trojuhelnik.VypoctiObsah();
	cout << "Trojuhelnik (a=1,10 b=12,19 c=0,17) Z=1 P=0,0 " <<
		"T=" << T.x << "," << T.y << " " <<
		"S=" << S
		<< endl;
	kontext.Zapis(T.x, T.y);

	// Polygon (konvexni)
	Polygon polygon = Polygon();
	polygon.ZadejBod(0,-1);
	polygon.ZadejBod(0,1);
	polygon.ZadejBod(-1,0);
	polygon.ZadejBod(1,0);
	polygon.ZadejZvetseni(3);
	polygon.ZadejPosunuti(13,14);
	polygon.Vykresli(&kontext);
	// Vypocitej a vypis teziste a plochu
	T = polygon.VypoctiTeziste();
	S = polygon.VypoctiObsah();
	cout << "Polygon (0,-1 0,1 -1,0 1,0) Z=3 P=13,14 " <<
		"T=" << T.x << "," << T.y << " " <<
		"S=" << S
		<< endl;

	kontext.Zobraz();
	kontext.Vymaz();

	return 0;
}
