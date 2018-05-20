#pragma once
/**
 * \file PopulationStateInterface.h
 */

#include "ExitStatus.h"
#include "State.h"

class PersonBase;
class PopulationEvent;
class PopulationStateExtra;
class GslRandomNumberGenerator;

/** Interface for a simulation state for the population-based algorithm, specifying
 *  member functions that need to be implemented. */
class PopulationStateInterface : public State
{
public:
        PopulationStateInterface() { m_pExtraState = 0; }

        ~PopulationStateInterface() override = default;

        /** Returns a list to the current living members in the population, introduced
         *  into the simulation using PopulationStateInterface::addNewPerson. */
        virtual PersonBase** getAllPeople() = 0;

        /** Same as PopulationStateInterface::getAllPeople, but only the men are returned. */
        virtual PersonBase** getMen() = 0;

        /** Same as PopulationStateInterface::getAllPeople, but only the women are returned. */
        virtual PersonBase** getWomen() = 0;

        /** Returns the people who were part of the simulation but who are now deceased
         *  (intended for result analysis, not to be used during the simulation). */
        virtual PersonBase** getDeceasedPeople() = 0;

        /** Returns the number of people in the array returned by PopulationStateInterface::getAllPeople. */
        virtual int getNumberOfPeople() const = 0;

        /** Returns the number of people in the array returned by PopulationStateInterface::getMen. */
        virtual int getNumberOfMen() const = 0;

        /** Returns the number of people in the array returned by PopulationStateInterface::getWomen. */
        virtual int getNumberOfWomen() const = 0;

        /** Returns the number of people in the array returned by PopulationStateInterface::getDeceasedPeople. */
        virtual int getNumberOfDeceasedPeople() const = 0;

        /** When a new person is introduced into the population, this function must be
         *  used to tell the simulation about this. In essence this function will make
         *  sure that the person appears in the arrays returned by PopulationStateInterface::getAllPeople,
         *  PopulationStateInterface::getMen and PopulationStateInterface::getWomen. */
        virtual void addNewPerson(PersonBase* pPerson) = 0;

        /** When a person has died, this function must be called to inform the simulation about
         *  this. This function will set the time of death for the person and will remove the
         *  person from the arrays with living people (PopulationStateInterface::getAllPeople,
         *  PopulationStateInterface::getMen and PopulationStateInterface::getWomen). */
        virtual void setPersonDied(PersonBase* pPerson) = 0;

        /** This should only be called from within the PopulationEvent::markOtherAffectedPeople function,
         *  to indicate which other persons are also affected by the event (other than the persons
         *  mentioned in the event constructor. */
        virtual void markAffectedPerson(PersonBase* pPerson) const = 0;

        /** This allows you to store additional information for a state that implements this
         *  PopulationStateInterface class, note that this is _not_ automatically deleted in
         *  the destructor. */
        void setExtraStateInfo(PopulationStateExtra* pExtra) { m_pExtraState = pExtra; }

        /** Retrieves the PopulationStateExtra instance that was stored using
         *  PopulationStateInterface::setExtraStateInfo. */
        PopulationStateExtra* getExtraStateInfo() const { return m_pExtraState; }

private:
        PopulationStateExtra* m_pExtraState;
};
