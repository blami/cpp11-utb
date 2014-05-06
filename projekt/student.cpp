/*
 * student.cpp: definice tridy Student
 */

#include "student.h"

using namespace data;


// Konstruktor
Student::Student(unsigned int id, std::string jmeno, std::string prijmeni, 
	unsigned int rocnik) :
	id { id }, jmeno { jmeno }, prijmeni { prijmeni }, rocnik { rocnik } {
}

// Vrati id studenta
unsigned int Student::VratId() const {
	return this->id;
}

// Vrati krestni jmeno studenta
std::string Student::VratJmeno() const {
	return this->jmeno;
}

// Vrati prijmeni studenta
std::string Student::VratPrijmeni() const {
	return this->prijmeni;
}

// Vrati rocnik studenta
unsigned int Student::VratRocnik() const {
	return this->rocnik;
}

// Nastavi krestni jmeno studenta
void Student::NastavJmeno(std::string jmeno) {
	this->jmeno = jmeno;
}

// Nastavi prijmeni studenta
void Student::NastavPrijmeni(std::string prijmeni) {
	this->prijmeni = prijmeni;
}

// Nastavi rocnik studenta
void Student::NastavRocnik(unsigned int rocnik) {
	this->rocnik = rocnik;
}
