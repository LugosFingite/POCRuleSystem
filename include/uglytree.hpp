/*  uglytree %{Cpp:License:ClassName} - Yann BOUCHER (yann) 14/05/2017
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
#ifndef UGLYTREE_HPP
#define UGLYTREE_HPP

/// DISCLAIMER : Oui, c'est très moche
/// Mais je voulais baser l'algo sur un arbre
/// car flemme de faire un truc poussé et optimisé
/// et j'ai donc réutilisé une classe Tree moche mais qui marche
/// que j'avais fait pour france ioi à la base avant de me rendre compte que c'était totalement overkill

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <memory>

template<class T>
class TreeNode
{
    public:
        TreeNode(T data = T(), TreeNode<T>* parent = nullptr);
        T getData() const;
        void setData(const T& data);
        TreeNode<T>& addChild(const T& data);
        TreeNode<T>& addChild(std::unique_ptr<TreeNode<T> > &ptr);
        void removeChild(TreeNode<T>* ptr);
        const TreeNode<T>* findChild(const T& data) const;
        TreeNode<T> *findChild(const T& data);
        const TreeNode<T>& getChild(size_t indx) const;
        TreeNode<T>& getChild(size_t indx);
        const TreeNode<T>* getParent() const;
        TreeNode<T>* getParent();
        void changeParent(TreeNode<T>* parent);
        bool hasChild(const T& data) const
        {
            return findChild(data) != nullptr;
        }
        size_t getNumChildren() const;
        void print(std::ostream& os = std::cout, std::__cxx11::string indent = "", bool last = false) const;
        friend std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node)
        {
            node.print(os);
            return os;
        }

        bool isLeaf() const
        {
            return getNumChildren() == 0;
        }

        bool isParentOfLeafs() const
        {
            return std::all_of(m_children.begin(), m_children.end(), [](const std::unique_ptr<TreeNode<T>>& ptr)
            {
                return ptr->isLeaf();
            });
        }

        void removeChildren()
        {
            m_children.clear();
        }

    private:
        void moveChild(TreeNode<T>* el, TreeNode<T>* newParent)
        {
            newParent->addChild(*std::find_if(m_children.begin(), m_children.end(), [el](const std::unique_ptr<TreeNode<T>>& ptr)
            {
                return ptr.get() == el;
            }));
            cleanupChildren();
        }
        void cleanupChildren()
        {
            removeChild(nullptr);
        }
    private:
        T m_data {};
        TreeNode<T>* m_parent { nullptr };
        std::vector<std::unique_ptr<TreeNode<T>>> m_children {};
};
template <class T>
void TreeNode<T>::changeParent(TreeNode<T> *parent)
{
    m_parent->moveChild(this, parent);
}
template<class T>
TreeNode<T>::TreeNode(T data, TreeNode<T>* parent) : m_parent(parent)
{
    m_data = data;
}
template<class T>
T TreeNode<T>::getData() const
{
    return m_data;
}
template<class T>
void TreeNode<T>::setData(const T& data)
{
    m_data = data;
}
template<class T>
TreeNode<T>& TreeNode<T>::addChild(const T& data)
{
    m_children.emplace_back(std::make_unique<TreeNode<T>>(data, this));
    m_children.shrink_to_fit();
    return *m_children.back();
}
template<class T>
TreeNode<T>& TreeNode<T>::addChild(std::unique_ptr<TreeNode<T>>& ptr)
{
    m_children.emplace_back(std::move(ptr));
    m_children.back()->m_parent = this;
    m_children.shrink_to_fit();
    return *m_children.back();
}
template<class T>
void TreeNode<T>::removeChild(TreeNode<T> *ptr)
{
    m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [ptr](const std::unique_ptr<TreeNode<T>>& child)
    {
        return ptr == child.get();
    }), m_children.end());
}
template<class T>
const TreeNode<T>*  TreeNode<T>::findChild(const T& data) const
{
    for (size_t i { 0 }; i < m_children.size(); ++i)
    {
        if(m_children[i]->getData() == data)
        {
            return m_children[i].get();
        }
        auto find_child = m_children[i]->findChild(data);
        if (find_child != nullptr)
        {
            return find_child;
        }
    }
    return nullptr;
}
template<class T>
TreeNode<T>* TreeNode<T>::findChild(const T& data)
{
    for (size_t i { 0 }; i < m_children.size(); ++i)
    {
        if(m_children[i]->getData() == data)
        {
            return m_children[i].get();
        }
        auto find_child = m_children[i]->findChild(data);
        if (find_child != nullptr)
        {
            return find_child;
        }
    }
    return nullptr;
}
template<class T>
const TreeNode<T>& TreeNode<T>::getChild(size_t indx) const
{
    assert(indx < m_children.size());
    return *m_children[indx];
}
template<class T>
TreeNode<T>& TreeNode<T>::getChild(size_t indx)
{
    assert(indx < m_children.size());
    return *m_children[indx];
}
template<class T>
const TreeNode<T> *TreeNode<T>::getParent() const
{
    return m_parent;
}
template<class T>
TreeNode<T> *TreeNode<T>::getParent()
{
    return m_parent;
}
template<class T>
size_t TreeNode<T>::getNumChildren() const
{
    return m_children.size();
}
template<class T>
void TreeNode<T>::print(std::ostream& os, std::string indent, bool last) const
{
    os << indent;
    if (last)
    {
        os << "\\-";
        indent += "  ";
    }
    else
    {
        os << "|-";
        indent += "| ";
    }
    os << "(" << getData() << ")\n";

    for (size_t i { 0 }; i < getNumChildren(); ++i)
    {
        getChild(i).print(os, indent, i == getNumChildren() - 1);
    }
}

#endif // UGLYTREE_HPP
