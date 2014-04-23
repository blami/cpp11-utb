/*
 * polygony.h: definice trid pro objekty zalozene na polygonu
 */

#pragma once

#include "iobrazec.h"
#include "bod.h"
#include <vector>

namespace obrazce {

class Polygon : public IObrazec {
	// Protected znamena ze potomci tridy IObrazec maji k takto deklarovanym
	// vlastnostem tridy pristup primo
	protected:
	// Polygon je tvoren N body spojenymi carou
	std::vector<Bod> body;

	public:
	Polygon() {}; // Implicitni konstruktor
	Polygon(const std::vector<Bod> body);

	void ZadejBod(const Bod bod);
	Bod VypoctiTeziste() const;
	double VypoctiObsah() const;
	void Vykresli(IKontext *ikontext) const;
};

// Ostatni konkretni pripady polygonu. Pouzivame private dedicnost abychom
// zakryli metodu ZadejBod() tridy Polygon. Ostatni metody jsou zpristupneny

class Ctverec : public Polygon {
	public:
	Ctverec() {}; // Implicitni konstruktor
	Ctverec(const double l, const Bod stred);

	void ZadejDelkuStranyAStred(const double l, const Bod stred);
	// Smazeme metodu Polygon::ZadejBod()
	void ZadejBod(const Bod bod) = delete;
};

class Trojuhelnik : public Polygon {
	public:
	Trojuhelnik() {}; // Implicitni konstruktor
	Trojuhelnik(const Bod a, const Bod b, const Bod c);

	void ZadejBody(const Bod a, const Bod b, const Bod c);
	// Smazeme metodu Polygon::ZadejBod()
	void ZadejBod(const Bod bod) = delete;
};

} /* obrazce:: */
