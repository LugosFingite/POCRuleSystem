/*  parsing %{Cpp:License:ClassName} - Yann BOUCHER (yann) 08/05/2017
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
#ifndef PARSING_HPP
#define PARSING_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#include <stdexcept>

#include "util.hpp"

namespace parser
{

struct parse_error : std::runtime_error
{
        using std::runtime_error::runtime_error;
};

[[noreturn]] inline void throw_parse_error(const std::string& why)
{
    throw parse_error(why);
}

namespace detail
{

inline std::vector<std::string> parseChoice(const std::string& pattern)
{
    std::vector<std::string> choices;
    std::stringstream ss(pattern);
    std::string word;
    while (std::getline(ss, word, '|'))
    {
        choices.emplace_back(word);
    }

    return choices;
}

inline std::string replaceVariables(const std::string& in, const std::map<std::string, std::string>& variables)
{
    std::string result;

    std::stringstream ss(in);
    std::string word;
    while (ss >> word)
    {
        if (word.front() == '$') // c'est une variable à remplacer
        {
            word = word.substr(1, word.length()-1);
            if (variables.find(word) == variables.cend())
            {
                throw_parse_error("Undefined variable $" + word + " in answer pattern !");
            }
            else
            {
                word = variables.at(word);
            }
        }
        result += word + " ";
    }

    return result;
}

}

inline std::string parsePattern(const std::string& in, const std::map<std::string, std::string>& variables)
{
    std::string result;

    std::stringstream ss(in);
    std::string word;

    while (std::getline(ss, word, '('))
    {
        result += word;
        if (std::getline(ss, word, ')'))
        {
            auto choices = detail::parseChoice(word);
            result += *select_randomly(choices.begin(), choices.end());
        }
    }

    return detail::replaceVariables(result, variables);
}

}

#endif // PARSING_HPP
