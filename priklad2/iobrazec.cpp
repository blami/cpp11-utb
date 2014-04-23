/*
 * iobrazec.cpp: implementace tridy IObrazec.
 */

#include "iobrazec.h"

using namespace std;

// Zadani souradnice posunuti obrazce.
void IObrazec::ZadejPosunuti(const double x, const double y) {
	this->posunuti.x = x;
	this->posunuti.y = y;
}

// Zadani faktoru zvetseni obrazce.
void IObrazec::ZadejZvetseni(const double zvetseni) {
	this->zvetseni = zvetseni;
}
