/*
 * kruh.h: definice tridy pro kruh
 */

#pragma once

#include "iobrazec.h"

class Kruh : public IObrazec {
	private:
	double polomer = 0;
	Bod stred = {0, 0};

	public:
	void ZadejPolomerAStred(const double polomer,
		const double x, const double y);
	Bod VypoctiTeziste() const;
	double VypoctiObsah() const;
	void Vykresli(IKontext *ikontext) const;
};
