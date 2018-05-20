#include "Event.h"
#include "debugwarning.h"
#include "gslrandomnumbergenerator.h"

#include <cmath>

#ifndef NDEBUG
bool Event::s_checkInverse = false;
#endif // NDEBUG

Event::Event()
{
        m_Tdiff         = -10000000.0; // should trigger an assertion in debug mode
        m_tLastCalc     = -1;
        m_tEvent        = -2;
        m_willBeRemoved = false;

#ifndef NDEBUG
        if (s_checkInverse)
                DEBUGWARNING("debug code to check solveForRealTimeInterval <-> calculateInternalTimeInterval "
                             "compatibility is enabled")
#endif // !NDEBUG
}

Event::~Event() {}

void Event::generateNewInternalTimeDifference(GslRandomNumberGenerator* pRndGen, const State* pState)
{
        m_Tdiff = getNewInternalTimeDifference(pRndGen, pState);
        setNeedEventTimeCalculation();
}

double Event::getNewInternalTimeDifference(GslRandomNumberGenerator* pRndGen, const State* pState)
{
        double r = pRndGen->pickRandomDouble();
        return -std::log(r);
}

// In this default implementation there's no difference between internal time and real world time,
// meaning that for a fixed time event, you'd just need to implement the getNewInternalTimeDifference
// to generate a real world time interval
double Event::calculateInternalTimeInterval(const State* pState, double t0, double dt) { return dt; }

double Event::solveForRealTimeInterval(const State* pState, double Tdiff, double t0) { return Tdiff; }

void Event::fire(Algorithm* pAlgorithm, State* pState, double t)
{
        // test implementation: nothing happens
}

ExitStatus Event::setCheckInverse(bool check)
{
#ifdef NDEBUG
        return "Double checking the time interval mapping is not supported in release mode";
#else
        s_checkInverse = check;
        return ExitStatus(true);
#endif // NDEBUG
}
