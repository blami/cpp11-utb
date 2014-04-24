/*
 * obrazcejson.h - deklarace funkci pro (de)serializaci obrazcu (z)do JSON
 */

#pragma once

#include <vector>
#include <memory>
#include "iobrazec.h"
#include "json.h"

namespace obrazcejson {

json::Object Serializuj(const std::shared_ptr<obrazce::IObrazec>& obrazec);
std::shared_ptr<obrazce::IObrazec> Deserializuj(json::Object objekt);
//std::vector<std::shared_ptr<IObrazec>> Deserializuj(std::string json);

} /* obrazcejson:: */
