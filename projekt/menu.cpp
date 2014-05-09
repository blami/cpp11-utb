/*
 * menu.cpp: definice tridy Menu
 */

#include "menu.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <sstream>

using namespace menu;

// Konstruktor
Menu::Menu(std::shared_ptr<data::Databaze> databaze) :
	databaze { databaze } {
}

// Pomocna metoda pro nacteni nezaporneho cisla
unsigned int Menu::NactiCislo(const std::string zprava) {
	unsigned int vstup;

	do {
		std::cout << zprava << ": ";
		std::cin >> vstup;
		if(std::cin.fail()) {
			std::cerr << "CHYBA: neplatny vstup!" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		} else {
			break;
		}
	} while(true); // Cyklus ridime pomoci break;

	return vstup;
}

// Pomocna metoda pro nacteni cisla jako string
std::string Menu::NactiCisloString(const std::string zprava) {
	unsigned int cislo = this->NactiCislo(zprava);
	std::stringstream vstup;
	vstup << cislo;

	return vstup.str();
}

// Pomocna metoda pro nacteni retezce
std::string Menu::NactiString(const std::string zprava) {
	std::string vstup;

	do {
		std::cout << zprava << ": ";
		std::cin >> vstup;
		if(std::cin.fail()) {
			std::cerr << "CHYBA: neplatny vstup!" << std::endl;
			std::cin.clear();
		} else {
			break;
		}
	} while(true); // Cyklus ridime pomoci break;

	return vstup;
}

// Pomocna metoda pro nacteni Znamky A-F
data::Znamka Menu::NactiZnamku(const std::string zprava) {
	data::Znamka znamka;
	std::string vstup;

	do {
		std::cout << zprava << " (A-F): ";
		std::cin >> vstup;
		// U znamky je jeste nutne overit ze je z rozsahu a-fA-F
		if(std::cin.fail()
			|| (vstup.find_first_not_of("abcdefABCDEF") != std::string::npos)) {
			std::cerr << "CHYBA: neplatny vstup!" << std::endl;
			std::cin.clear();
		} else {
			break;
		}
	} while(true); // Cyklus ridime pomoci break;

	znamka = StringZnamka(vstup);
	return znamka;
}

// Hlavni nabidka
void Menu::HlavniNabidka() {
	bool konec = false;

	while(!konec) {
		std::cout << std::endl << "*** Hlavni nabidka ***" << std::endl
			<< "1-Nacist databazi" << std::endl
			<< "2-Ulozit databazi" << std::endl
			<< "3-Zobrazit seznam studentu" << std::endl
			<< "4-Zobrazit seznam predmetu" << std::endl
			<< "5-Vytvorit studenta" << std::endl
			<< "6-Vytvorit predmet" << std::endl
			<< "7-Vyhledat studenta" << std::endl
			<< "8-Vyhledat predmet" << std::endl
			<< "0-Konec" << std::endl;
		unsigned int volba = this->NactiCislo("Volba");
		switch(volba) {
			case 1:
				this->NacistDatabaziNabidka();
				break;
			case 2:
				this->UlozitDatabaziNabidka();
				break;
			case 3:
				this->SeznamStudentuVypis("Seznam vsech studentu",
					this->databaze->SeznamStudentu());
				break;
			case 4:
				this->SeznamPredmetuVypis("Seznam vsech predmetu",
					this->databaze->SeznamPredmetu());
				break;
			case 5:
				this->VytvoritStudentaNabidka();
				break;
			case 6:
				this->VytvoritPredmetNabidka();
				break;
			case 7:
				this->VyhledatStudentaNabidka(false);
				break;
			case 8:
				this->VyhledatPredmetNabidka(false);
				break;
			case 0:
				konec = true;
				break;
			default:
				std::cerr << "CHYBA: neplatna volba!" << std::endl;
		}
	}
}

// Nabidka nacteni databaze
void Menu::NacistDatabaziNabidka() {
	std::string nazev;
	nazev = this->NactiString("Cesta k nacitanemu souboru");

	if(this->databaze->NactiSoubor(nazev))
		std::cout << "Databaze uspesne nactena" << std::endl;
	else
		std::cerr << "CHYBA: nelze nacist databazi!" << std::endl;
}

// Nabidka ulozeni databaze
void Menu::UlozitDatabaziNabidka() {
	std::string nazev;
	nazev = this->NactiString("Cesta k ukladanemu souboru");

	if(this->databaze->UlozSoubor(nazev))
		std::cout << "Databaze uspesne ulozena" << std::endl;
	else
		std::cerr << "CHYBA: nelze ulozit databazi!" << std::endl;
}

