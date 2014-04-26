/*
 * platno.h - definice tridy Platno
 */

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "ikontext.h"
#include "iobrazec.h"
#include "bod.h"
#include "json.h"

namespace obrazce {

// Trida Platno je akumulator objektu s rozhranim IObrazec a muze byt
// vykreslena pomoci kontextu s rozhranim IKontext.
class Platno {
	private:
	std::vector<std::shared_ptr<IObrazec>> obrazce;
	std::shared_ptr<IKontext> kontext;

	public:
	Platno(const Platno& vzor);
	Platno& operator= (const Platno& vzor);
	// Lze pouzit nasledujici kod. Viz. poznamka v platno.cpp
	/*
	Platno(const Platno&) = default;
	Platno& operator= (const Platno&) = default;
	*/
	Platno(Platno&&) = default;
	Platno& operator= (Platno&&) = default;
	Platno(std::shared_ptr<IKontext> kontext);

	void Pridej(std::shared_ptr<IObrazec> obrazec);
	void OdstranVsechnyObrazce();
	void Zobraz() const;
	std::string SerializujJSON() const;
	void DeserializujJSON(const std::string& json);
	void NastavKontext(const std::shared_ptr<IKontext> kontext);
};

} /* obrazce:: */
