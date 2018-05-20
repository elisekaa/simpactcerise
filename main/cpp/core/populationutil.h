#pragma once

#include "ExitStatus.h"
#include "PopulationAlgorithmInterface.h"
#include "PopulationStateInterface.h"

class PopulationUtil
{
public:
        static ExitStatus selectAlgorithmAndState(const std::string& algo, GslRandomNumberGenerator& rng, bool parallel,
                                                  PopulationAlgorithmInterface** ppAlgo,
                                                  PopulationStateInterface**     ppState);
};