// Nabidka vytvoreni studenta
void Menu::VytvoritStudentaNabidka() {
	std::string jmeno, prijmeni;
	unsigned int rocnik;

	jmeno = this->NactiString("Zadejte jmeno");
	prijmeni = this->NactiString("Zadejte prijmeni");
	rocnik = this->NactiCislo("Zadejte rocnik");

	auto student = this->databaze->VytvorStudenta(jmeno, prijmeni, rocnik);
	std::cout << "Student vytvoren s ID: "
		<< student->VratId()
		<< std::endl;

	// Volby studenta
	this->StudentNabidka(student);
}

// Nabidka vytvoreni predmetu
void Menu::VytvoritPredmetNabidka() {
	std::string nazev;

	nazev = this->NactiString("Zadejte nazev");

	auto predmet = this->databaze->VytvorPredmet(nazev);
	std::cout << "Predmet vytvoren s ID: "
		<< predmet->VratId()
		<< std::endl;

	// Volby predmetu
	this->PredmetNabidka(predmet);
}

// Nabidka studenta
void Menu::StudentNabidka(const std::shared_ptr<data::Student>& student) {
	bool zpet = false;
	std::string aktualizace;
	unsigned int aktualizace_rocnik;
	this->StudentVypis(student);

	while(!zpet) {
		std::cout << std::endl << "*** Volby studenta ***" << std::endl
			<< "1-Zapsat predmet" << std::endl
			<< "2-Odepsat predmet" << std::endl
			<< "3-Aktualizovat jmeno" << std::endl
			<< "4-Aktualizovat prijmeni" << std::endl
			<< "5-Aktualizovat rocnik" << std::endl
			<< "6-Znamkovat" << std::endl
			<< "7-Vypsat informace" << std::endl
			<< "8-Smazat" << std::endl
			<< "0-Zpet" << std::endl;
		unsigned int volba = this->NactiCislo("Volba");
		switch(volba) {
			case 0:
				zpet = true;
				break;
			case 1:
				this->ZapsatPredmetNabidka(student);
				break;
			case 2:
				this->OdepsatPredmetNabidka(student);
				break;
			case 3:
				aktualizace = this->NactiString("Nove jmeno");
				student->NastavJmeno(aktualizace);
				break;
			case 4:
				aktualizace = this->NactiString("Nove prijmeni");
				student->NastavPrijmeni(aktualizace);
				break;
			case 5:
				aktualizace_rocnik = this->NactiCislo("Novy rocnik");
				student->NastavRocnik(aktualizace_rocnik);
				break;
			case 6:
				this->ZnamkovatNabidka(student);
				break;
			case 7:
				this->StudentVypis(student);
				break;
			case 8:
				this->databaze->SmazStudenta(student);
				std::cout << "Student byl smazan" << std::endl;
				// Vratime se do hlavni nabidky (zanikne posledni reference z
				// kontextu teto metody
				zpet = true;
				break;
			default:
				std::cerr << "CHYBA: neplatna volba!" << std::endl;
		}
	}
}

// Nabidka predmetu
void Menu::PredmetNabidka(const std::shared_ptr<data::Predmet>& predmet) {
	bool zpet = false;
	std::string aktualizace;
	auto zapisy = this->databaze->VratZapisy(predmet);

	this->PredmetVypis(predmet);

	while(!zpet) {
		std::cout << std::endl << "*** Volby predmetu ***" << std::endl
			<< "1-Aktualizovat nazev" << std::endl
			<< "2-Vypsat informace" << std::endl
			<< "3-Smazat" << std::endl
			<< "0-Zpet" << std::endl;
		unsigned int volba = this->NactiCislo("Volba");
		switch(volba) {
			case 0:
				zpet = true;
				break;
			case 1:
				aktualizace = this->NactiString("Novy nazev");
				predmet->NastavNazev(aktualizace);
				break;
			case 2:
				this->PredmetVypis(predmet);
				break;
			case 3:
				if(zapisy.size() == 0) {
					this->databaze->SmazPredmet(predmet);
					// Vratime se do hlavni nabidky (zanikne posledni reference
					// z kontextu teto metody
					std::cout << "Predmet byl smazan" << std::endl;
					zpet = true;
				} else {
					std::cerr << "CHYBA: nelze smazat predmet se zapisy!"
						<< std::endl;
				}
				break;
			default:
				std::cerr << "CHYBA: neplatna volba!" << std::endl;
		}
	}
}

