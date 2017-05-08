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
#include <regex>

#include "ext/json.hpp"

class Rule
{
    public:
        bool matches(const std::string& input) const;
        std::string answer(const std::string& input) const;

    public:
        std::vector<std::regex> checkPatterns;
        std::string returnPattern;
};

Rule ruleFromJson(const nlohmann::json& json);

#endif // RULE_HPP
