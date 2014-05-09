/*
 * znamka.cpp: Pomocne funkce pro praci se znamkou
 */

#include "znamka.h"


// Prevede vyctovy typ znamka na string
std::string ZnamkaString(data::Znamka znamka) {
	switch(znamka) {
		case data::Znamka::A:
			return "A";
		case data::Znamka::B:
			return "B";
		case data::Znamka::C:
			return "C";
		case data::Znamka::D:
			return "D";
		case data::Znamka::E:
			return "E";
		case data::Znamka::F:
			return "F";
	};

	return "?";
}

// Prevede string na znamku. Pokud nejde o validni znamku vrati F
data::Znamka StringZnamka(std::string string) {
	if(string.length() != 1)
		return data::Znamka::F;

	switch(string[0]) {
		case 'a':
		case 'A':
			return data::Znamka::A;
		case 'b':
		case 'B':
			return data::Znamka::B;
		case 'c':
		case 'C':
			return data::Znamka::C;
		case 'd':
		case 'D':
			return data::Znamka::D;
		case 'e':
		case 'E':
			return data::Znamka::E;
		default:
			return data::Znamka::F;
	}
}