// Nabidka pro vyhledani studenta
void Menu::VyhledatStudentaNabidka(bool dle_id) {
	std::vector<std::shared_ptr<data::Student>> vysledek;
	std::string dotaz;

	unsigned int volba = 1;
	if(!dle_id) {
		std::cout << "Vyhledat studenta dle:" << std::endl
			<< "1-ID" << std::endl
			<< "2-Jmena" << std::endl
			<< "3-Prijmeni" << std::endl;
		volba = this->NactiCislo("Volba");
	}
	switch(volba) {
		case 1:
			dotaz = this->NactiCisloString("ID");
			vysledek = this->databaze->NajdiStudenta(
				data::StudentKriterium::ID, dotaz);
			break;
		case 2:
			dotaz = this->NactiString("Jmeno");
			vysledek = this->databaze->NajdiStudenta(
				data::StudentKriterium::JMENO, dotaz);
			break;
		case 3:
			dotaz = this->NactiString("Prijmeni");
			vysledek = this->databaze->NajdiStudenta(
				data::StudentKriterium::PRIJMENI, dotaz);
			break;
		default:
			std::cerr << "CHYBA: neplatna volba!" << std::endl;
			return;
	}

	// Pokud je vysledek prave jeden, prejdeme na volby studenta
	if(vysledek.size() == 1) {
		this->StudentNabidka(vysledek[0]);
	// Pokud je vysledku 0 nebo vice nez jeden, vypiseme seznam. V pripade ze
	// je vysledku vice nez jeden volime dle ID
	} else {
		this->SeznamStudentuVypis("Nalezeni studenti", vysledek);
		if(vysledek.size() > 1) {
			this->VyhledatStudentaNabidka(true);
		}
	}
}

// Nabidka pro vyhledani predmetu
void Menu::VyhledatPredmetNabidka(bool dle_id) {
	std::vector<std::shared_ptr<data::Predmet>> vysledek;
	std::string dotaz;

	unsigned int volba = 1;
	if(!dle_id) {
		std::cout << std::endl << "Vyhledat predmet dle: " << std::endl
			<< "1-ID" << std::endl
			<< "2-Nazev" << std::endl;
		volba = this->NactiCislo("Volba");
	}
	switch(volba) {
		case 1:
			dotaz = this->NactiCisloString("ID");
			vysledek = this->databaze->NajdiPredmet(
				data::PredmetKriterium::ID, dotaz);
			break;
		case 2:
			dotaz = this->NactiString("Nazev");
			vysledek = this->databaze->NajdiPredmet(
				data::PredmetKriterium::NAZEV, dotaz);
			break;
		default:
			std::cerr << "CHYBA: neplatna volba!" << std::endl;
			return;
	}

	// Pokud je vysledek prave jeden, prejdeme na volby predmetu
	if(vysledek.size() == 1) {
		this->PredmetNabidka(vysledek[0]);
	// Pokud je vysledku 0 nebo vice nez jeden, vypiseme seznam. V pripade ze
	// je vysledku vice nez jeden volime dle ID
	} else {
		this->SeznamPredmetuVypis("Nalezene predmety", vysledek);
		if(vysledek.size() > 1) {
			this->VyhledatPredmetNabidka(true);
		}
	}
}

// Nabidka pro zapsani predmetu
void Menu::ZapsatPredmetNabidka(
	const std::shared_ptr<data::Student>& student) {

	this->SeznamPredmetuVypis("Dostupne predmety",
		this->databaze->SeznamPredmetu());
	std::string id = this->NactiCisloString("ID predmetu");

	auto predmet = this->databaze->NajdiPredmet(data::PredmetKriterium::ID,
		id);
	if(predmet.size() == 1) {
		// Zkontrolujeme ze predmet uz neni zapsan
		for(auto zapis : this->databaze->VratZapisy(student)) {
			if(zapis->JePredmetu(predmet[0])) {
				std::cerr << "CHYBA: predmet je jiz zapsan!" << std::endl;
				return;
			}
		}
		// Zapiseme predmet s vychozi znamkou F
		this->databaze->ZapisPredmet(student, predmet[0], data::Znamka::F);
		std::cout << "Predmet byl zapsan" << std::endl;
	} else {
		std::cerr << "CHYBA: neplatne ID predmetu!" << std::endl;
	}
}

// Nabidka pro odepsani predmetu
void Menu::OdepsatPredmetNabidka(
	const std::shared_ptr<data::Student>& student) {
	std::stringstream id_string;

	// Odepsat lze pouze zapsane predmety
	auto zapisy = this->databaze->VratZapisy(student);
	if(zapisy.size() < 1) {
		std::cout << "Nejsou zapsany zadne predmety" << std::endl;
		return;
	}

	// Nabidneme zapsane predmety
	std::cout << "Zapsane predmety:" << std::endl;
	for(auto zapis : zapisy) {
		std::cout << std::setw(2) << zapis->VratPredmet()->VratId() << ". "
			<< zapis->VratPredmet()->VratNazev() << std::endl;
	}
	bool hotovo = false;
	while(!hotovo) {
		unsigned int id = this->NactiCislo("ID zapsaneho predmetu");
		for(auto zapis : zapisy)
			if(zapis->VratPredmet()->VratId() == id) {
				this->databaze->ZrusZapis(student, zapis->VratPredmet());
				hotovo = true;
				break;
			}
		if(!hotovo)
			std::cerr << "CHYBA: tento predmet neni zapsan!" << std::endl;
	}
	std::cout << "Predmet byl odepsan" << std::endl;

}


