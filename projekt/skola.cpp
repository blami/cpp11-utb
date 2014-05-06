/*
 * skola.cpp: hlavni zdrojovy soubor s funkci main
 */

#include <iostream>
#include "databaze.h"

using namespace std;


int main() {
	auto db = make_shared<data::Databaze>();

	db->VytvorPredmet("Elektronika");
	db->VytvorPredmet("Strojnictvi");
	db->VytvorPredmet("Cestina");

	db->VytvorStudenta("Jan", "Novak", 1);
	db->VytvorStudenta("Radim", "Starak", 5);

	auto student = db->NajdiStudenta(data::StudentKriterium::ID, "1");

	auto predmet = db->NajdiPredmet(data::PredmetKriterium::ID, "1");
	db->ZapisPredmet(student[0], predmet[0], data::Znamka::C);

	predmet = db->NajdiPredmet(data::PredmetKriterium::NAZEV, "cestina");
	db->ZapisPredmet(student[0], predmet[0], data::Znamka::A);

	db->SmazPredmet(db->NajdiPredmet(data::PredmetKriterium::ID, "1")[0]);

	cout << "Prumer: " << db->SpoctiPrumer(student[0]) << endl;

	for(auto i : db->VratZapisy(student[0])) {
		cout << (i->VratPredmet())->VratNazev() << " " << endl;
	}

}
