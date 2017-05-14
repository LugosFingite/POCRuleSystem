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

#include "database.hpp"

#include <fstream>
#include "ext/chaiscript/chaiscript.hpp"

#include "ext/json.hpp"

namespace db
{

std::string load(const std::string& id)
{
    std::fstream fstream("database.json", std::ios::in | std::ios::out | std::ios::app);

    nlohmann::json json;
    fstream >> json;

    return json.at(id);
}

std::string load(const std::string& id, const std::string& defaultValue)
{
    std::fstream fstream("database.json", std::ios::in | std::ios::out | std::ios::app);

    nlohmann::json json;
    fstream >> json;

    if (json.find(id) != json.end())
    {
        return json[id];
    }
    else
    {
        return defaultValue;
    }
}

void save(const std::string &id, const std::string &data)
{
    std::ifstream ifstream("database.json");

    nlohmann::json json;
    ifstream >> json;

    ifstream.close();

    json[id] = data;

    std::ofstream ofstream("database.json", std::ios::out | std::ios::trunc);

    ofstream << json;
}

bool exists(const std::string &id)
{
    std::ifstream ifstream("database.json");

    nlohmann::json json;
    ifstream >> json;

    return json.find(id) != json.end();
}

void registerToScript(chaiscript::ChaiScript &chai)
{
    chai.add(chaiscript::fun(static_cast<std::string (*)(const std::string&)>(&load)), "load");
    chai.add(chaiscript::fun(static_cast<std::string (*)(const std::string&, const std::string&)>(&load)), "load");

    chai.add(chaiscript::fun(&save), "save");
    chai.add(chaiscript::fun(&exists), "exists");
}

}
