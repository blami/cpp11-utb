/*
 * predmet.h: deklarace tridy Predmet
 */

#pragma once
#include <string>

namespace data {

// Trida predstavujici predmet
class Predmet {
	private:
	unsigned int id;
	std::string nazev;

	public:
	Predmet(unsigned int id, std::string nazev);
	unsigned int VratId() const;
	std::string VratNazev() const;
	void NastavNazev(std::string nazev);
};

// Vyctovy typ pro vyhledavani v predmetech dle kriteria
enum class PredmetKriterium {
	ID,
	NAZEV
};

} /* data:: */
