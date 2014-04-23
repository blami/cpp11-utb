/*
 * asciikontext.cpp: implementace tridy AsciiKontext
 */

#include "asciikontext.h"

using namespace std;

// Konstruktor
AsciiKontext::AsciiKontext(const unsigned int pocetRadku,
	const unsigned int pocetSloupcu) {
	int x;

	this->vyska = pocetRadku;
	this->sirka = pocetSloupcu;

	for(x = 0; x < vyska; x++) {
		string radek(this->sirka, this->znakPozadi);
		this->matice.push_back(radek);
	}
}

// Nastavi znak urceny pro vykreslovani bodu na terminal
void AsciiKontext::NastavZnakPopredi(const char znak) {
	this->znakPopredi = znak;
}

// Nastavi znak urceny pro vykreslovani volneho mista (pozadi) na terminal
void AsciiKontext::NastavZnakPozadi(const char znak) {
	this->znakPozadi = znak;
}

// Vrati sirku kontextu
int AsciiKontext::VratVysku() const {
	return this->vyska;
}

// Vrati sirku kontextu
int AsciiKontext::VratSirku() const {
	return this->sirka;
}

// Zobrazi obsah kontextu
void AsciiKontext::Zobraz() const {
	int y;

	for(y = 0; y < this->vyska; y++) {
		cout << this->matice[y] << endl;
	}
}

// Zapise bod na souradnici x,y do matice kontextu.
void AsciiKontext::Zapis(const double x, const double y) {
	// Rozhrani definuje double coz je desetinny typ, nicmene nas kontext
	// pocita pouze s integralnim typem. Pouzita bude implicitni konverze se
	// ztratou presnosti.

	// Pred zapisem provedeme kontrolu, zda je zapisovano do prostoru kontextu
	// vymezeneho souradnicemi 0,0 sirka,vyska
	if(x >= 0 && x < this->sirka && y >= 0 && y < this->sirka) {
		this->matice[y][x] = this->znakPopredi;
	}
}

// Vymaze cely kontext.
void AsciiKontext::Vymaz() {
	int y;

	for(y = 0; y < this->vyska; y++) {
		this->matice[y].clear();
		this->matice[y].insert(0, this->sirka, this->znakPozadi);
	}
}
