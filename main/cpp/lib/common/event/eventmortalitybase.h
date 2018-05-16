#ifndef EVENTMORTALITYBASE_H

#define EVENTMORTALITYBASE_H

#include "simpactevent.h"

class ConfigSettings;

// Base class for AIDS and normal mortality events
class EventMortalityBase : public SimpactEvent
{
public:
        EventMortalityBase(Person* pPerson);
        ~EventMortalityBase();

        // bool isEveryoneAffected() const							{ return true; }
        void markOtherAffectedPeople(const PopulationStateInterface& population) override;

        void fire(Algorithm* pAlgorithm, State* pState, double t) override;
};

#endif // EVENTMORTALITYBASE_H
