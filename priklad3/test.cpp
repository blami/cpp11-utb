/*
 * test.cpp: test implementace tridy AsciiKontext
 */

#include <iostream>
#include <memory>
#include "asciikontext.h"
#include "kruh.h"
#include "polygony.h"
#include "platno.h"

using namespace std;

int main()
{
	shared_ptr<obrazce::IKontext> kontext =
		make_shared<obrazce::AsciiKontext>(20,20);

	shared_ptr<obrazce::Kruh> kruh =
		make_shared<obrazce::Kruh>(5, obrazce::Bod(10,10));
	shared_ptr<obrazce::Ctverec> ctverec =
		make_shared<obrazce::Ctverec>(5, obrazce::Bod(10,10));

	obrazce::Platno platno(kontext);

	platno.Pridej(kruh);
	platno.Pridej(ctverec);

	platno.Zobraz();

	return 0;
}
