/*
 * databaze.h: definice tridy Databaze
 */

#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>
#include "databaze.h"
#include "serializace.h"

using namespace data;


// Vymaze celou databazi
void Databaze::VymazDatabazi() {
	this->studenti.clear();
	this->predmety.clear();
	this->zapisy.clear();
}

// Porovna dve promenne typu retezec bez ohledu na velikost pismen
bool Databaze::PorovnejString(const std::string& l, const std::string &p)
	const {
	// Retezce musi mit stejnou delku
	return l.size() == p.size()
		// Funkce equal porovnava dva rozsahy vytycene iteratory pomoci
		// predikatu
		&& std::equal(begin(l), end(l), begin(p),
			// Lambda vyraz pro urceni zda jsou elemnty shodne nebo ne
			// porovnavame "zmensene" verze znaku z leve a prave strany
			[](std::string::value_type lz, std::string::value_type pz) {
				return std::tolower(lz) == std::tolower(pz);
			});
}

// Vytvori noveho studenta
std::shared_ptr<Student> Databaze::VytvorStudenta(std::string jmeno,
	std::string prijmeni, unsigned int rocnik) {
	// Vygenerovat nove id
	unsigned int id = 0;
	for(auto student : this->studenti)
		if(student->VratId() > id)
			id = student->VratId();

	auto student = std::make_shared<Student>(++id, jmeno, prijmeni, rocnik);
	this->studenti.push_back(student);

	return student;
}

// Smaze studenta a jeho zapisy
void Databaze::SmazStudenta(std::shared_ptr<Student> student) {
	// Najdeme predmet, pokud student neexistuje nic se nestane
	auto pozice = std::find(begin(this->studenti), end(this->studenti),
		student);
	if(pozice == end(this->studenti))
		return;

	// Zrusime vsechny zapisy studenta
	this->ZrusZapis(student, nullptr);

	// Smazeme samotneho studenta
	this->studenti.erase(pozice);

}

// Vrati seznam vsech studentu
std::vector<std::shared_ptr<Student>> Databaze::SeznamStudentu() const {
	return this->studenti;
}

// Najde studenty dle zadaneho kriteria a dotazu. Metoda neni citliva na
// velikost pismen
std::vector<std::shared_ptr<Student>> Databaze::NajdiStudenta(
	StudentKriterium kriterium, std::string dotaz) const {

	std::vector<std::shared_ptr<Student>> vysledek;

	switch(kriterium) {
	case StudentKriterium::ID:
		unsigned int id;
		// Pokud se nepodari prevest dotaz na cislo, vratime pouze prazdny
		// vektor
		if (!(std::stringstream(dotaz) >> id))
			return vysledek;

		for(auto student : this->studenti) {
			if(student->VratId() == id)
				vysledek.push_back(student);
		}
		break;
	case StudentKriterium::JMENO:
		for(auto student : this->studenti) {
			if(this->PorovnejString(student->VratJmeno(), dotaz))
				vysledek.push_back(student);
		}
		break;
	case StudentKriterium::PRIJMENI:
		for(auto student : this->studenti) {
			if(this->PorovnejString(student->VratPrijmeni(), dotaz))
				vysledek.push_back(student);
		}
		break;
	}

	return vysledek;
}

// Zapise predmet studentovi
void Databaze::ZapisPredmet(std::shared_ptr<Student> student,
	std::shared_ptr<Predmet> predmet, Znamka znamka) {
	// Overime ze student a predmet nejsou null
	if(student == nullptr || predmet == nullptr)
		return;
	// Overime ze predmet a student jsou opravdu v databazi
	if((std::find(begin(this->studenti), end(this->studenti), student) ==
		end(this->studenti)) ||
		(std::find(begin(this->predmety), end(this->predmety), predmet) ==
		end(this->predmety)))
		return;

	// Pokud takovy zapis jiz existuje pouze upravime znamku
	for(auto zapis : this->zapisy) {
		if(zapis->JeStudenta(student) && zapis->JePredmetu(predmet)) {
			zapis->NastavZnamku(znamka);
			return;
		}
	}

	// Jinak vytvorime novy zapis
	auto zapis = std::make_shared<Zapis>(student, predmet, znamka);
	this->zapisy.push_back(zapis);
}

