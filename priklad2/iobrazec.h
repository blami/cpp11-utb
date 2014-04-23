/*
 * iobrazec.h - definice rozhrani IObrazec
 */

#pragma once

#include "ikontext.h"
#include "bod.h"

// Rozhrani IObrazec. C++ nedefinuje rozhrani jako takova. Proto IObrazec neni
// rozhrani ve smyslu Javovskeho interface, ale definice spolecnych vlastnosti
// vsech obrazcu (zvetseni, posunuti) a jejich manipulatoru a sady minimalniho
// rozhrani tvoreneho trojici virtualnich metod pro vypocet teziste, obsahu a
// vykresleni na libovolny typ kontextu podedeny od IKontext.
class IObrazec {
	protected:
	double zvetseni = 1;
	Bod posunuti = {0, 0};

	public:
	void ZadejPosunuti(const double x, const double y);
	void ZadejZvetseni(const double zvetseni);

	// Specificke metody, ktere musi kazdy potomek tridy IObrazec
	// naimplementovat.
	virtual Bod VypoctiTeziste() const = 0;
	virtual double VypoctiObsah() const = 0;
	virtual void Vykresli(IKontext *ikontext) const = 0;
};
