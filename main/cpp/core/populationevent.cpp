#include "populationevent.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

void PopulationEvent::commonConstructor()
{
#ifdef POPULATIONEVENT_FAKEDELETE
        m_deleted = false;
#endif // POPULATIONEVENT_FAKEDELETE

        // Since we'll be removing each event when executed, this
        // avoids the needless generation of a random number
        setWillBeRemoved(true);

        m_numPersons          = 0;
        m_eventID             = -1;
        m_scheduledForRemoval = false;

        // only one person will have a reference to this event

        for (int i = 0; i < POPULATIONEVENT_MAXPERSONS; i++) {
                m_pPersons[i]   = 0;
                m_eventIndex[i] = -1;
        }
}

PopulationEvent::PopulationEvent() { commonConstructor(); }

void PopulationEvent::setGlobalEventPerson(PersonBase* pDummyPerson)
{
#ifdef POPULATIONEVENT_FAKEDELETE
        assert(!m_deleted);
#endif // POPULATIONEVENT_FAKEDELETE
        assert(m_numPersons == 0);
        assert(pDummyPerson != 0 && pDummyPerson->getGender() == PersonBase::GlobalEventPerson);

        m_pPersons[0] = pDummyPerson;
        m_numPersons  = 1;
}

PopulationEvent::PopulationEvent(PersonBase* pPerson)
{
        assert(pPerson != 0);
        commonConstructor();
        m_pPersons[0] = pPerson;
        m_numPersons  = 1;
}

PopulationEvent::PopulationEvent(PersonBase* pPerson1, PersonBase* pPerson2)
{
        assert(pPerson1 != 0 && pPerson2 != 0);
        commonConstructor();
        m_pPersons[0] = pPerson1;
        m_pPersons[1] = pPerson2;
        m_numPersons  = 2;
}

bool PopulationEvent::isNoLongerUseful(const PopulationStateInterface& population)
{
#ifdef POPULATIONEVENT_FAKEDELETE
        assert(!m_deleted);
#endif // POPULATIONEVENT_FAKEDELETE

        int num = m_numPersons;

        for (int i = 0; i < num; i++) {
                assert(m_pPersons[i] != 0);

                if (m_pPersons[i]->hasDied())
                        return true;
        }

        return isUseless(population);
}
