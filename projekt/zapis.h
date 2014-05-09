/*
 * zapisy.h: deklarace tridy Zapis
 */

#pragma once
#include <string>
#include <memory>
#include "student.h"
#include "predmet.h"
#include "znamka.h"

namespace data {

// Trida predstavujici zapis predmetu
class Zapis {
	private:
	// Zapis nepotrebuje mit identifikator, protoze je jednoznacne urcen
	// klicem student:predmet.
	std::shared_ptr<Student> student;
	std::shared_ptr<Predmet> predmet;
	Znamka znamka;

	public:
	Zapis(const std::shared_ptr<Student> student,
		const std::shared_ptr<Predmet> predmet, Znamka znamka);
	std::shared_ptr<Student> VratStudenta() const;
	std::shared_ptr<Predmet> VratPredmet() const;
	Znamka VratZnamku() const;
	std::string VratZnamkuString() const;
	void NastavZnamku(const Znamka znamka);
	bool JeStudenta(const std::shared_ptr<Student> student);
	bool JePredmetu(const std::shared_ptr<Predmet> predmet);
};

} /* data:: */
