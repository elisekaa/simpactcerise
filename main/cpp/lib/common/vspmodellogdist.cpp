#include "vspmodellogdist.h"
#include "distribution/probabilitydistribution.h"
#include "distribution/probabilitydistribution2d.h"
#include "gslrandomnumbergenerator.h"
#include "util.h"
#include <assert.h>
#include <cmath>
#include <iostream>

using namespace std;

VspModelLogDist::VspModelLogDist(ProbabilityDistribution2D* pDist2D, ProbabilityDistribution* pAltSeedDist,
                                 GslRandomNumberGenerator* pRndGen)
    : VspModel(pRndGen)
{
        m_pDist2D      = pDist2D;
        m_pAltSeedDist = pAltSeedDist;

        assert(pDist2D && pDist2D->hasMarginalsAndConditionals());
}

VspModelLogDist::~VspModelLogDist()
{
        delete m_pAltSeedDist;
        delete m_pDist2D;
}

double VspModelLogDist::pickSetPointViralLoad()
{
        double x;

        if (m_pAltSeedDist) // We want to use an alternative seeding distribution
        {
                x = m_pAltSeedDist->pickNumber();
        } else {
                x = m_pDist2D->pickMarginalX();
        }

        return std::pow(10.0, x); // use this as power of 10
}

double VspModelLogDist::inheritSetPointViralLoad(double VspInfector)
{
        double x = VspInfector;
        x        = std::log10(x); // have to switch back to the log scale

        double y = m_pDist2D->pickConditionalOnX(x);

        return std::pow(10.0, y);
}
