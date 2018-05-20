#pragma once

#include "ExitStatus.h"
#include "PersonAlgorithmInfo.h"
#include "populationevent.h"
#include <list>
#include <set>
#include <vector>

//#define PERSONALEVENTLIST_EXTRA_DEBUGGING

class PersonBase;
class PopulationStateTesting;
class PopulationAlgorithmTesting;

class PersonalEventListTesting : public PersonAlgorithmInfo
{
public:
        ///
        explicit PersonalEventListTesting(PersonBase* pPerson);

        ///
        ~PersonalEventListTesting() override;

        ///
        void registerPersonalEvent(PopulationEvent* pEvt);

        ///
        void processUnsortedEvents(PopulationAlgorithmTesting& alg, PopulationStateTesting& pop, double t0);

        ///
        void advanceEventTimes(PopulationAlgorithmTesting& alg, const PopulationStateTesting& pop, double t1);

        ///
        void adjustingEvent(PopulationEvent* pEvt);

        ///
        void removeTimedEvent(PopulationEvent* pEvt);

        ///
        PopulationEvent* getEarliestEvent();

        ///
        void setListIndex(int i) { m_listIndex = i; }

        ///
        int getListIndex() const { return m_listIndex; }

private:
        static PersonalEventListTesting* personalEventList(PersonBase* pPerson);
        void                             removeSecondaryEvent(PopulationEvent* pEvt);
        void                             checkEarliestEvent();
        void                             checkEvents();

private:
        std::vector<PopulationEvent*> m_timedEventsPrimary;
        std::vector<PopulationEvent*> m_untimedEventsPrimary;
        std::vector<PopulationEvent*> m_secondaryEvents;
        PopulationEvent*              m_pEarliestEvent;
        PersonBase*                   m_pPerson;
        int                           m_listIndex;

        friend class PopulationAlgorithmTesting;
};
