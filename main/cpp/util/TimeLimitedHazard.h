#pragma once

/**
 * \file hazardfunction.h
 */

#include "Hazard.h"

/**
 * Starting from a particular hazard, this modified hazard returns a constant
 *  value for times larger that a certain value.
 *
 *  The advantage of this, is that hazards which could not be used in the mNRM
 *  because a mapping of internal time dT to real-world time dt was impossible,
 *  now become useable.
 *
 *  For example, if the hazard \f$h(s) = exp(-s) \f$ is used, there's a problem
 *  for the mNRM: in this algorithm, a random number \f$ dT \f$ is first picked
 *  and then mapped onto a real-world time by solving the following equation for
 *  \f$ dt \f$: \f[ dT = \int_{t_0}^{t_0 + dt} h(s) ds \f]
 *
 *  Now, the integral of \f$ h(s) \f$ is bounded, with \f[ \int_0^{\infty} h(s) ds = 1 \f]
 *  Because \f$ dT \f$ can easily be larger than one, this means that calculating the
 *  corresponding \f$ dt \f$ value by solving the integral equation above, may simply
 *  not be possible.
 *
 *  By using a modified hazard \f$ g(s) \f$ instead, where
 *  \f[ g(t) = \left\{
 *			\begin{array}{ll}
 *				h(t) & {\rm if\ } t < t_{max} \\
 *				h(t_{max}) & {\rm if\ } t \ge t_{max}
 *			\end{array}
 *			\right.
 *		\f]
 * this integral becomes solvable again.
 *
 * For more information, some calculations can be found in <a href="hazard_tmax.pdf">hazard_tmax.pdf</a>
 */
class TimeLimitedHazard : public Hazard
{
public:
        /** This constructor specifies that the base hazard \c h should be used for
         *  times smaller than \c tMax, and that the constant value h(tMax) should
         *  be the hazard for times larger than tMax. */
        TimeLimitedHazard(Hazard& h, double tMax) : m_h(h), m_tMax(tMax) {}
        ~TimeLimitedHazard() {}

        double evaluate(double t);
        double calculateInternalTimeInterval(double t0, double dt);
        double solveForRealTimeInterval(double t0, double Tdiff);

private:
        Hazard& m_h;
        double  m_tMax;
};

inline double TimeLimitedHazard::evaluate(double t)
{
        if (t < m_tMax)
                return m_h.evaluate(t);
        return m_h.evaluate(m_tMax);
}

// something small to prevent division by zero
#define TIMELIMITEDHAZARDFUNCTION_SMALLNUMBER 1e-100

inline double TimeLimitedHazard::calculateInternalTimeInterval(double t0, double dt)
{
        if (t0 >= m_tMax) // we're in the regime where the hazard has become constant
                return (m_h.evaluate(m_tMax) + TIMELIMITEDHAZARDFUNCTION_SMALLNUMBER) * dt;

        if (t0 + dt <= m_tMax)
                return m_h.calculateInternalTimeInterval(t0, dt);

        double tMaxMinT0 = m_tMax - t0;
        double TdiffMax  = m_h.calculateInternalTimeInterval(t0, tMaxMinT0);

        return TdiffMax + m_h.evaluate(m_tMax) * (dt - tMaxMinT0);
}

inline double TimeLimitedHazard::solveForRealTimeInterval(double t0, double Tdiff)
{
        if (t0 >= m_tMax) // we're in the regime where the hazard has become constant
                return Tdiff / (m_h.evaluate(m_tMax) + TIMELIMITEDHAZARDFUNCTION_SMALLNUMBER);

        double tMaxMinT0 = m_tMax - t0;
        double TdiffMax  = m_h.calculateInternalTimeInterval(t0, tMaxMinT0);

        if (TdiffMax >= Tdiff) // we haven't reached tMax yet
                return m_h.solveForRealTimeInterval(t0, Tdiff);

        return (Tdiff - TdiffMax) / m_h.evaluate(m_tMax) + tMaxMinT0;
}
