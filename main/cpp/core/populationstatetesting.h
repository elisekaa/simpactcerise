#pragma once

/**
 * \file populationstatetesting.h
 */
#include "algorithm.h"
#include "mutex.h"
#include "populationstatesimpleadvancedcommon.h"

#include <cassert>
#include <vector>

class PopulationAlgorithmTesting;
class PersonBase;

class PopulationStateTesting : public PopulationStateSimpleAdvancedCommon
{
public:
        ///
        PopulationStateTesting();

        ///
        ~PopulationStateTesting() override = default;

        ///
        ExitStatus init(bool parallel);

private:
        int64_t getNextPersonID() override;
        void    setListIndex(PersonBase* pPerson, int idx) override;
        int     getListIndex(PersonBase* pPerson) override;
        void    addAlgorithmInfo(PersonBase* pPerson) override;

private:
        bool    m_init;
        bool    m_parallel;
        int64_t m_nextPersonID;

private:
        friend class PopulationAlgorithmTesting;
};
