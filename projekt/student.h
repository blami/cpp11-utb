/*
 * predmet.h: deklarace tridy Student
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "predmet.h"
#include "znamka.h"

namespace data {

// Trida predstavujici studenta
class Student {
	private:
	unsigned int id;
	std::string jmeno;
	std::string prijmeni;
	unsigned int rocnik;

	public:
	Student(unsigned int id, std::string jmeno, std::string prijmeni, 
		unsigned int rocnik);
	unsigned int VratId() const;
	std::string VratJmeno() const;
	std::string VratPrijmeni() const;
	unsigned int VratRocnik() const;
	void NastavJmeno(std::string jmeno);
	void NastavPrijmeni(std::string prijmeni);
	void NastavRocnik(unsigned int rocnik);
};

// Vyctovy typ pro vyhledavani ve studentech dle kriteria
enum class StudentKriterium {
	ID,
	JMENO,
	PRIJMENI,
	//ROCNIK
};

} /* data:: */
