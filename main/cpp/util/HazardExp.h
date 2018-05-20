#pragma once

/**
 * \file HazardExp.h
 */

#include "Hazard.h"

#include <cmath>

/**
 * Helper class for time dependent exponential hazards.
 * This is a helper class for hazards of the form \f[ h = \exp(A+Bt) \f].
 */
class HazardExp : public Hazard
{
public:
        /// Constructor which specifies the parameters in exp(A+Bt).
        explicit HazardExp(double A = 0, double B = 0) : m_A(A), m_B(B) {}

        ///
        ~HazardExp() override = default;

        ///
        double evaluate(double t) override;

        ///
        double calculateInternalTimeInterval(double t0, double dt) override;

        ///
        double solveForRealTimeInterval(double t0, double Tdiff) override;

protected:
        void setAB(double A, double B)
        {
                m_A = A;
                m_B = B;
        }

private:
        double m_A, m_B;
};

inline double HazardExp::evaluate(double t) { return std::exp(m_A + m_B * t); }

inline double HazardExp::calculateInternalTimeInterval(double t0, double dt)
{
        return (m_B == 0) ? dt * std::exp(m_A) : (std::exp(m_A + m_B * t0) / m_B) * (std::exp(m_B * dt) - 1.0);
}

inline double HazardExp::solveForRealTimeInterval(double t0, double Tdiff)
{
        return (m_B == 0) ? Tdiff / std::exp(m_A) : (std::log((m_B * Tdiff) / std::exp(m_A + m_B * t0) + 1.0)) / m_B;
}
