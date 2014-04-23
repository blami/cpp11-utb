/*
 * iobrazec.cpp: implementace tridy IObrazec.
 */

#include "iobrazec.h"

using namespace obrazce;

// Zadani souradnice posunuti obrazce.
void IObrazec::ZadejPosunuti(const Bod posunuti) {
	this->posunuti = posunuti;
}

// Zadani faktoru zvetseni obrazce.
void IObrazec::ZadejZvetseni(const double zvetseni) {
	this->zvetseni = zvetseni;
}
