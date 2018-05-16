#ifndef SIMPACTEVENT_H

#define SIMPACTEVENT_H

#include "person.h"
#include "populationevent.h"
#include "simpactpopulation.h"
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string>

// This just provides some casts towards Person instead of PersonBase
class SimpactEvent : public PopulationEvent
{
public:
        SimpactEvent() : PopulationEvent() {}
        SimpactEvent(Person* pPerson) : PopulationEvent(pPerson) {}
        SimpactEvent(Person* pPerson1, Person* pPerson2) : PopulationEvent(pPerson1, pPerson2) {}
        ~SimpactEvent() {}

        Person* getPerson(int idx) const { return reinterpret_cast<Person*>(PopulationEvent::getPerson(idx)); }
};

#endif // SIMPACTEVENT_H
