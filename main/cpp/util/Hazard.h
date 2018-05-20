#pragma once

/**
 * \file hazardfunction.h
 */

/**
 * Abstract base class which can be used for a hazard.
 *
 *  If this way of implementing a hazard is used, the parameters for the hazard must
 *  be specified using the constructor of a derived class. The advantage of this
 *  is that the functions HazardFunction::evaluate, HazardFunction::calculateInternalTimeInterval
 *  and HazardFunction::solveForRealTimeInterval are implemented in the derived class,
 *  allowing you to use different hazard implementations as parameter to some other
 *  function.
 */
class Hazard
{
public:
        ///
        Hazard() = default;

        ///
        virtual ~Hazard() = default;

        /// Evaluate the hazard at time \c t.
        virtual double evaluate(double t) = 0;

        /// Map the real-world time \c dt to an internal time interval.
        /// This calculates: \f[ dT = \int_{t_0}^{t_0 + dt} h(s) ds \f]
        virtual double calculateInternalTimeInterval(double t0, double dt) = 0;

        /// For the specified internal time interval Tdiff, calculate the
        /// corresponding real-world time interval.
        /// This solves the following equation for \f$ dt \f$: \f[ Tdiff = \int_{t_0}^{t_0 + dt} h(s) ds \f]
        virtual double solveForRealTimeInterval(double t0, double Tdiff) = 0;

        /// NOTE: this is just for debugging/testing, not meant to be used to evaluate hazards!
        double integrateNumerically(double t0, double dt);

private:
        static double staticEvaluationFunction(double t, void* pParams);
};
