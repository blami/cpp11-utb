/*
 * trojuhelnik.cpp: implementace tridy Trojuhelnik
 */

#include "trojuhelnik.h"
#include <cmath>	// sqrt(), pow()

using namespace obrazce;

// Konstruktor
Trojuhelnik::Trojuhelnik(const Bod a, const Bod b, const Bod c) {
	this->ZadejBody(a, b, c);
}

void Trojuhelnik::ZadejBody(const Bod a, const Bod b, const Bod c) {

	// Vymazat vsechny body trojuhelniku
	this->body.clear();

	// Pokud je splnena trojuhelnikova nerovnost, pridat body trojuhelniku
	double la = std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	double lb = std::sqrt(std::pow(c.x - b.x, 2) + std::pow(c.y - b.y, 2));
	double lc = std::sqrt(std::pow(a.x - c.x, 2) + std::pow(a.y - c.y, 2));

	if(la + lb > lc && la + lc > lb && lb + lc > la) {
		Polygon::ZadejBod(a);
		Polygon::ZadejBod(b);
		Polygon::ZadejBod(c);
	}
}

std::string Trojuhelnik::Typ() const {
	return "Trojuhelnik";
}
