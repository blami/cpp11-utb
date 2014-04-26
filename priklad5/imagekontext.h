/*
 * imagekontext.h: definice tridy ImageKontext
 */

#pragma once

#include <string>
#include "ikontext.h"
#include "CImg.h"

namespace obrazce {

// Implementace ascii kontextu ktery vypisuje na znakovy terminal. Umoznuje
// nastaveni znaku popredi a znaku pozadi. Veskere operace se kesuji do matice.
class ImageKontext : public IKontext {
	private:
	std::string nazev;
	int vyska;
	int sirka;
	cimg_library::CImg<unsigned char> obraz;

	public:
	ImageKontext(const std::string nazev, const unsigned int pocetRadku,
		const unsigned int pocetSloupcu);

	int VratVysku() const;
	int VratSirku() const;
	void Zobraz() const;
	void Zapis(const double x, const double y);
	void Vymaz();
	std::string Popis() const;
};

} /* obrazce:: */
