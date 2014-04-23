/*
 * asciikontext.h: definice tridy AsciiKontext
 */

#ifndef __ASCIIKONTEXT_H
#define __ASCIIKONTEXT_H

#include "ikontext.h"
#include <vector>
#include <string>
#include <iostream>

// Implementace ascii kontextu ktery vypisuje na znakovy terminal. Umoznuje
// nastaveni znaku popredi a znaku pozadi. Veskere operace se kesuji do matice.
class AsciiKontext : public IKontext
{
	private:
	std::vector<std::string> matice;
	char znakPopredi = 'x';
	char znakPozadi = '-';
	int vyska;
	int sirka;

	public:
	AsciiKontext(const unsigned int pocetRadku, const unsigned int pocetSloupcu);
	void NastavZnakPopredi(const char znak);
	void NastavZnakPozadi(const char znak);

	// Zde necheceme pouzit 'virtual' protoze Asciikontext metody implementuje
	int VratVysku() const;
	int VratSirku() const;
	void Zobraz() const;
	void Zapis(const double x, const double y);
	void Vymaz();
};

#endif /* __ASCIIKONTEXT_H */
