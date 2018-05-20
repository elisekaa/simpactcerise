#pragma once

/**
 * \file populationstatesimple.h
 */

#include "personbase.h"
#include "populationstatesimpleadvancedcommon.h"
#include <assert.h>
#include <vector>

class PersonAlgorithmInfoSimple : public PersonAlgorithmInfo
{
public:
        ///
        PersonAlgorithmInfoSimple() : m_listIndex(-1) {}

        ///
        ~PersonAlgorithmInfoSimple() override = default;

        ///
        void setListIndex(int idx) { m_listIndex = idx; }

        ///
        int  getListIndex() const { return m_listIndex; }

private:
        int m_listIndex;
};

/**
 * Population state to be used when simulating with the straightforward
 *  algorithm in PopulationAlgorithmSimple, makes sure that the functions
 *  from PopulationStateInterface are implemented.
 */
class PopulationStateSimple : public PopulationStateSimpleAdvancedCommon
{
public:
        ///
        PopulationStateSimple() : m_init(false) {}

        ///
        ~PopulationStateSimple() override =default;

        ///
        ExitStatus init();

private:
        ///
        int64_t getNextPersonID() override;

        ///
        void    addAlgorithmInfo(PersonBase* pPerson) override;

        ///
        void    setListIndex(PersonBase* pPerson, int idx) override;

        ///
        int     getListIndex(PersonBase* pPerson) override;

private:
        bool    m_init;
        int64_t m_nextPersonID;
};
