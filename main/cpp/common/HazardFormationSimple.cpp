#include "HazardFormationSimple.h"

#include <cassert>

HazardFormationSimple::HazardFormationSimple(const Person* pPerson1, const Person* pPerson2, double tr,
                                                             double a0, double a1, double a2, double a3, double a4,
                                                             double a5, double Dp, double b)
    : m_pPerson1(pPerson1), m_pPerson2(pPerson2), m_tr(tr), m_a0(a0), m_a1(a1), m_a2(a2), m_a3(a3), m_a4(a4), m_a5(a5),
      m_Dp(Dp), m_b(b)
{
}

double HazardFormationSimple::evaluate(double t)
{
        return std::exp(getLnB() + getC() * t);
}

double HazardFormationSimple::calculateInternalTimeInterval(double t0, double dt)
{
        assert(t0 - m_tr > -1.0e-10); // slightly negative is possible due to finite precision and error
        const double C  = getC();
        return (C == 0) ? getB() * dt : (getE(t0) / C) * (std::exp(C * dt) - 1.0);
}

double HazardFormationSimple::solveForRealTimeInterval(double t0, double Tdiff)
{
        assert(t0 - m_tr > -1.0e-10); // slightly negative is possible due to finite precision and error
        const double C  = getC();
        return (C == 0) ? Tdiff / getB() : (1.0 / C) * std::log((C / getE(t0)) * Tdiff + 1.0);
}
