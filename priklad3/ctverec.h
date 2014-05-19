/*
 * ctverec.h: definice tridy Ctverec
 */

#pragma once

#include "polygony.h"

namespace obrazce {

// Pro funkcni polymorfismus (IObrazec) je treba verejna dedicnost od Polygonu.
// Metodu PridejBod ovsem smazeme abychom meli pod kontrolou "byti ctvercem"
class Ctverec : public Polygon {
	public:
	Ctverec() {}; // Implicitni konstruktor
	Ctverec(const double l, const Bod stred);

	void ZadejDelkuStranyAStred(const double l, const Bod stred);

	// Smazeme metodu Polygon::ZadejBod()
	void ZadejBod(const Bod bod) = delete;
};

} /* obrazce:: */
