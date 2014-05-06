/*
 * databaze.h: definice tridy Databaze
 */

#include "databaze.h"
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace data;


// Porovna dve promenne typu retezec bez ohledu na velikost pismen
bool Databaze::PorovnejString(const std::string& l, const std::string &p)
	const {
	// Retezce musi mit stejnou delku
	return l.size() == p.size()
		// Funkce equal porovnava dva rozsahy vytycene iteratory pomoci
		// dodaneho predikatu
		&& std::equal(begin(l), end(l), begin(p),
			// Lambda vyraz pro urceni zda jsou elemnty shodne nebo ne
			// porovnavame "zmensene" verze znaku z leve a prave strany
			[](std::string::value_type lz, std::string::value_type pz) {
				return std::tolower(lz) == std::tolower(pz);
			});
}

// Vytvori noveho studenta
void Databaze::VytvorStudenta(std::string jmeno, std::string prijmeni,
	unsigned int rocnik) {
	// Vygenerovat nove id
	unsigned int id = 0;
	for(auto student : this->studenti)
		if(student->VratId() > id)
			id = student->VratId();

	auto student = std::make_shared<Student>(++id, jmeno, prijmeni, rocnik);
	this->studenti.push_back(student);
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
const std::vector<std::shared_ptr<Student>> Databaze::SeznamStudentu() const {
	return this->studenti;
}

// Najde studenty dle zadaneho kriteria a dotazu. Metoda neni citliva na
// velikost pismen
const std::vector<std::shared_ptr<Student>> Databaze::NajdiStudenta(
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
const std::vector<std::shared_ptr<Zapis>> Databaze::VratZapisy(
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
void Databaze::VytvorPredmet(std::string nazev) {
	// Vygenerovat nove id
	unsigned int id = 0;
	for(auto predmet : this->predmety)
		if(predmet->VratId() > id)
			id = predmet->VratId();

	auto predmet = std::make_shared<Predmet>(++id, nazev);
	this->predmety.push_back(predmet);
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
const std::vector<std::shared_ptr<Predmet>> Databaze::SeznamPredmetu() const {
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

// Najde predmety dle zadaneho kriteria a dotazu. Metoda neni citliva na
// velikost pismen.
const std::vector<std::shared_ptr<Predmet>> Databaze::NajdiPredmet(
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

// Zrusi zapis ktery vyhovuje prislusnosti studentovi, predmetu nebo obojimu
void Databaze::ZrusZapis(std::shared_ptr<Student> student,
	std::shared_ptr<Predmet> predmet) {

	if(student == nullptr && predmet == nullptr)
		return;

	// Pouzijeme rovnou iterator abychom mohli rovnou mazat
	for(auto zapis_it = begin(this->zapisy); zapis_it != end(this->zapisy); ) {

		if((student == nullptr && (*zapis_it)->JePredmetu(predmet))
			|| (predmet == nullptr && (*zapis_it)->JeStudenta(student))
			|| ((*zapis_it)->JePredmetu(predmet)
				&& (*zapis_it)->JeStudenta(student))) {
			zapis_it = this->zapisy.erase(zapis_it);
		} else {
			++zapis_it;
		}
	}
}
