/*
 * ctverec.h: definice tridy Ctverec
 */

#pragma once

#include "polygony.h"

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
