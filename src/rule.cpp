/*  src/rule.cpp Rule - Yann BOUCHER (yann) 08/05/2017
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
#include "rule.hpp"

#include <algorithm>

#include "parsing.hpp"

bool Rule::matches(const std::string &input) const
{
    return std::regex_match(input, checkPattern);
}

std::string Rule::answer(const std::string& input) const
{
    (void)input; // on utilise pas encore, c'est juste un POC la ^^'
    return parser::parsePattern(returnPattern);
}

Rule ruleFromJson(const nlohmann::json &json)
{
    Rule rule;

    std::string pattern = json["input"];
    rule.checkPattern = std::regex(pattern, std::regex::icase);
    rule.returnPattern = json["answer"];

    return rule;
}
