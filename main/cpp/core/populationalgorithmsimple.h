#pragma once

/**
 * \file populationalgorithmsimple.h
 */

#include "PopulationAlgorithmAboutToFireInterface.h"
#include "PopulationAlgorithmInterface.h"
#include "populationevent.h"
#include "simplealgorithm.h"

#include <cassert>

#ifdef STATE_SHOW_EVENTS
#include <iostream>
#endif // STATE_SHOW_EVENTS

class GslRandomNumberGenerator;
class PersonBase;
class PopulationEvent;
class PopulationStateSimple;

/**
 * This class provides functions for a population-based simulation using
 * the modified Next Reaction Method (mNRM). Being population-based, the
 * state of the simulation mostly consists of the (living) people.
 *
 * In this implementation, the very straightforward algorithm provided
 * by the SimpleState class is used, making sure that all event times
 * are recalculated after an event got fired. While being a slow algorithm,
 * it can be useful to compare the results from PopulationAlgorithmAdvanced
 * to, to make sure the advanced implementation yields the correct results.
 *
 * Before calling PopulationAlgorithmInterface::run, you'll need to introduce
 * initial events (see PopulationAlgorithmInterface::onNewEvent) and most
 * likely also an initial set of persons in the simulation state you're
 * using (see PopulationStateInterface::addNewPerson). The actual state
 * that needs to be used in this implementation, is defined in PopulationStateSimple.
 *
 * Events for this type of simulation should derive from the PopulationEvent
 * class instead of using the EventBase base class directly.
 */
class PopulationAlgorithmSimple : public SimpleAlgorithm, public PopulationAlgorithmInterface
{
public:
        /// Constructor of the class, indicating if a parallel version should be used,
        /// which random number generator should be used and which simulation state.
        PopulationAlgorithmSimple(PopulationStateSimple& state, GslRandomNumberGenerator& rng, bool parallel);

        ///
        ~PopulationAlgorithmSimple() override;

        ///
        ExitStatus init() override;

        ///
        ExitStatus run(double& tMax, int64_t& maxEvents, double startTime = 0);

        ///
        void onNewEvent(PopulationEvent* pEvt) override;

        // TODO: shield these from the user somehow? These functions should not be used
        //       directly by the user, they are used internally by the algorithm
        void scheduleForRemoval(PopulationEvent* pEvt);

        ///
        double getTime() const override { return SimpleAlgorithm::getTime(); }

        ///
        void setAboutToFireAction(PopulationAlgorithmAboutToFireInterface* pAction) override
        {
                m_pOnAboutToFire = pAction;
        }

        ///
        GslRandomNumberGenerator* getRandomNumberGenerator() const override
        {
                return SimpleAlgorithm::getRandomNumberGenerator();
        }

private:
        ///
        ExitStatus initEventTimes() const override;

        ///
        const std::vector<Event*>& getCurrentEvents() const override { return m_allEvents; }

        ///
        void onFiredEvent(Event* pEvt, int position) override;

        ///
        int64_t getNextEventID();

        ///
        void onAboutToFire(Event* pEvt) override;

        std::vector<Event*>    m_allEvents;
        PopulationStateSimple& m_popState;
        bool                   m_init;

#ifdef ALGORITHM_SHOW_EVENTS
        void showEvents(); // FOR DEBUGGING
#endif

        void onAlgorithmLoop(bool finished) override;

private:
        std::vector<Event*>                      m_eventsToRemove;
        bool                                     m_parallelRequested;
        int64_t                                  m_nextEventID;
        PopulationAlgorithmAboutToFireInterface* m_pOnAboutToFire;
};

inline int64_t PopulationAlgorithmSimple::getNextEventID()
{
        int64_t id = m_nextEventID++;
        return id;
}

inline void PopulationAlgorithmSimple::onAboutToFire(Event* pEvt)
{
#ifdef STATE_SHOW_EVENTS
        std::cerr << getTime() << "\t" << static_cast<PopulationEvent*>(pEvt)->getDescription(getTime()) << std::endl;
#endif // STATE_SHOW_EVENTS

        if (m_pOnAboutToFire)
                m_pOnAboutToFire->onAboutToFire(static_cast<PopulationEvent*>(pEvt));
}
