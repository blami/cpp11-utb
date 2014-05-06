/*
 * zapisy.h: deklarace trid Zapis a Zapisy pro spravu zapsanych predmetu
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
	std::shared_ptr<Student> student;
	std::shared_ptr<Predmet> predmet;
	Znamka znamka;

	public:
	Zapis(const std::shared_ptr<Student> student,
		const std::shared_ptr<Predmet> predmet, Znamka znamka);
	const std::shared_ptr<Student> VratStudenta() const;
	const std::shared_ptr<Predmet> VratPredmet() const;
	Znamka VratZnamku() const;
	void NastavZnamku(const Znamka znamka);
	bool JeStudenta(const std::shared_ptr<Student> student);
	bool JePredmetu(const std::shared_ptr<Predmet> predmet);
};

} /* data:: */
