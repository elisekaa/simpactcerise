#pragma once

#include "ExitStatus.h"
#include "PersonAlgorithmInfo.h"
#include "populationevent.h"

#include <list>
#include <set>
#include <vector>

class PersonBase;
class PopulationStateAdvanced;
class PopulationAlgorithmAdvanced;

class PersonalEventList : public PersonAlgorithmInfo
{
public:
        ///
        explicit PersonalEventList(PersonBase* pPerson);

        ///
        ~PersonalEventList() override;

        ///
        void registerPersonalEvent(PopulationEvent* pEvt);

        ///
        void processUnsortedEvents(PopulationAlgorithmAdvanced& alg, PopulationStateAdvanced& pop, double t0);

        ///
        void advanceEventTimes(PopulationAlgorithmAdvanced& alg, const PopulationStateAdvanced& pop, double t1);

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
        static PersonalEventList* personalEventList(PersonBase* pPerson);

private:
        void checkEarliestEvent();
        void checkEvents();

private:
        std::vector<PopulationEvent*> m_timedEvents;
        std::vector<PopulationEvent*> m_untimedEvents;
        PopulationEvent*              m_pEarliestEvent;
        PersonBase*                   m_pPerson;
        int                           m_listIndex;

private:
        friend class PopulationAlgorithmAdvanced;
};
