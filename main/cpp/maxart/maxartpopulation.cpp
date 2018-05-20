#include "maxartpopulation.h"
#include "eventstudystart.h"

MaxARTPopulation::MaxARTPopulation(PopulationAlgorithmInterface& alg, PopulationStateInterface& state)
    : SimpactPopulation(alg, state)
{
        m_studyStage = PreStudy;
}

ExitStatus MaxARTPopulation::scheduleInitialEvents()
{
        ExitStatus r;
        if (!(r = SimpactPopulation::scheduleInitialEvents()))
                return r;
        if (EventStudyStart::isMaxARTStudyEnabled()) {
                auto pEvt = new EventStudyStart(); // global event
                onNewEvent(pEvt);
        }
        return ExitStatus(true);
}
