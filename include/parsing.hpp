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

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdexcept>

#include "uglytree.hpp"

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

inline TreeNode<std::string> buildTree(const std::string& pattern)
{
    std::vector<std::string> tokens = splitByDelimiters(pattern, "()|");
    TreeNode<std::string> tree;
    auto* currentNode = &tree;
    std::string acc;
    for (const auto& tok : tokens)
    {
        if (tok == "(")
        {
            if (tree.getParent() == nullptr || !acc.empty())
            {
                currentNode = &currentNode->addChild(acc);
                acc.clear();
            }
        }
        else if (tok == ")")
        {
            if (!acc.empty())
            {
                currentNode->addChild(acc);
                acc.clear();
            }
            currentNode = currentNode->getParent();
        }
        else if (tok == "|")
        {
            if (!acc.empty())
            {
                currentNode->addChild(acc);
                acc.clear();
            }
        }
        else
        {
            acc += tok;
        }
    }
    if (!acc.empty())
    {
        tree.addChild(acc);
    }
    return tree;
}

inline void collapseTree(TreeNode<std::string>& tree)
{
    if (!tree.isLeaf())
    {
        if (tree.isParentOfLeafs())
        {
            std::vector<std::string> choices;
            for (size_t i { 0 }; i < tree.getNumChildren(); ++i)
            {
                choices.emplace_back(tree.getChild(i).getData());
            }
            tree.setData(tree.getData() + *select_randomly(choices.begin(), choices.end()));
            tree.removeChildren();
        }
        else
        {
            for (size_t i { 0 }; i < tree.getNumChildren(); ++i)
            {
                collapseTree(tree.getChild(i));
            }
        }
    }
}

}


inline std::string parsePattern(const std::string& in, const std::map<std::string, std::string>& variables)
{
    std::string pattern = detail::replaceVariables(in, variables);
    auto tree = detail::buildTree(pattern);

    while (!tree.isParentOfLeafs())
    {
        detail::collapseTree(tree);
    }

    std::string result;

    for (size_t i { 0 }; i < tree.getNumChildren(); ++i)
    {
        result += tree.getChild(i).getData();
    }

    return result;
}



}

#endif // PARSING_HPP
