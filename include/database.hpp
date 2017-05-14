/*  database %{Cpp:License:ClassName} - Yann BOUCHER (yann) 14/05/2017
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
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>

namespace chaiscript
{
class ChaiScript;
}

namespace db
{

bool exists(const std::string& id);

std::string load(const std::string& id);
std::string load(const std::string& id, const std::string& defaultValue);

void save(const std::string& id, const std::string& data);


void registerToScript(chaiscript::ChaiScript& chai);

}

#endif // DATABASE_HPP
