#include "personaleventlist.h"
#include "debugwarning.h"
#include "parallel.h"
#include "personbase.h"
#include "populationalgorithmadvanced.h"
#include "populationstateadvanced.h"

#include <cstdlib>
#include <iostream>
#include <string>

inline PersonalEventList* PersonalEventList::personalEventList(PersonBase* pPerson)
{
        assert(pPerson);
        auto pEvtList = dynamic_cast<PersonalEventList*>(pPerson->getAlgorithmInfo());
        assert(pEvtList);
        return pEvtList;
}

PersonalEventList::PersonalEventList(PersonBase* pPerson)
{
        m_pPerson        = pPerson;
        m_pEarliestEvent = 0;
        m_listIndex      = -1;
#ifndef NDEBUG
        DEBUGWARNING("debug code to track earliest event is enabled")
#endif
}

PersonalEventList::~PersonalEventList()
{
        // TODO: cleanup?
}

void PersonalEventList::registerPersonalEvent(PopulationEvent* pEvt)
{
        // When this is called, the actual time at which it should take place
        // should still be undefined, since it is called from the PopEvent constructor
        assert(pEvt != nullptr);
        assert(!pEvt->isDeleted());
        assert(pEvt->needsEventTimeCalculation());
        m_untimedEvents.push_back(pEvt);
}

void PersonalEventList::processUnsortedEvents(PopulationAlgorithmAdvanced& alg, PopulationStateAdvanced& pop, double t0)
{
        checkEarliestEvent();
        checkEvents();

        if (m_untimedEvents.size() == 0) // nothing to do
                return;

        int          num    = m_untimedEvents.size();
        const State* pState = &pop;

        // First calculate the times

        for (int i = 0; i < num; i++) {
                PopulationEvent* pEvt = m_untimedEvents[i];
                assert(pEvt != 0);
                assert(!pEvt->isDeleted());
                alg.lockEvent(pEvt);
                if (pEvt->isScheduledForRemoval()) { // event was already examined and considered to be useless
                        m_untimedEvents[i] = 0;
                } else {
                        // Note that in the parallel version this event itself is locked!
                        if (pEvt->isNoLongerUseful(pop)) // for example if it refers to a dead person, of the maximum
                                                         // number of relationships has been reached
                        {
                                //			std::cout << "Detected useless event: " << pEvt << std::endl;
                                alg.scheduleForRemoval(pEvt);
                                m_untimedEvents[i] = 0;
                        } else {
                                // this assertion may fail for events that involve two people,
                                // for the same reason as above
                                // assert(pEvt->needsEventTimeCalculation());

                                if (pEvt->needsEventTimeCalculation()) {
                                        Event* pEvtBase = pEvt;
                                        pEvtBase->solveForRealTimeInterval(pState, t0);
                                }
                        }
                }

                alg.unlockEvent(pEvt);
        }

        checkEarliestEvent();

        // See if we need to check the events currently in m_timedEvents for the best time
        if (m_pEarliestEvent == 0 && m_timedEvents.size() != 0) {
                int num = m_timedEvents.size();

                m_pEarliestEvent = m_timedEvents[0];
                assert(!m_pEarliestEvent->isDeleted());

                double bestTime = m_pEarliestEvent->getEventTime();
                assert(bestTime >= 0);

                for (int i = 1; i < num; i++) {
                        PopulationEvent* pCheckEvt = m_timedEvents[i];
                        assert(!pCheckEvt->isDeleted());
                        double t = pCheckEvt->getEventTime();

                        if (t < bestTime) {
                                bestTime         = t;
                                m_pEarliestEvent = pCheckEvt;
                        }
                }
        }

        // merge lists

        double           newBestTime = 0;
        PopulationEvent* pNewBestEvt = 0;

        for (int i = 0; i < num; i++) {
                PopulationEvent* pEvt = m_untimedEvents[i];

                if (pEvt) { // can be NULL because of the previous code that checks the validity
                        assert(!pEvt->isDeleted());
                        int idx = m_timedEvents.size();
                        m_timedEvents.push_back(pEvt);
                        pEvt->setEventIndex(m_pPerson, idx); // TODO: this should be safe!
                        double t = pEvt->getEventTime();
                        if (!pNewBestEvt || t < newBestTime) {
                                newBestTime = t;
                                pNewBestEvt = pEvt;
                        }
                }
        }
        if (pNewBestEvt) {
                if (m_pEarliestEvent == 0) { // This should only happen if the original m_timedEvents list was empty
                        m_pEarliestEvent = pNewBestEvt;
                } else {
                        if (newBestTime < m_pEarliestEvent->getEventTime()) {
                                m_pEarliestEvent = pNewBestEvt;
                        }
                }
        }
        m_untimedEvents.resize(0);
        checkEarliestEvent();
        checkEvents();
}

