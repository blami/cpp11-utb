/*
 * databaze.h: deklarace tridy Databaze
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "student.h"
#include "predmet.h"
#include "zapis.h"
#include "znamka.h"

namespace data {

// Trida predstavujici databazi studentu
class Databaze {
	private:
	std::vector<std::shared_ptr<Student>> studenti;
	std::vector<std::shared_ptr<Predmet>> predmety;
	std::vector<std::shared_ptr<Zapis>> zapisy;
	bool PorovnejString(const std::string& l, const std::string &p) const;

	public:
	void VytvorStudenta(std::string jmeno, std::string prijmeni,
		unsigned int rocnik);
	void SmazStudenta(std::shared_ptr<Student> student);
	const std::vector<std::shared_ptr<Student>> SeznamStudentu() const;
	const std::vector<std::shared_ptr<Student>> NajdiStudenta(
		StudentKriterium kriterium, std::string dotaz) const;
	void ZapisPredmet(std::shared_ptr<Student> student,
		std::shared_ptr<Predmet> predmet, Znamka znamka);
	const std::vector<std::shared_ptr<Zapis>> VratZapisy(
		std::shared_ptr<Student> student) const;
	float SpoctiPrumer(std::shared_ptr<Student> student) const;
	void VytvorPredmet(std::string nazev);
	void SmazPredmet(std::shared_ptr<Predmet>);
	const std::vector<std::shared_ptr<Predmet>> SeznamPredmetu() const;
	unsigned int VratPocetZapsanychStudentu(
		std::shared_ptr<Predmet> predmet) const;
	const std::vector<std::shared_ptr<Predmet>> NajdiPredmet(
		PredmetKriterium kriterium, std::string dotaz) const;
	void ZrusZapis(std::shared_ptr<Student> student,
		std::shared_ptr<Predmet> predmet);

	/*
	void NactiDatabazi();
	void UlozDatabazi();
	*/
};

} /* data:: */