// Vrati seznam zapsanych predmetu studenta
std::vector<std::shared_ptr<Zapis>> Databaze::VratZapisy(
	std::shared_ptr<Student> student) const {
	std::vector<std::shared_ptr<Zapis>> zapisy;

	// Nemusime overovat ze student je studentem, protoze kdyz neni, nebude mit
	// zapsany zadne predmety
	for(auto zapis : this->zapisy) {
		if(zapis->JeStudenta(student))
			zapisy.push_back(zapis);
	}

	return zapisy;
}

// Spocte aritmeticky prumer ze znamek (krome F) studenta
float Databaze::SpoctiPrumer(std::shared_ptr<Student> student) const {
	float soucet = 0;
	int pocet = 0;

	for(auto zapis : this->zapisy) {
		// Preskocime zapisy jinych studentu
		if(!zapis->JeStudenta(student))
			continue;

		// F se nezapocitavaji do prumeru
		if(zapis->VratZnamku() != Znamka::F) {
			pocet++;
			soucet += (int)zapis->VratZnamku();
		}
	}

	if(pocet)
		// Soucet znamek vydelime 10 abychom ziskali skutecnou hodnotu (viz.
		// poznamka v souboru znamka.h
		return (soucet / 10) / pocet;
	else
		return 0;
}

// Vytvori novy predmet
std::shared_ptr<Predmet> Databaze::VytvorPredmet(std::string nazev) {
	// Vygenerovat nove id
	unsigned int id = 0;
	for(auto predmet : this->predmety)
		if(predmet->VratId() > id)
			id = predmet->VratId();

	auto predmet = std::make_shared<Predmet>(++id, nazev);
	this->predmety.push_back(predmet);

	return predmet;
}

// Smaze predmet a jeho zapisy
void Databaze::SmazPredmet(std::shared_ptr<Predmet> predmet) {
	// Najdeme predmet, pokud predmet neexistuje nic se nestane
	auto pozice = std::find(begin(this->predmety), end(this->predmety),
		predmet);
	if(pozice == end(this->predmety))
		return;

	// Zrusime vsechny zapisy predmetu
	this->ZrusZapis(nullptr, predmet);

	// Smazeme samotny predmet
	this->predmety.erase(pozice);
}

// Vrati seznam vsech predmetu
std::vector<std::shared_ptr<Predmet>> Databaze::SeznamPredmetu() const {
	return this->predmety;
}

// Vrati pocet unikatnich studentu zapsanych na predmet
unsigned int Databaze::VratPocetZapsanychStudentu(
	std::shared_ptr<Predmet> predmet) const {
	unsigned int pocet = 0;

	// Nemuze nastat situace ze jeden student by mel predmet zapsan vicekrat
	for(auto zapis : this->zapisy) {
		if(zapis->JePredmetu(predmet))
			pocet++;
	}

	return pocet;
}

// Vrati zapisy predmetu
std::vector<std::shared_ptr<Zapis>> Databaze::VratZapisy(
	std::shared_ptr<Predmet> predmet) const {
	std::vector<std::shared_ptr<Zapis>> zapisy;

	// Nemusime overovat ze student je studentem, protoze kdyz neni, nebude mit
	// zapsany zadne predmety
	for(auto zapis : this->zapisy) {
		if(zapis->JePredmetu(predmet))
			zapisy.push_back(zapis);
	}

	return zapisy;
}


// Najde predmety dle zadaneho kriteria a dotazu. Metoda neni citliva na
// velikost pismen.
std::vector<std::shared_ptr<Predmet>> Databaze::NajdiPredmet(
	PredmetKriterium kriterium, std::string dotaz) const {

	std::vector<std::shared_ptr<Predmet>> vysledek;

	switch(kriterium) {
	case PredmetKriterium::ID:
		unsigned int id;
		// Pokud se nepodari prevest dotaz na cislo, vratime pouze prazdny
		// vektor
		if (!(std::stringstream(dotaz) >> id))
			return vysledek;

		for(auto predmet : this->predmety) {
			if(predmet->VratId() == id)
				vysledek.push_back(predmet);
		}
		break;
	case PredmetKriterium::NAZEV:
		for(auto predmet : this->predmety) {
			if(this->PorovnejString(predmet->VratNazev(), dotaz))
				vysledek.push_back(predmet);
		}
		break;
	}

	return vysledek;
}

