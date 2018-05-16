#include "populationdistribution.h"
#include "csvfile.h"
#include "distribution/discretedistribution.h"
#include <iostream>

PopulationDistribution::PopulationDistribution(GslRandomNumberGenerator* pRndGen) { m_pRndGen = pRndGen; }

PopulationDistribution::~PopulationDistribution() {}
