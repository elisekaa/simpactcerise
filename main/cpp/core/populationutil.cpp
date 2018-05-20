#include "populationutil.h"
#include "populationalgorithmadvanced.h"
#include "populationalgorithmsimple.h"
#include "populationalgorithmtesting.h"
#include "populationstateadvanced.h"
#include "populationstatesimple.h"
#include "populationstatetesting.h"

using namespace std;

ExitStatus PopulationUtil::selectAlgorithmAndState(const string& algo, GslRandomNumberGenerator& rng, bool parallel,
                                               PopulationAlgorithmInterface** ppAlgo,
                                               PopulationStateInterface**     ppState)
{
        if (algo == "opt") {
                if (!parallel) // The new version appears to be better only for the serial version
                {
                        // TODO: figure out how to get this to work better in this algorithm
                        // Event::setCheckInverse(true); // Only does something in release mode
                        auto pPopState = new PopulationStateTesting();
                        *ppState                          = pPopState;
                        *ppAlgo                           = new PopulationAlgorithmTesting(*pPopState, rng, parallel);
                } else {
                        // TODO: figure out how to get this to work better in this algorithm
                        // Event::setCheckInverse(true); // Only does something in release mode
                        auto pPopState = new PopulationStateAdvanced();
                        *ppState                           = pPopState;
                        *ppAlgo                            = new PopulationAlgorithmAdvanced(*pPopState, rng, parallel);
                }
        } else if (algo == "simple") {
                Event::setCheckInverse(true); // Only does something in release mode
                auto pPopState = new PopulationStateSimple();
                *ppState                         = pPopState;
                *ppAlgo                          = new PopulationAlgorithmSimple(*pPopState, rng, parallel);
        } else
                return ExitStatus("Invalid algorithm: " + algo);

        ExitStatus r = (*ppAlgo)->init();
        if (!r) {
                delete *ppState;
                delete *ppAlgo;
                *ppState = 0;
                *ppAlgo  = 0;
                return r;
        }

        return ExitStatus(true);
}
