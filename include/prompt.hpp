/*  include/prompt.hpp Prompt - Yann BOUCHER (yann) 08/05/2017
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
#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <string>
#include <vector>

#include "ext/chaiscript/chaiscript.hpp"

#include "rule.hpp"

class Prompt
{
    public:
        Prompt();

    public:
        void run();

    private:
        void loadRules();
        void loadRuleNotUnderstood();
        void loadRuleExit();

        std::string read();

        std::vector<Rule> m_rules;
        Rule m_notUnderstood;
        Rule m_exit;

        chaiscript::ChaiScript m_scriptingEngine;
};

#endif // PROMPT_HPP
