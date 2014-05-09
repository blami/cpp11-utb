/*
 * serializace.cpp: definice tridy Serializace
 */

#include <sstream>
#include "serializace.h"
#include "znamka.h"

using namespace data;


// Serializuje objekt typu Student do JSON
json::Object Serializace::SerializujStudent(
	std::shared_ptr<Student> student) {

	json::Object json;
	if(student == nullptr)
		return json;

	// SuperEasyJSON nema typ hodnoty unsigned int, proto musime provest
	// explicitni konverzi na int
	json["ID"] = (int)student->VratId();
	json["Jmeno"] = student->VratJmeno();
	json["Prijmeni"] = student->VratPrijmeni();
	json["Rocnik"] = (int)student->VratRocnik();

	return json;
}

// Serializuje objekt typu Predmet do JSON
json::Object Serializace::SerializujPredmet(
	std::shared_ptr<Predmet> predmet) {

	json::Object json;
	if(predmet == nullptr)
		return json;

	// SuperEasyJSON nema typ hodnoty unsigned int, proto musime provest
	// explicitni konverzi na int
	json["ID"] = (int)predmet->VratId();
	json["Nazev"] = predmet->VratNazev();

	return json;
}

// Serializuje objekt typu Zapis do JSON
json::Object Serializace::SerializujZapis(
	std::shared_ptr<Zapis> zapis) {

	json::Object json;
	if(zapis == nullptr)
		return json;

	// Nase implementace nepodporuje ID zapisu
	// SuperEasyJSON nema typ hodnoty unsigned int, proto musime provest
	// explicitni konverzi na int
	json["ID_Student"] = (int)zapis->VratStudenta()->VratId();
	json["ID_Predmet"] = (int)zapis->VratPredmet()->VratId();
	json["Znamka"] = ZnamkaString(zapis->VratZnamku());

	return json;
}

// Deserializuje objekt typu Student z JSON
std::shared_ptr<Student> Serializace::DeserializujStudent(
	const json::Value json) {

	// Overime ze objekt ma veskere atributy pro rekonstrukci a pokud ne,
	// vratime nullptr
	if(!(json.HasKey("ID") && json["ID"].GetType() == json::ValueType::IntVal)
		|| !(json.HasKey("Jmeno") &&
			json["Jmeno"].GetType() == json::ValueType::StringVal)
		|| !(json.HasKey("Prijmeni") &&
			json["Prijmeni"].GetType() == json::ValueType::StringVal)
		|| !(json.HasKey("Rocnik") &&
			json["Rocnik"].GetType() == json::ValueType::IntVal))
		return nullptr;

	// Z duvodu omezeni knihovny SuperEasyJSON predpokladame ze celociselne
	// hodnoty jsou bezznaminkove
	auto student = std::make_shared<Student>((int)json["ID"],
		json["Jmeno"], json["Prijmeni"], (int)json["Rocnik"]);

	return student;
}

// Deserializuje objekt typu Predmet z JSON
std::shared_ptr<Predmet> Serializace::DeserializujPredmet(
	const json::Value json) {

	// Overime ze objekt ma veskere atributy pro rekonstrukci a pokud ne,
	// vratime nullptr
	if(!(json.HasKey("ID") && json["ID"].GetType() == json::ValueType::IntVal)
		|| !(json.HasKey("Nazev")
			&& json["Nazev"].GetType() == json::ValueType::StringVal))
		return nullptr;

	// Z duvodu omezeni knihovny SuperEasyJSON predpokladame ze celociselne
	// hodnoty jsou bezznaminkove
	std::shared_ptr<Predmet> predmet = std::make_shared<Predmet>(
		(int)json["ID"], json["Nazev"]);

	return predmet;
}

// Deserializuje objekt typu zapis z JSON Metoda pro deserializaci zapisu
// vyzaduje pro vytvoreni zapisu databazi k ziskani referenci dle ID
std::shared_ptr<Zapis> Serializace::DeserializujZapis(const json::Value json,
	const Databaze& databaze) {

	// Overime ze objekt ma veskere atributy pro rekonstrukci a pokud ne,
	// vratime nullptr
	if(!(json.HasKey("ID_Student")
			&& json["ID_Student"].GetType() == json::ValueType::IntVal)
		|| !(json.HasKey("ID_Predmet")
			&& json["ID_Predmet"].GetType() == json::ValueType::IntVal)
		|| !(json.HasKey("Znamka")
			&& json["Znamka"].GetType() == json::ValueType::StringVal))
		return nullptr;
	// ID zapisu v nasi implementaci nepouzivame

	auto znamka = StringZnamka(json["Znamka"]);

	// Nyni z dodane databaze zjistime Id studenta a predmetu pro vytvoreni
	// vazby. Pokud jedno z toho neexistuje vratime nullptr (vazba je
	// nerealizovatelna)
	std::stringstream ss;
	ss << (int)json["ID_Student"];
	auto student = databaze.NajdiStudenta(StudentKriterium::ID, ss.str());
	ss.str(""); // Vycistit stringstream aby se nam neslepily ID dohromady
	ss << (int)json["ID_Predmet"];
	auto predmet = databaze.NajdiPredmet(PredmetKriterium::ID, ss.str());

	if(student.size() != 1 || predmet.size() != 1)
		return nullptr;

	// Zde by bylo mozne volat rovnou databaze.ZapisPredmet() coz ale porusuje
	// r/o pouziti atributu a tvori odlisnou semantiku nez maji ostatni
	// deserializacni funkce. Proto proste jednoduse vratime objekt Zapis

	auto zapis = std::make_shared<Zapis>(student[0], predmet[0], znamka);
	return zapis;
}
