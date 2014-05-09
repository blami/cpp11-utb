/*
 * serializace.h: deklarace tridy Serializace
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "student.h"
#include "predmet.h"
#include "zapis.h"
#include "databaze.h"
#include "json.h"

namespace data {

// Pomocna trida pro serializaci databazovych objektu do JSON
class Serializace {
	public:
	json::Object SerializujStudent(const std::shared_ptr<Student> student);
	json::Object SerializujPredmet(const std::shared_ptr<Predmet> predmet);
	json::Object SerializujZapis(const std::shared_ptr<Zapis> zapis);
	std::shared_ptr<Student> DeserializujStudent(const json::Value json);
	std::shared_ptr<Predmet> DeserializujPredmet(const json::Value json);
	// Metoda pro deserializaci zapisu vyzaduje potrebuje pro vytvoreni vazby
	// referenci na databazi
	std::shared_ptr<Zapis> DeserializujZapis(const json::Value json,
		const Databaze& databaze);
};

} /* data:: */
