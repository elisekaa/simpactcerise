#pragma once

#include "ExitStatus.h"

#include <cstdint>

class ConfigSettings;
class GslRandomNumberGenerator;
class SimpactPopulationConfig;
class PopulationDistributionCSV;

void       processNonInterventionEventConfig(ConfigSettings& config, GslRandomNumberGenerator* pRndGen);
ExitStatus configure(ConfigSettings& config, SimpactPopulationConfig& populationConfig,
                     PopulationDistributionCSV& ageDist, GslRandomNumberGenerator* pRndGen, double& tMax,
                     int64_t& maxEvents);
