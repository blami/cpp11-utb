/*
 * polygony.h: definice trid pro objekty zalozene na polygonu
 */

#pragma once

#include "iobrazec.h"
#include <vector>

class Polygon : public IObrazec {
	// Protected znamena ze potomci tridy IObrazec maji k takto deklarovanym
	// vlastnostem tridy pristup primo
	protected:
	// Polygon je tvoren N body spojenymi carou
	std::vector<Bod> body;

	public:
	void ZadejBod(const double x, const double y);
	Bod VypoctiTeziste() const;
	double VypoctiObsah() const;
	void Vykresli(IKontext *ikontext) const;
};

// Ostatni konkretni pripady polygonu. Pouzivame private dedicnost abychom
// zakryli metodu ZadejBod() tridy Polygon. Ostatni metody jsou zpristupneny

class Ctverec : private Polygon {
	public:
	void ZadejDelkuStranyAStred(const double l, const double x, const double y);

	// Zpristupnene metody nadtridy Polygon
	using Polygon::ZadejZvetseni;
	using Polygon::ZadejPosunuti;
	using Polygon::VypoctiTeziste;
	using Polygon::VypoctiObsah;
	using Polygon::Vykresli;

};

class Trojuhelnik : private Polygon {
	public:
	void ZadejBody(const double x1, const double y1,
		const double x2, const double y2,
		const double x3, const double y3);

	// Zpristupnene metody nadtridy Polygon
	using Polygon::ZadejZvetseni;
	using Polygon::ZadejPosunuti;
	using Polygon::VypoctiTeziste;
	using Polygon::VypoctiObsah;
	using Polygon::Vykresli;
};
