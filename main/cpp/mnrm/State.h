#pragma once
/**
 * \file State.h
 */

#include "ExitStatus.h"

#include <cstdint>
#include <vector>

class Mutex;

/**
 * This is a base class describing the simulation state of an mNRM algorithm.
 */
class State
{
public:
        ///
        State();

        ///
        virtual ~State();

        /// Retrieve the current simulation time, which is stored by the Algorithm
        /// instance in use (note that until Algorithm::evolve is first called, the
        /// time has it's initial value of zero, may be important when starting the
        /// simulation from another time).
        double getTime() const { return m_time; }

        /// Set the simulation time, which is normally only done by the Algorithm
        /// in use (but may be necessary when starting the simulation from a time
        /// different than zero, see State::getTime).
        void setTime(double t) { m_time = t; }

        /// Protected by a mutex
        void setAbortAlgorithm(const std::string& reason) const;

        /// Will only be called from the main simulation thread
        void        clearAbort();

        ///
        bool        shouldAbortAlgorithm() const { return m_abort; }

        ///
        std::string getAbortReason() const;

private:
        double              m_time;
        mutable bool        m_abort;
        mutable Mutex*      m_pAbortMutex;
        mutable std::string m_abortReason;
};
