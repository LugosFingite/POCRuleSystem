/*  util %{Cpp:License:ClassName} - Yann BOUCHER (yann) 08/05/2017
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
#ifndef UTIL_HPP
#define UTIL_HPP

#include <random>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g)
{
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

inline std::vector<std::string> splitByDelimiters(const std::string& input, const std::string& delims)
{
    std::vector<std::string> tokens;
    char c;
    std::stringstream ss(input);
    while (ss.get(c))
    {
        if (delims.find(c) != std::string::npos)
        {
            tokens.emplace_back(1, c);
        }
        else
        {
            tokens.emplace_back(1, c); // start new string
            while (ss.get(c))
            {
                if (delims.find(c) != std::string::npos)
                {
                    tokens.emplace_back(1, c);
                    break;
                }
                else
                {
                    tokens.back() += c; // append to existing string
                }
            }
        }
    }

    return tokens;
}

#endif // UTIL_HPP
