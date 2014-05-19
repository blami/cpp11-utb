/*
 * test.cpp: test implementace tridy AsciiKontext
 */

#include <iostream>
#include <memory>
#include "kruh.h"
#include "polygony.h"
#include "ctverec.h"
#include "trojuhelnik.h"
#include "platno.h"
#include "imagekontext.h"

using namespace std;

int main()
{
	shared_ptr<obrazce::IKontext> kontext =
		make_shared<obrazce::ImageKontext>("test.bmp",100,100);
	obrazce::Platno platno(kontext);

	shared_ptr<obrazce::Kruh> kruh =
		make_shared<obrazce::Kruh>(40, obrazce::Bod(1,1));
	shared_ptr<obrazce::Ctverec> ctverec =
		make_shared<obrazce::Ctverec>(40, obrazce::Bod(50,50));

	platno.Pridej(kruh);
	platno.Pridej(ctverec);

	platno.Zobraz();

	return 0;
}