// Nabidka pro znamkovani predmetu
void Menu::ZnamkovatNabidka(
	const std::shared_ptr<data::Student>& student) {
	std::stringstream id_string;

	// Znamkovat lze pouze zapsane predmety
	auto zapisy = this->databaze->VratZapisy(student);
	if(zapisy.size() < 1) {
		std::cout << "Nejsou zapsany zadne predmety" << std::endl;
		return;
	}

	// Nabidneme zapsane predmety
	std::cout << "Zapsane predmety:" << std::endl;
	for(auto zapis : zapisy) {
		std::cout << std::setw(2) << zapis->VratPredmet()->VratId() << ". "
			<< zapis->VratPredmet()->VratNazev() << std::endl;
	}
	bool hotovo = false;
	while(!hotovo) {
		unsigned int id = this->NactiCislo("ID zapsaneho predmetu");
		for(auto zapis : zapisy)
			if(zapis->VratPredmet()->VratId() == id) {
				auto znamka = this->NactiZnamku("Znamka");
				zapis->NastavZnamku(znamka);
				hotovo = true;
				break;
			}
		if(!hotovo)
			std::cerr << "CHYBA: tento predmet neni zapsan!" << std::endl;
	}
	std::cout << "Znamka byla udelena" << std::endl;
}

// Vypis seznamu studentu
void Menu::SeznamStudentuVypis(const std::string titulek,
	const std::vector<std::shared_ptr<data::Student>>& seznam) {
	std::cout << std::endl << "*** " << titulek << " ***" << std::endl;

	for(auto s : seznam) {
		std::cout << std::setw(4) << s->VratId() << ". "
			<< s->VratJmeno() << " " << s->VratPrijmeni() << "\t"
			<< "rocnik: " << std::setw(2) << s->VratRocnik() << "\t"
			<< "prumer: " << std::setprecision(2) << std::fixed
			<< this->databaze->SpoctiPrumer(s)
			<< std::endl;
	}
	std::cout << "Celkem studentu: " << seznam.size() << std::endl;
}

// Vypis seznamu predmetu
void Menu::SeznamPredmetuVypis(const std::string titulek,
	const std::vector<std::shared_ptr<data::Predmet>>& seznam) {
	std::cout << std::endl << "*** " << titulek << " ***" << std::endl;

	for(auto p : seznam) {
		std::cout << std::setw(4) << p->VratId() << ". "
			<< p->VratNazev() << "\tzapsano:"
			<< this->databaze->VratPocetZapsanychStudentu(p)
			<< std::endl;
	}
	std::cout << "Celkem predmetu: " << seznam.size() << std::endl;
}

// Vypis studenta
void Menu::StudentVypis(const std::shared_ptr<data::Student>& student) {
	std::cout << std::endl << "*** Student "
		<< student->VratJmeno() << " "
		<< student->VratPrijmeni()
		<< " ***" << std::endl;

	std::cout << "ID: " << student->VratId() << std::endl;
	std::cout << "rocnik: " << student->VratRocnik() << std::endl;
	std::cout << "prumer: " << std::setprecision(2) << std::fixed
		<< this->databaze->SpoctiPrumer(student) << std::endl;

	std::cout << "Zapsane predmety:" << std::endl;
	for(auto zapis : this->databaze->VratZapisy(student)) {
		std::cout << std::setw(2) << zapis->VratPredmet()->VratId() << ". "
			<< zapis->VratPredmet()->VratNazev() << "\t"
			<< zapis->VratZnamkuString() << std::endl;
	}
}

// Vypis predmetu
void Menu::PredmetVypis(const std::shared_ptr<data::Predmet>& predmet) {
	std::cout << std::endl << "*** Predmet "
		<< predmet->VratNazev() << " "
		<< " ***" << std::endl;

	std::cout << "ID: " << predmet->VratId() << std::endl;

	std::cout << "Zapsani studenti:" << std::endl;
	for(auto zapis : this->databaze->VratZapisy(predmet)) {
		std::cout << std::setw(2) << zapis->VratStudenta()->VratId() << ". "
			<< zapis->VratStudenta()->VratJmeno() << " "
			<< zapis->VratStudenta()->VratPrijmeni() << "\t"
			<< zapis->VratZnamkuString() << std::endl;
	}
}

// Nastaveni databaze se kterou v menu pracujeme
void Menu::NastavDatabazi(std::shared_ptr<data::Databaze> databaze) {
	this->databaze = databaze;
}

// Spustit menu
void Menu::Spust() {
	this->HlavniNabidka();
}
