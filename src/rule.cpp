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

#include "ext/chaiscript/chaiscript.hpp"

#include "parsing.hpp"

using namespace boost::xpressive;

bool Rule::matches(const std::string &input) const
{
    return regex_match(input, checkPattern);
}

std::string Rule::answer(const std::string& input, chaiscript::ChaiScript &scriptingEngine)
{
    auto oldState = scriptingEngine.get_state();
    smatch what;
    regex_match(input, what, checkPattern);

    for (const auto& pair : variables)
    {
        variables[pair.first] = what[pair.first].str();
        scriptingEngine.add_global(chaiscript::var(&variables[pair.first]), pair.first);
    }

    scriptingEngine.add(chaiscript::fun([input]{return input;}), "input");

    std::vector<std::string> temporaryVariables;

    scriptingEngine.add(chaiscript::fun([this, &temporaryVariables](const std::string& id, const std::string& val)
    {variables[id] = val; temporaryVariables.emplace_back(id);}), "pushVariable");

    scriptingEngine.eval<std::function<void()>>("fun() {" + analyzeScript + "}")();

    scriptingEngine.set_state(oldState);

    std::string result = parser::parsePattern(returnPattern, variables);

    for (const auto& id : temporaryVariables)
    {
        variables.erase(id);
    }

    return result;
}

std::vector<Rule> rulesFromJson(const nlohmann::json &root)
{
    std::vector<Rule> rules;
    for (const auto& json : root["rules"])
    {
        Rule rule;
        std::string pattern = json["input"];
        sregex match = sregex::compile(R"(\$[[:alnum:]]+)");

        sregex_token_iterator iter(pattern.begin(), pattern.end(), match, 0);
        sregex_token_iterator end;

        for(; iter != end; ++iter )
        {
            auto val = *iter;
            rule.variables[val.str().substr(1, val.length()-1)] = ""; // enlever le '$' au début
        }

        pattern = regex_replace(pattern, match, R"((?P<$&>[[:alnum:]]+))");
        pattern.erase(std::remove(pattern.begin(), pattern.end(), '$'), pattern.end());

        rule.checkPattern = sregex::compile(pattern, regex_constants::icase);
        rule.returnPattern = json["answer"];

        if (json.find("script") != json.cend())
        {
            rule.analyzeScript = json["script"];
        }

        rules.emplace_back(rule);
    }

    return rules;
}
