/*
 * menu.h: deklarace tridy Menu
 */

#pragma once

#include <memory>
#include <string>
#include "databaze.h"

namespace menu {

// Trida predstavujici uzivatelske rozhrani pro praci s databazi pomoci
// terminalu
class Menu {
	private:
	std::shared_ptr<data::Databaze> databaze;
	// Pomocne funkce pro nacitani a validaci vstupu z terminalu
	unsigned int NactiCislo(const std::string zprava);
	std::string NactiCisloString(const std::string zprava);
	std::string NactiString(const std::string zprava);
	data::Znamka NactiZnamku(const std::string zprava);

	// Nabidky
	void HlavniNabidka();
	void NacistDatabaziNabidka();
	void UlozitDatabaziNabidka();
	void VytvoritStudentaNabidka();
	void VytvoritPredmetNabidka();
	void StudentNabidka(const std::shared_ptr<data::Student>& student);
	void PredmetNabidka(const std::shared_ptr<data::Predmet>& predmet);
	void VyhledatStudentaNabidka(bool dle_id);
	void VyhledatPredmetNabidka(bool dle_id);
	void ZapsatPredmetNabidka(const std::shared_ptr<data::Student>& student);
	void OdepsatPredmetNabidka(const std::shared_ptr<data::Student>& student);
	void ZnamkovatNabidka(const std::shared_ptr<data::Student>& student);

	// Vypisy
	void SeznamStudentuVypis(const std::string titulek,
		const std::vector<std::shared_ptr<data::Student>>& seznam);
	void SeznamPredmetuVypis(const std::string titulek,
		const std::vector<std::shared_ptr<data::Predmet>>& seznam);
	void StudentVypis(const std::shared_ptr<data::Student>& student);
	void PredmetVypis(const std::shared_ptr<data::Predmet>& predmet);

	public:
	Menu(std::shared_ptr<data::Databaze> databaze);
	void NastavDatabazi(std::shared_ptr<data::Databaze> databaze);
	void Spust();
};


} /* menu:: */