void PersonalEventList::advanceEventTimes(PopulationAlgorithmAdvanced& alg, const PopulationStateAdvanced& pop,
                                          double t1)
{
        checkEarliestEvent();
        checkEvents();

        // Something about this person changed, so we must call 'subtractInternalTimeInterval'
        // for all events in the person's list (which becomes the unsorted list) and if the
        // event refers to another person as well, this means it is stored in that person's
        // list as well and must be moved to the unsorted list as well

        // note that it's possible that the unsorted list already contains an element:
        // we're calling pMan->advanceEventTimes() followed by pWoman->advanceEventTimes()
        // and the first call may already have moved something

        // append all events from the sorted list to the unsorted one
        pop.lockPerson(m_pPerson); // going to change the lists
        {
                // New version with swap and memcpy seems to be slightly (2%) faster, but contains a BUG!
                // So now we're using the older but safer version
                int num = m_timedEvents.size();

                for (int i = 0; i < num; i++) {
                        PopulationEvent* pEvt = m_timedEvents[i];
                        assert(!pEvt->isDeleted());

                        m_untimedEvents.push_back(pEvt);
                }

                m_timedEvents.resize(0);
                m_pEarliestEvent = 0;
                // std::cout << "advanceEventTimes: Person " << (void *)m_pPerson << ": timed events cleared,
                // m_untimedEvents " << m_untimedEvents.size() << std::endl;
        }
        pop.unlockPerson(m_pPerson);

        checkEvents();

        // calculate the times in the untimed event list
        int num = m_untimedEvents.size();

        if (!alg.isParallel()) {
                for (int i = 0; i < num; i++) {
                        PopulationEvent* pEvt = m_untimedEvents[i];

                        assert(pEvt != 0);
                        assert(!pEvt->isDeleted());
                        assert(pEvt->isInitialized());

                        // Check that we still need to process it, it may already have been done
                        // because of the reason above
                        if (!pEvt->needsEventTimeCalculation()) {
                                // check if another person's involved

                                int  numPersons     = pEvt->getNumberOfPersons();
                                bool foundOurselves = false;

                                for (int i = 0; i < numPersons; i++) {
                                        PersonBase* pOtherPerson = pEvt->getPerson(i);

                                        assert(pOtherPerson != 0);

                                        // we need to do this beforehand since we're going
                                        // to adjust the event time, which is used as a sorting key
                                        if (pOtherPerson != m_pPerson)
                                                personalEventList(pOtherPerson)->adjustingEvent(pEvt);
                                        else
                                                foundOurselves = true;
                                }

                                if (!foundOurselves) {
                                        std::cerr << "Consistency error: we're not present in the event" << std::endl;
                                        abort();
                                }

                                pEvt->subtractInternalTimeInterval(&pop, t1);
                        }
                }
        } else {
#pragma omp parallel for
                for (int i = 0; i < num; i++) {
                        PopulationEvent* pEvt = m_untimedEvents[i];

                        assert(pEvt != 0);
                        assert(!pEvt->isDeleted());

                        alg.lockEvent(pEvt);

                        assert(pEvt->isInitialized());

                        // Check that we still need to process it, it may already have been done
                        // because of the reason above
                        if (!pEvt->needsEventTimeCalculation()) {
                                // check if another person's involved

                                int  numPersons     = pEvt->getNumberOfPersons();
                                bool foundOurselves = false;

                                for (int i = 0; i < numPersons; i++) {
                                        PersonBase* pOtherPerson = pEvt->getPerson(i);

                                        assert(pOtherPerson != 0);

                                        // we need to do this beforehand since we're going
                                        // to adjust the event time, which is used as a sorting key
                                        if (pOtherPerson != m_pPerson) {
                                                pop.lockPerson(pOtherPerson); // can change the lists
                                                personalEventList(pOtherPerson)->adjustingEvent(pEvt);
                                                pop.unlockPerson(pOtherPerson);
                                        } else
                                                foundOurselves = true;
                                }

                                if (!foundOurselves) {
                                        std::cerr << "Consistency error: we're not present in the event" << std::endl;
                                        abort();
                                }

                                pEvt->subtractInternalTimeInterval(&pop, t1);
                        }

                        alg.unlockEvent(pEvt);
                }
        }

        checkEarliestEvent();
        checkEvents();
}

