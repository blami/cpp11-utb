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

} /* obrazce:: */
