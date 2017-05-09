/*  src/prompt.cpp Prompt - Yann BOUCHER (yann) 08/05/2017
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
#include "prompt.hpp"

#include <iostream>
#include <fstream>

#include "ext/tinydir.h"

#include "parsing.hpp"

void Prompt::run()
{
    loadRules();

    while (true)
    {
        auto input = read();

        if (m_exit.matches(input))
        {
            break;
        }

        bool matched { false };
        for (const auto& rule : m_rules)
        {
            if (rule.matches(input))
            {
                std::cout << rule.answer(input) << "\n";
                matched = true;
                break;
            }
        }
        if (!matched)
        {
            std::cout << m_notUnderstood.answer(input) << "\n";
        }
    }
}

void Prompt::loadRules()
{
    tinydir_dir dir;
    tinydir_open(&dir, "rules");

    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        if (!file.is_dir)
        {
            std::ifstream ifstream("rules/" + std::string(file.name));

            nlohmann::json json;
            ifstream >> json;
            m_rules.emplace_back(ruleFromJson(json));
        }

        tinydir_next(&dir);
    }

    loadRuleNotUnderstood();
    loadRuleExit();
}

void Prompt::loadRuleNotUnderstood()
{
    std::ifstream ifstream("rulesSpecial/notUnderstood.json");

    nlohmann::json json;
    ifstream >> json;
    m_notUnderstood = ruleFromJson(json);
}

void Prompt::loadRuleExit()
{
    std::ifstream ifstream("rulesSpecial/exit.json");

    nlohmann::json json;
    ifstream >> json;
    m_exit = ruleFromJson(json);
}

std::string Prompt::read()
{
    std::cout << ">";

    std::string input;
    std::getline(std::cin, input);

    return input;
}
