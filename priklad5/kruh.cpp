/*
 * polygony.cpp: implementace trid pro objekty zalozene na polygonu
 */

#include <cstddef>	// NULL
#include <cmath>	// fabs()
#include "kruh.h"

using namespace obrazce;

// Konstruktor
Kruh::Kruh(const double polomer, const Bod stred) {
	this->ZadejPolomerAStred(polomer, stred);
}

// Zadani polomeru a stredu kruhu
void Kruh::ZadejPolomerAStred(const double polomer, const Bod stred) {
	this->polomer = polomer;
	this->stred = stred;
}

// Vypocet teziste kruhu (neuvazujeme posun ani zvetseni)
Bod Kruh::VypoctiTeziste() const {
	return this->stred;
}

// Vypocet obsahu kruhu (neuvazujeme posun ani zvetseni)
double Kruh::VypoctiObsah() const {
	return M_PI * pow(this->polomer, 2);
}

// Vykresleni kruhu na kontext podedeny od rozhrani IKontext
void Kruh::Vykresli(IKontext *kontext) const {
	// Jen zkontrolujeme ze kontext neni NULL
	if(!kontext)
		return;

	// Pokud je polomer mensi nez 1, nevykreslime nic
	if(this->polomer < 1)
		return;

	// Zvetseni je vlastne prenasobeni polomeru
	double polomer = this->polomer * this->zvetseni;

	// Posunuti
	Bod stred = {this->stred.x + this->posunuti.x,
		this->stred.y + this->posunuti.y};

	// Protoze kontexty jsou bitmapa (mapa bodu) zatimco IObrazec je vektorove
	// rozhrani, musime pro vykresleni pouzit aproximacni algoritmus (navic nam
	// do toho vstupuje 'zvetseni'.) Pouzijeme Bersenhamuv algoritmus popsany
	// zde:
	// http://www.ecse.rpi.edu/~wrf/Research/Short_Notes/bresenham.html
	float d, x, y; // d je deviace od perfektniho oblouku
	x = 0;
	y = polomer;

	// Vypsat kruhovou vysec
	kontext->Zapis(stred.x + x, stred.y + y);
	kontext->Zapis(stred.x - x, stred.y + y);
	kontext->Zapis(stred.x + x, stred.y - y);
	kontext->Zapis(stred.x - x, stred.y - y);
	kontext->Zapis(stred.x + y, stred.y + x);
	kontext->Zapis(stred.x - y, stred.y + x);
	kontext->Zapis(stred.x + y, stred.y - x);
	kontext->Zapis(stred.x - y, stred.y - x);

	d = 3 - 2 * polomer;
	while(x < y) {
		if(d < 0) {
			x++;
			d = d + (4 * x) + 6;
		} else {
			x++;
			y--;
			d = d + (4 * x) - (4 * y) + 10;
		}
		// Vypsat kruhovou vysec
		kontext->Zapis(stred.x + x, stred.y + y);
		kontext->Zapis(stred.x - x, stred.y + y);
		kontext->Zapis(stred.x + x, stred.y - y);
		kontext->Zapis(stred.x - x, stred.y - y);
		kontext->Zapis(stred.x + y, stred.y + x);
		kontext->Zapis(stred.x - y, stred.y + x);
		kontext->Zapis(stred.x + y, stred.y - x);
		kontext->Zapis(stred.x - y, stred.y - x);
	}
}

std::string Kruh::Typ() const {
	return "Kruh";
}

double Kruh::VratPolomer() const {
	return this->polomer;
}

Bod Kruh::VratStred() const {
	return this->stred;
}