void PersonalEventList::adjustingEvent(PopulationEvent* pEvt)
{
        // this should move the event from the sorted to the unsorted list
        assert(!pEvt->isDeleted());
        checkEarliestEvent();
        checkEvents();
        int idx = pEvt->getEventIndex(m_pPerson);
        assert(idx >= 0 && idx < (int)m_timedEvents.size());
        assert(m_timedEvents[idx] == pEvt);
        int lastIdx = m_timedEvents.size() - 1;
        assert(idx >= 0 && idx <= lastIdx);
        if (m_timedEvents[lastIdx] != pEvt) {
                m_timedEvents[idx] = m_timedEvents[lastIdx];
                m_timedEvents[idx]->setEventIndex(m_pPerson, idx);
        }
        m_timedEvents.resize(lastIdx);
        m_untimedEvents.push_back(pEvt);
        // if it's the earliest event, it must be reset
        if (pEvt == m_pEarliestEvent) {
                m_pEarliestEvent = 0;
        }

        checkEarliestEvent();
        checkEvents();
}

PopulationEvent* PersonalEventList::getEarliestEvent()
{
        if (m_timedEvents.size() == 0)
                return 0;

        PopulationEvent* pEvt = m_pEarliestEvent;

        if (pEvt == 0) // means we still have to determine the earliest event
        {
                int num = m_timedEvents.size();

                m_pEarliestEvent = m_timedEvents[0];
                assert(!m_pEarliestEvent->isDeleted());
                double bestTime = m_pEarliestEvent->getEventTime();

                assert(bestTime >= 0);

                for (int i = 1; i < num; i++) {
                        PopulationEvent* pCheckEvt = m_timedEvents[i];
                        assert(!pCheckEvt->isDeleted());
                        double t = pCheckEvt->getEventTime();

                        if (t < bestTime) {
                                bestTime         = t;
                                m_pEarliestEvent = pCheckEvt;
                        }
                }

                pEvt = m_pEarliestEvent;
        }

        assert(pEvt != 0);
        assert(!pEvt->isDeleted());
        checkEarliestEvent();

        return pEvt;
}

void PersonalEventList::removeTimedEvent(PopulationEvent* pEvt)
{
        checkEarliestEvent();
        checkEvents();

        assert(pEvt != 0);
        assert(!pEvt->isDeleted());

        const auto idx     = pEvt->getEventIndex(m_pPerson);
        const auto lastIdx = m_timedEvents.size() - 1;

        if (m_timedEvents[lastIdx] != pEvt) {
                m_timedEvents[idx] = m_timedEvents[lastIdx];
                m_timedEvents[idx]->setEventIndex(m_pPerson, idx);
        }
        m_timedEvents.resize(lastIdx);

        if (pEvt == m_pEarliestEvent) // removed the earliest event
                m_pEarliestEvent = 0;

        checkEarliestEvent();
        checkEvents();
}

void PersonalEventList::checkEarliestEvent()
{
#ifndef NDEBUG
        if (m_pEarliestEvent == 0)
                return;
        {
                PopulationEvent* pE0      = m_timedEvents[0];
                double           bestTime = pE0->getEventTime();
                assert(bestTime >= 0);
                const auto num = m_timedEvents.size();
                for (size_t i = 1; i < num; i++) {
                        PopulationEvent* pCheckEvt = m_timedEvents[i];
                        double           t         = pCheckEvt->getEventTime();
                        if (t < bestTime) {
                                bestTime = t;
                                pE0      = pCheckEvt;
                        }
                }
                if (m_pEarliestEvent != pE0) {
                        std::cerr << "Mismatch between stored earliest event and real earliest event" << std::endl;
                        std::cerr << "m_pEarliestEvent->getEventTime() = " << m_pEarliestEvent->getEventTime()
                                  << std::endl;
                        std::cerr << "realEarliestEvent->getEventTime() = " << pE0->getEventTime() << std::endl;
                }

                assert(m_pEarliestEvent == pE0);
        }
#endif
}

void PersonalEventList::checkEvents()
{
#ifndef NDEBUG
        for (const auto& p : m_timedEvents) {
                assert(p);
        }
        for (const auto& p : m_untimedEvents) {
                assert(p);
        }
#endif
}
