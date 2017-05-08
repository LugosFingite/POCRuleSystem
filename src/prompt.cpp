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

void Prompt::run()
{
    while (true)
    {
        auto input = read();
        std::cout << input << "\n";
    }
}

std::string Prompt::read()
{
    std::cout << ">";

    std::string input;
    std::getline(std::cin, input);

    return input;
}
