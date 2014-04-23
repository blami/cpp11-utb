/*
 * ikontext.h - definice rozhrani IKontext
 */

#pragma once

namespace obrazce {

// Virtualni trida IKontext definuje minimalni rozhrani kontextu. Struktura
// (struct) a trida (class) je v C++ totez s rozdilem, ze vsechny cleny struct
// jsou implictne public, zatimco u class jsou implicitne private.
struct IKontext {
	virtual int VratVysku() const = 0;
	virtual int VratSirku() const = 0;
	virtual void Zobraz() const = 0;
	virtual void Zapis(const double x, const double y) = 0;
	virtual void Vymaz() = 0;
	virtual ~IKontext() {};
};

} /* obrazce:: */
