/*
 * test.cpp: test implementace tridy AsciiKontext
 */

#include <iostream>
#include "asciikontext.h"


int main()
{
	// Nastaveni rozmeru
	int pocetRadku = 20;
	int pocetSloupcu = 20;

	// Inicializace AsciiKontext s nastavenymi rozmery
	AsciiKontext kontext(pocetRadku, pocetSloupcu);

	// Vypis nastavenych rozmeru na obrazovku (pro kontrolu)
	std::cout << "Rozmery: " \
		<< kontext.VratVysku() << " x " << kontext.VratSirku() \
		<< std::endl;

	// Zapis bodu do kontextu po diagonalach ve ctverci
	for (int i = 0; i < pocetRadku; ++i) {
		// Na souradnici akt. radek, sloupec (diagonala levy horni roh az pravy
		// dolni roh)
		kontext.Zapis(i, i);
		// Na souradnici akt. radek, pocet sloupcu - akt. sloupec (diagonala
		// pravy horni roh az levy dolni roh)
		kontext.Zapis(i, pocetRadku - 1 - i);
	}

	// Vypsat obsah kontextu na obrazovku
	kontext.Zobraz();

	// Zmenit vychozi znak pro 'nezapsanou pozici'
	kontext.NastavZnakPozadi('o');

	// Vymazani kontextu a zobrazeni prazdneho kontextu
	kontext.Vymaz();
	kontext.Zobraz();

	return 0;
}
