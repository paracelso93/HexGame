//
// Created by edoardo biasio on 2021-03-14.
//

#include "unit_parser.hpp"
#include "../game.hpp"
#include <fstream>
#include <string>

std::vector<std::string > UnitParser::unit_types = std::vector<std::string >();
std::vector<UnitParser::Unit* > UnitParser::units = std::vector<UnitParser::Unit* >();