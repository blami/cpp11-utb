/*
 * trojuhelnik.h: definice tridy Trojuhelnik
 */

#pragma once

#include "polygony.h"

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
