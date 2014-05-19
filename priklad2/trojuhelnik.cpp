/*
 * trojuhelnik.cpp: implementace tridy Trojuhelnik
 */

#include "trojuhelnik.h"

using namespace std;

void Trojuhelnik::ZadejBody(const double x1, const double y1,
const double x2, const double y2,
const double x3, const double y3) {

	// Vymazat vsechny body trojuhelniku
	this->body.clear();

	// Pokud je splnena trojuhelnikova nerovnost, pridat body trojuhelniku
	double la = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	double lb = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
	double lc = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2));

	if(la + lb > lc && la + lc > lb && lb + lc > la) {
		this->ZadejBod(x1, y1);
		this->ZadejBod(x2, y2);
		this->ZadejBod(x3, y3);
	}
}
