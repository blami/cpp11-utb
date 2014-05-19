/*
 * ctverec.cpp: implementace tridy Ctverec
 */

#include "ctverec.h"

using namespace std;

void Ctverec::ZadejDelkuStranyAStred(const double l,
	const double x, const double y) {

	// Vymazat vsechny body ctverce
	this->body.clear();

	// Pokud je delka strany 0 nebo mensi, nepridame zadne body
	if(l <= 0)
		return;

	// Pridat body ctverce (stred +- pulka delky strany) s vyuzitim metody
	// ZadejBod() z predku Polygon

	// Body jsou zadavany po smeru hodinovych rucicek od 0,0
	this->ZadejBod(x - (l / 2), y - (l / 2));
	this->ZadejBod(x + (l / 2), y - (l / 2));
	this->ZadejBod(x + (l / 2), y + (l / 2));
	this->ZadejBod(x - (l / 2), y + (l / 2));
}
