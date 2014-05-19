/*
 * ctverec.h: definice tridy Ctverec
 */

#pragma once

#include "polygony.h"

namespace obrazce {

// Pro funkcni polymorfismus (IObrazec) je treba verejna dedicnost od Polygonu.
// Metodu PridejBod ovsem smazeme abychom meli pod kontrolou "byti ctvercem"
class Ctverec : public Polygon {
	private:
	double a;
	Bod stred;

	public:
	Ctverec() {}; // Implicitni konstruktor
	Ctverec(const double l, const Bod stred);

	void ZadejDelkuStranyAStred(const double l, const Bod stred);
	// Pretizime Typ()
	std::string Typ() const;

	// Smazeme metodu Polygon::ZadejBod()
	void ZadejBod(const Bod bod) = delete;
	double VratDelkuStrany() const;
	Bod VratStred() const;
};

} /* obrazce:: */
