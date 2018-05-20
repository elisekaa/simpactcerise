#pragma once

/**
 * \file populationstateadvanced.h
 */

#include "algorithm.h"
#include "mutex.h"
#include "personaleventlist.h"
#include "personbase.h"
#include "populationstatesimpleadvancedcommon.h"

#include <cassert>
#include <vector>

class PopulationAlgorithmAdvanced;

/**
 * Population state to be used when simulating with the population based
 *  algorithm in PopulationAlgorithmAdvanced, makes sure that the functions
 *  from PopulationStateInterface are implemented. */
class PopulationStateAdvanced : public PopulationStateSimpleAdvancedCommon
{
public:
        ///
        PopulationStateAdvanced();

        ///
        ~PopulationStateAdvanced() override = default;

        ///
        ExitStatus init(bool parallel);

        /// For internal use (by PersonalEventList)
        void lockPerson(PersonBase* pPerson) const;

        ///
        void unlockPerson(PersonBase* pPerson) const;

private:
        ///
        int64_t getNextPersonID() override;

        ///
        void setListIndex(PersonBase* pPerson, int idx) override;

        ///
        int getListIndex(PersonBase* pPerson) override;

        ///
        void addAlgorithmInfo(PersonBase* pPerson) override;

private:
        bool m_init;
        bool m_parallel;

        int64_t m_nextPersonID;
#ifndef DISABLEOPENMP
        Mutex                      m_nextPersonIDMutex;
        mutable std::vector<Mutex> m_personMutexes;
#endif // !DISABLEOPENMP

private:
        friend class PopulationAlgorithmAdvanced;
};
