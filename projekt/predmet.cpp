/*
 * predmet.cpp: definice tridy Predmet
 */

#include "predmet.h"

using namespace data;


// Konstruktor
Predmet::Predmet(unsigned int id, std::string nazev) :
	id { id }, nazev { nazev } {
}

// Vrati id predmetu
unsigned int Predmet::VratId() const {
	return this->id;
}

// Vrati nazev predmetu
std::string Predmet::VratNazev() const {
	return this->nazev;
}

// Nastavi nazev predmetu
void Predmet::NastavNazev(std::string nazev) {
	this->nazev = nazev;
}
