/*  include/rule.hpp Rule - Yann BOUCHER (yann) 08/05/2017
**
**
**            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
**                    Version 2, December 2004
**
** Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
**
** Everyone is permitted to copy and distribute verbatim or modified
** copies of this license document, and changing it is allowed as long
** as the name is changed.
**
**            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
**   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
**
**  0. You just DO WHAT THE FUCK YOU WANT TO.
*/
#ifndef RULE_HPP
#define RULE_HPP

#include <vector>
#include <string>
#include <map>

#include <boost/xpressive/xpressive.hpp>

#include "ext/json.hpp"

namespace chaiscript
{
class ChaiScript;
}

/// La structure règle
struct Rule
{
        /// vérifie si une entrée donnée correspond à la règle
        bool matches(const std::string& input) const;
        /// s'occupe de fournir une réponse appropriée selon les caractéristiques de l'entrée et de la règle
        std::string answer(const std::string& input, chaiscript::ChaiScript& scriptingEngine);

        boost::xpressive::sregex checkPattern;
        std::string returnPattern;
        std::string analyzeScript;
        std::map<std::string, std::string> variables;
};

std::vector<Rule> rulesFromJson(const nlohmann::json& root);

#endif // RULE_HPP
