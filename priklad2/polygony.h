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
