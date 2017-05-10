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

using namespace boost::xpressive;

bool Rule::matches(const std::string &input) const
{
    return regex_match(input, checkPattern);
}

std::string Rule::answer(const std::string& input)
{
    smatch what;
    regex_match(input, what, checkPattern);

    for (const auto& pair : variables)
    {
        variables[pair.first] = what[pair.first].str();
    }

    (void)input; // on utilise pas encore, c'est juste un POC la ^^'
    return parser::parsePattern(returnPattern, variables);
}

Rule ruleFromJson(const nlohmann::json &json)
{
    Rule rule;
    std::string pattern = json["input"];
    sregex match = sregex::compile(R"(\$[[:alpha:]]+)");

    smatch what;
    regex_search(pattern, what, match);

    for (const auto& val : what)
    {
        rule.variables[val.str().substr(1, val.length()-1)] = ""; // enlever le '$' au début
    }

    pattern = regex_replace(pattern, match, R"((?P<$&>[[:alnum:]]+))");
    pattern.erase(std::remove(pattern.begin(), pattern.end(), '$'), pattern.end());

    rule.checkPattern = sregex::compile(pattern, regex_constants::icase);
    rule.returnPattern = json["answer"];

    return rule;
}
