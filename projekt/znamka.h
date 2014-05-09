/*
 * znamka.h: Deklarace a definice vyctoveho typu pro znamku
 */

#pragma once
#include <string>

namespace data {

// Vyctovy typ pro jednotlive znamky. Prirazene hodnoty jsou desetinasobky ECTS
// hodnot protoze pro enumeraci lze pouzit pouze integralni typ.
enum class Znamka {
	A = 10, // 1.0
	B = 15, // 1.5
	C = 20, // 2.0
	D = 25, // 2.5
	E = 30, // 3.0
	F = 0   // Pozn.: nezapocitava se do prumeru
};

} /* data:: */

// Pomocne funkce pro praci se znamkou
std::string ZnamkaString(data::Znamka znamka);
data::Znamka StringZnamka(std::string string);
