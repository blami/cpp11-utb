/*
 * ctverec.cpp: implementace tridy Ctverec
 */

#include "ctverec.h"

using namespace obrazce;

// Konstruktor
Ctverec::Ctverec(const double l, const Bod stred) {
	this->ZadejDelkuStranyAStred(l, stred);
}

void Ctverec::ZadejDelkuStranyAStred(const double l, const Bod stred) {

	// Vymazat vsechny body ctverce
	this->body.clear();

	// Pokud je delka strany 0 nebo mensi, nepridame zadne body
	if(l <= 0)
		return;

	// Pridat body ctverce (stred +- pulka delky strany) s vyuzitim metody
	// ZadejBod() z predku Polygon

	// Body jsou zadavany po smeru hodinovych rucicek od 0,0
	Polygon::ZadejBod({stred.x - (l / 2), stred.y - (l / 2)});
	Polygon::ZadejBod({stred.x + (l / 2), stred.y - (l / 2)});
	Polygon::ZadejBod({stred.x + (l / 2), stred.y + (l / 2)});
	Polygon::ZadejBod({stred.x - (l / 2), stred.y + (l / 2)});
}
