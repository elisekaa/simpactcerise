#pragma once

#include "pop/simpactpopulation.h"

#include <cassert>

class MaxARTPopulation : public SimpactPopulation
{
public:
        enum StudyStage
        {
                PreStudy,
                InStudy,
                PostStudy
        };

        ///
        MaxARTPopulation(PopulationAlgorithmInterface& alg, PopulationStateInterface& state);

        ///
        ~MaxARTPopulation() override = default;

        ///
        StudyStage getStudyStage() const { return m_studyStage; }

        ///
        void setInStudy()
        {
                assert(m_studyStage == PreStudy);
                m_studyStage = InStudy;
        }

        ///
        void setStudyEnded()
        {
                assert(m_studyStage == InStudy);
                m_studyStage = PostStudy;
        }

protected:
        ///
        ExitStatus scheduleInitialEvents() override;

protected:
        StudyStage m_studyStage;
};

inline MaxARTPopulation& MAXARTPOPULATION(State* pState)
{
        assert(pState != 0);
        auto& state = dynamic_cast<PopulationStateInterface&>(*pState);
        assert(state.getExtraStateInfo() != 0);
        return dynamic_cast<MaxARTPopulation&>(*state.getExtraStateInfo());
}

inline const MaxARTPopulation& MAXARTPOPULATION(const State* pState)
{
        assert(pState != 0);
        const auto& state = dynamic_cast<const PopulationStateInterface&>(*pState);
        assert(state.getExtraStateInfo() != 0);
        return dynamic_cast<const MaxARTPopulation&>(*state.getExtraStateInfo());
}
