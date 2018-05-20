#include "populationstatesimple.h"

ExitStatus PopulationStateSimple::init()
{
        if (m_init)
                return ExitStatus("Already initialized");

        assert(m_people.size() == 0);
        assert(m_deceasedPersons.size() == 0);
        m_numMen       = 0;
        m_numWomen     = 0;
        m_nextPersonID = 0;

        // Note: we can't do this too soon since m_nextPersonID must be initialized
        m_people.resize(m_numGlobalDummies);

        for (int i = 0; i < m_numGlobalDummies; i++) {
                m_people[i] = new GlobalEventDummyPerson();
                auto pInfo  = new PersonAlgorithmInfoSimple();
                m_people[i]->setAlgorithmInfo(pInfo);
                pInfo->setListIndex(i);
                int64_t id = getNextPersonID();
                m_people[i]->setPersonID(id);
        }
        m_init = true;
        return ExitStatus(true);
}

int64_t PopulationStateSimple::getNextPersonID()
{
        int64_t id = m_nextPersonID++;
        return id;
}

void PopulationStateSimple::setListIndex(PersonBase* pPerson, int idx)
{
        assert(pPerson);
        auto pInfo = dynamic_cast<PersonAlgorithmInfoSimple*>(pPerson->getAlgorithmInfo());
        assert(pInfo);
        pInfo->setListIndex(idx);
}

int PopulationStateSimple::getListIndex(PersonBase* pPerson)
{
        assert(pPerson);
        auto pInfo = dynamic_cast<PersonAlgorithmInfoSimple*>(pPerson->getAlgorithmInfo());
        assert(pInfo);
        return pInfo->getListIndex();
}

void PopulationStateSimple::addAlgorithmInfo(PersonBase* pPerson)
{
        auto pInfo = new PersonAlgorithmInfo();
        pPerson->setAlgorithmInfo(pInfo);
}
