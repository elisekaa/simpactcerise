#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

class Person;
class Man;
class Woman;

Man*   MAN(Person* pPerson);
Woman* WOMAN(Person* pPerson);

class PersonFamily
{
public:
        ///
        PersonFamily() : m_pFather(nullptr), m_pMother(nullptr) {}

        ///
        ~PersonFamily() = default;

        ///
        void setFather(Man* pFather)
        {
                assert(m_pFather == 0 && pFather != 0);
                m_pFather = pFather;
        }

        ///
        void setMother(Woman* pMother)
        {
                assert(m_pMother == 0 && pMother != 0);
                m_pMother = pMother;
        }

        ///
        Man* getFather() const { return m_pFather; }

        ///
        Woman* getMother() const { return m_pMother; }

        // TODO: currently, the death of a parent or the death of a child does
        // not have any influence on this list. I don't think modifying the list
        // on a mortality event is useful, will only complicate things
        // TODO: what might be useful is a member function to retrieve the number
        // of living children?
        void    addChild(Person* pPerson);
        bool    hasChild(Person* pPerson) const;
        int     getNumberOfChildren() const { return m_children.size(); }
        Person* getChild(int idx);

private:
        Man*                 m_pFather;
        Woman*               m_pMother;
        std::vector<Person*> m_children;
};

inline void PersonFamily::addChild(Person* pPerson)
{
        assert(pPerson != 0);
        assert(!hasChild(pPerson));
        m_children.push_back(pPerson);
}

// TODO: this is currently not fast for large number of children
//       can always use a 'set' if this becomes a bottleneck
inline bool PersonFamily::hasChild(Person* pPerson) const
{
        assert(pPerson != 0);
        for (size_t i = 0; i < m_children.size(); i++) {
                assert(m_children[i] != 0);
                if (m_children[i] == pPerson)
                        return true;
        }
        return false;
}

inline Person* PersonFamily::getChild(int idx)
{
        assert(idx >= 0 && idx < (int)m_children.size());
        Person* pChild = m_children[idx];
        assert(pChild != 0);
        return pChild;
}