/*
 * zapis.cpp: definice tridy Zapis
 */

#include "zapis.h"

using namespace data;


// Konstruktor
Zapis::Zapis(std::shared_ptr<Student> student,
	std::shared_ptr<Predmet> predmet, Znamka znamka) :
	student { student }, predmet { predmet }, znamka { znamka } {
}

// Vrati zapsaneho studenta
std::shared_ptr<Student> Zapis::VratStudenta() const {
	return this->student;
}

// Vrati zapsany predmet
std::shared_ptr<Predmet> Zapis::VratPredmet() const {
	return this->predmet;
}

// Vrati znamku
Znamka Zapis::VratZnamku() const {
	return this->znamka;
}

// Vrati znamku jako string
std::string Zapis::VratZnamkuString() const {
	return ZnamkaString(this->znamka);
}

// Vrati true pokud je dany zapis zapisem studenta
bool Zapis::JeStudenta(std::shared_ptr<Student> student) {
	return this->student == student;
}

// Vrati true pokud je dany zapis zapisem predmetu
bool Zapis::JePredmetu(std::shared_ptr<Predmet> predmet) {
	return this->predmet == predmet;
}

// Nastavi znamku
void Zapis::NastavZnamku(const Znamka znamka) {
	this->znamka = znamka;
}
