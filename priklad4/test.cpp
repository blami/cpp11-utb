/*
 * test.cpp: test implementace tridy AsciiKontext
 */

#include <iostream>
#include <memory>
#include "kruh.h"
#include "polygony.h"
#include "ctverec.h"
#include "trojuhelnik.h"
#include "obrazcejson.h"

using namespace std;

int main()
{
	shared_ptr<obrazce::Kruh> kruh =
		make_shared<obrazce::Kruh>(5, obrazce::Bod(10,10));
	shared_ptr<obrazce::Ctverec> ctverec =
		make_shared<obrazce::Ctverec>(5, obrazce::Bod(10,10));

	obrazcejson::Serializuj(kruh);
	obrazcejson::Serializuj(ctverec);

	return 0;
}
