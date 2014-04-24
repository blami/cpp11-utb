/*
 * kruh.h: definice tridy pro kruh
 */

#pragma once

#include "iobrazec.h"
#include "bod.h"

namespace obrazce {

class Kruh : public IObrazec {
	private:
	double polomer = 0;
	Bod stred = {0, 0};

	public:
	Kruh() {}; // Implicitni konstruktor
	Kruh(const double polomer, const Bod stred);

	void ZadejPolomerAStred(const double polomer, const Bod stred);
	Bod VypoctiTeziste() const;
	double VypoctiObsah() const;
	void Vykresli(IKontext *ikontext) const;
	std::string Typ() const;
	double VratPolomer() const;
	Bod VratStred() const;
};

} /* obrazce:: */
