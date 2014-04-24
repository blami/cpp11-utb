/*
 * obrazcejson.cpp - definice funkci pro serializaci a deserializaci obrazcu
 *
 */

#include "obrazcejson.h"
#include "kruh.h"
#include "polygony.h"

// using namespace zde nepomuze protoze jde o globalni funkce
namespace obrazcejson {

// Pomocna funkce pro serializaci datove struktury Bod do JSON
json::Object SerializujBod(const obrazce::Bod bod) {
	json::Object objekt;

	objekt["x"] = bod.x;
	objekt["y"] = bod.y;

	return objekt;
}

// Pomocna funkce pro deserializaci JSON reprezentace bodu do tridy Bod
obrazce::Bod DeserializujBod(const json::Object objekt) {
	return obrazce::Bod(objekt["x"], objekt["y"]);
}

// Funkce ktera prevede obrazec na objekt primo serializovatelny do JSON
json::Object Serializuj(const std::shared_ptr<obrazce::IObrazec>& obrazec) {
	json::Object objekt;

	if(obrazec == nullptr)
		return objekt;

	// Spolecne vlastnosti
	objekt["typ"] = obrazec->Typ();
	objekt["posunuti"] = SerializujBod(obrazec->VratPosunuti());
	objekt["zvetseni"] = obrazec->VratZvetseni();

	// Rozlisujeme pouze na dva zakladni typy obrazce Kruh a Polygon. Ctverec a
	// trojuhelnik jsou specialni pripady Polygonu a pri Deserializaci je
	// pozname podle pole typ.

	// Kruh
	if(std::dynamic_pointer_cast<obrazce::Kruh>(obrazec) != nullptr) {
		auto kruh = std::dynamic_pointer_cast<obrazce::Kruh>(obrazec);

		objekt["stred"] = SerializujBod(kruh->VratStred());
		objekt["polomer"] = kruh->VratPolomer();
	}
	// Ctverec je specialni pripad protoze ho konstruujeme pomoci delky strany
	// a a stredu namisto 4 bodu
	else if (std::dynamic_pointer_cast<obrazce::Ctverec>(obrazec) != nullptr) {
		auto ctverec = std::dynamic_pointer_cast<obrazce::Ctverec>(obrazec);

		objekt["a"] = ctverec->VratDelkuStrany();
		objekt["stred"] = SerializujBod(ctverec->VratStred());
	}
	// Polygon a ostatni potomci definovani body
	else if (std::dynamic_pointer_cast<obrazce::Polygon>(obrazec) != nullptr) {
		auto polygon = std::dynamic_pointer_cast<obrazce::Polygon>(obrazec);

		json::Array body;
		for(auto bod : polygon->VratBody()) {
			body.push_back(SerializujBod(bod));
		}
		objekt["body"] = body;
	}

	return objekt;
}

// Funkce ktera prevede JSON reprezentaci obrazce na prislusnou tridu obrazce
std::shared_ptr<obrazce::IObrazec> Deserializuj(json::Object objekt) {

	std::shared_ptr<obrazce::IObrazec> obrazec = nullptr;

	// Kruh
	if(objekt["typ"] == "Kruh") {
		obrazec = std::make_shared<obrazce::Kruh>(
		objekt["polomer"], DeserializujBod(objekt["stred"]));
	}
	else if(objekt["typ"] == "Ctverec") {
		obrazec = std::make_shared<obrazce::Ctverec>(
		objekt["a"], DeserializujBod(objekt["stred"]));
	}
	else {
		// Predpokladame ze vse dalsi je potomek Polygonu nebo Polygon (tj.
		// konkretne v tomto pripade Polygon nebo Trojuhelnik)
		std::vector<obrazce::Bod> body;
		for(auto bod : (json::Array)objekt["body"]) {
			body.push_back(DeserializujBod(bod));
		}
		if(objekt["typ"] == "Trojuhelnik") {
			obrazec = std::make_shared<obrazce::Trojuhelnik>(
				body[0], body[1], body[2]);
		}
		if(objekt["typ"] == "Polygon") {
			obrazec = std::make_shared<obrazce::Polygon>(
				body);
		}
	}

	// Spolecne parametry
	if(obrazec != nullptr) {
		obrazec->ZadejPosunuti(DeserializujBod(objekt["posunuti"]));
		obrazec->ZadejZvetseni(objekt["zvetseni"]);
	}

	return obrazec;
}

} /* obrazcejson:: */
