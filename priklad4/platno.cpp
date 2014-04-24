/*
 * platno.cpp - definice tridy Platno
 */

#include "platno.h"
#include "obrazcejson.h"

using namespace obrazce;

// Kopirujici konstruktor
// POZN: Toto je defakto tvar implicitniho kopirujiciho konstruktoru (ktery
// vygeneruje prekladac v dobe prekladu, protoze obe properties maji kopirovaci
// konstruktor, nejsou to reference (lze to overit v objektovem souboru .o).
Platno::Platno(const Platno& vzor) :
	// vector<T> i shared_ptr<T> maji kopirovaci konstruktor, v pripade
	// shared_pointeru dojde ke zvyseni poctu referenci a vektor se zkopiruje
	obrazce { vzor.obrazce },
	kontext { vzor.kontext } {}

// Operator prirazeni
// POZN: Viz. poznamka u kopirujiciho konstruktoru
Platno& Platno::operator= (const Platno& vzor) {
	// vector<T> i shared_ptr<T> maji implementovany operator prirazeni. Viz.
	// poznamka u kopirujiciho konstruktoru
	this->obrazce = vzor.obrazce;
	this->kontext = vzor.kontext;

	return *this;
}

// Poznamka vlastne stejne plati pro presouvaci konstruktor a operator =
// Proto je zde neuvadim (viz. platno.h a klicove slovo default)

// Konstruktor
Platno::Platno(std::shared_ptr<IKontext> kontext) :
	kontext { kontext } {}

// Prida obrazec na platno
void Platno::Pridej(std::shared_ptr<IObrazec> obrazec) {
	// Pokud je obrazec null pak nic nepridavame
	if(!obrazec)
		return;

	this->obrazce.push_back(obrazec);
}

// Odstrani vsechny obrazce z platna
void Platno::OdstranVsechnyObrazce() {
	this->obrazce.clear();
}

// Zobrazi obrazce pridane na platno na nastavenem kontextu
void Platno::Zobraz() const {
	// Pokud neni kontext nastaven, neudelame nic
	if(!this->kontext)
		return;

	// Vymazat kontext
	this->kontext->Vymaz();

	for(auto obrazec : this->obrazce) {
		obrazec->Vykresli(&*this->kontext);
	}

	this->kontext->Zobraz();
}

// Serializuje cele platno do JSON notace
std::string Platno::SerializujJSON() const {
	json::Array objekt;

	for(auto i : this->obrazce) {
		objekt.push_back(obrazcejson::Serializuj(i));
	}

	return json::Serialize(objekt);
}

// Vycisti platno a deserializuje JSON notaci
void Platno::DeserializujJSON(const std::string& json) {
	json::Array objekt = json::Deserialize(json);

	this->OdstranVsechnyObrazce();
	for(auto i : objekt) {
		std::shared_ptr<IObrazec> obrazec = obrazcejson::Deserializuj(i);
		if(obrazec != nullptr)
			this->Pridej(obrazec);
	}
}