// Zrusi zapis ktery vyhovuje prislusnosti studentovi, predmetu nebo obojimu.
// Vraci pocet zrusenych zapisu.
unsigned int Databaze::ZrusZapis(std::shared_ptr<Student> student,
	std::shared_ptr<Predmet> predmet) {
	unsigned int zruseno = 0;

	if(student == nullptr && predmet == nullptr)
		return false;

	// Pouzijeme rovnou iterator abychom mohli rovnou mazat
	for(auto zapis_it = begin(this->zapisy); zapis_it != end(this->zapisy); ) {

		if((student == nullptr && (*zapis_it)->JePredmetu(predmet))
			|| (predmet == nullptr && (*zapis_it)->JeStudenta(student))
			|| ((*zapis_it)->JePredmetu(predmet)
				&& (*zapis_it)->JeStudenta(student))) {
			zapis_it = this->zapisy.erase(zapis_it);
			zruseno++;
		} else {
			++zapis_it;
		}
	}

	return zruseno;
}

// Nacte databazi z JSON souboru
bool Databaze::NactiSoubor(const std::string nazev) {
	std::string obsah = "";
	Serializace s;

	// Nacist soubor
	std::ifstream soubor(nazev);
	std::stringstream ss;
	if(!soubor)
		return false;
	ss << soubor.rdbuf();
	obsah = ss.str();

	// Vymazat databazi
	this->VymazDatabazi();

	json::Value json = json::Deserialize(obsah);

	// Deserializovat objekty typu Student
	if(json.HasKey("Studenti") &&
		json["Studenti"].GetType() == json::ValueType::ArrayVal) {
		for(auto i : (json::Array)json["Studenti"]) {
			std::shared_ptr<Student> student = s.DeserializujStudent(i);
			if(student != nullptr) {
				this->studenti.push_back(student);
			}
		}
	}

	// Deserializovat objekty typu Predmet
	if(json.HasKey("Predmety") &&
		json["Predmety"].GetType() == json::ValueType::ArrayVal) {
		for(auto i : (json::Array)json["Predmety"]) {
			std::shared_ptr<Predmet> predmet = s.DeserializujPredmet(i);
			if(predmet != nullptr) {
				this->predmety.push_back(predmet);
			}
		}
	}

	// Deserializovat objekty typu Zapis
	if(json.HasKey("ZapsanePredmety") &&
		json["ZapsanePredmety"].GetType() == json::ValueType::ArrayVal) {
		for(auto i : (json::Array)json["ZapsanePredmety"]) {
			std::shared_ptr<Zapis> zapis = s.DeserializujZapis(i, *this);
			if(zapis != nullptr) {
				this->zapisy.push_back(zapis);
			}
		}
	}

	return true;
}

// Ulozi databazi do JSON souboru
bool Databaze::UlozSoubor(const std::string nazev) {
	json::Object json;
	json::Array studenti;
	json::Array predmety;
	json::Array zapisy;
	Serializace s;

	std::ofstream soubor(nazev);
	if(!soubor)
		return false;

	// Serializovat studenty
	for(auto i : this->studenti)
		studenti.push_back(s.SerializujStudent(i));

	// Serializovat predmety
	for(auto i : this->predmety)
		predmety.push_back(s.SerializujPredmet(i));

	// Serializovat zapisy
	for(auto i : this->zapisy)
		zapisy.push_back(s.SerializujZapis(i));

	json["Predmety"] = predmety;
	json["Studenti"] = studenti;
	json["ZapsanePredmety"] = zapisy;

	// Vlozit do souboru
	soubor << json::Serialize(json);
	soubor.close();

	return true;
}
