/*
 * imagekontext.cpp: implementace tridy ImageKontext
 */

#include <sstream>
#include "imagekontext.h"

using namespace obrazce;

// Konstruktor
ImageKontext::ImageKontext(const std::string nazev,
	const unsigned int pocetRadku, const unsigned int pocetSloupcu) {
	this->nazev = nazev;
	this->sirka = pocetSloupcu;
	this->vyska = pocetRadku;

	// Vytvorit obraz pomoci knihovny CImg
	this->obraz = cimg_library::CImg<unsigned char>(this->sirka, this->vyska,
		1, 3, 255);
}

// Vrati sirku kontextu
int ImageKontext::VratVysku() const {
	return this->vyska;
}

// Vrati sirku kontextu
int ImageKontext::VratSirku() const {
	return this->sirka;
}

// Zobrazi obsah kontextu do souboru
void ImageKontext::Zobraz() const {
	this->obraz.save(this->nazev.c_str());
}

// Zapise bod na souradnici x,y do matice kontextu.
void ImageKontext::Zapis(const double x, const double y) {
	// Rozhrani definuje double coz je desetinny typ, nicmene nas kontext
	// pocita pouze s integralnim typem. Pouzita bude implicitni konverze se
	// ztratou presnosti.

	// Pred zapisem provedeme kontrolu, zda je zapisovano do prostoru kontextu
	// vymezeneho souradnicemi 0,0 sirka,vyska
	if(x >= 0 && x < this->sirka && y >= 0 && y < this->sirka) {
		const unsigned char barva_popredi[] = {0, 0, 0};
		this->obraz.draw_point(x, y, barva_popredi);
	}
}

// Vymaze cely kontext.
void ImageKontext::Vymaz() {
	this->obraz.fill(255);
}

std::string ImageKontext::Popis() const {
	std::stringstream popis;
	popis << "image " << this->nazev << " "
		<< this->sirka << "x" << this->vyska;

	return popis.str();
}
