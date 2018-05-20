#pragma once
/**
 * \file PopulationAlgorithmInterface.h
 */

#include "State.h"
#include "ExitStatus.h"

class PopulationEvent;
class PopulationAlgorithmAboutToFireInterface;
class GslRandomNumberGenerator;

/**
 * An interface for a population based mNRM algorithm.
 */
class PopulationAlgorithmInterface
{
public:
        ///
        PopulationAlgorithmInterface() = default;

        ///
        virtual ~PopulationAlgorithmInterface() = default;

        /// Abstract function to initialize the implementation used.
        virtual ExitStatus init() = 0;

        /**
         * This should be called to actually start the simulation, do not call
         *  Algorithm::evolve for this.
         *  \param tMax Stop the simulation if the simulation time exceeds the specified time. Upon
         *              completion of the function, this variable will contain the actual simulation
         *              time stopped.
         *  \param maxEvents If positive, the simulation will stop if this many events have been
         *                   executed. Set to a negative value to disable this limit. At the end of
         *                   the simulation, this variable will contain the number of events executed.
         *  \param startTime The start time of the simulation, can be used to continue where a previous
         *                   call to this function left off.
         */
        virtual ExitStatus run(double& tMax, int64_t& maxEvents, double startTime = 0) = 0;

        /**
         * Allows you to set the action that needs to be performed before firing an
         *  event dynamically.
         *
         *  When implementing a new population based algorithm you must make sure that
         *  this way the action performed by Algorithm::onAboutToFire can be changed
         *  at run time. */
        virtual void setAboutToFireAction(PopulationAlgorithmAboutToFireInterface* pAction) = 0;

        /// When a new event has been created, it must be injected into the simulation using
        /// this function.
        virtual void onNewEvent(PopulationEvent* pEvt) = 0;

        /** Must return the simulation tilme of the algorithm. */
        virtual double getTime() const = 0;

        /** Must return the random number generator used by the algorithm. */
        virtual GslRandomNumberGenerator* getRandomNumberGenerator() const = 0;
};

