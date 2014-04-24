/*
 * bod.h: definice struktury pro zaznamenani souradnic bodu 
 */

#pragma once

namespace obrazce {

class Bod {
	public:
	double x;
	double y;

	// Implicitni konstruktor
	Bod(double x = 0, double y = 0) : x(x), y(y) {};

	// Kod inline metod musi byt v temze .h souboru aby prekladac rovnou vedel
	// co ma inlinovat
	inline bool operator< (const Bod& p) const;
};

// Operator < vyuzivany funkci sort k serazeni bodu podle souradnice x, prip.
// podle x a y.
inline bool Bod::operator< (const Bod& p) const {
	return x < p.x || (x == p.x && y < p.y);
};

} /* obrazce:: */
