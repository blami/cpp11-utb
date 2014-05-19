/*
 * trojuhelnik.h: definice tridy Trojuhelnik
 */

#pragma once

#include "polygony.h"

namespace obrazce {

// Pro funkcni polymorfismus (IObrazec) je treba verejna dedicnost od Polygonu.
// Metodu PridejBod ovsem smazeme abychom meli pod kontrolou "byti
// trojuhelnikem"
class Trojuhelnik : public Polygon {
	public:
	Trojuhelnik() {}; // Implicitni konstruktor
	Trojuhelnik(const Bod a, const Bod b, const Bod c);

	void ZadejBody(const Bod a, const Bod b, const Bod c);
	// Pretizime Typ()
	std::string Typ() const;

	// Smazeme metodu Polygon::ZadejBod()
	void ZadejBod(const Bod bod) = delete;
};

} /* obrazce:: */
