#include "populationdistribution.h"
#include "distribution/discretedistribution.h"
#include "csvfile.h"
#include <iostream>

PopulationDistribution::PopulationDistribution(GslRandomNumberGenerator *pRndGen)
{
	m_pRndGen = pRndGen;
}

PopulationDistribution::~PopulationDistribution()
{
}

