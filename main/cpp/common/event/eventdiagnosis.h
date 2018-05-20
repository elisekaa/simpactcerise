#pragma once

#include "hazardfunctionexp.h"
#include "simpactevent.h"

class ConfigSettings;
class ConfigWriter;
class ProbabilityDistribution;

class HazardFunctionDiagnosis : public HazardFunctionExp
{
public:
        HazardFunctionDiagnosis(Person* pPerson, double baseline, double ageFactor, double genderFactor,
                                double diagPartnersFactor, double isDiagnosedFactor, double beta, double HSV2factor);

        double evaluate(double t);

private:
        Person*      m_pPerson;
        const double m_baseline, m_ageFactor, m_genderFactor, m_diagPartnersFactor;
        const double m_isDiagnosedFactor, m_beta, m_HSV2factor;
};

class EventDiagnosis : public SimpactEvent
{
public:
        ///
        explicit EventDiagnosis(Person* pPerson);

        ///
        ~EventDiagnosis() override = default;

        ///
        std::string getDescription(double tNow) const override;

        ///
        void writeLogs(const SimpactPopulation& pop, double tNow) const override;

        ///
        void fire(Algorithm* pAlgorithm, State* pState, double t) override;

        /// Since the hazard depends on the number of diagnosed partners, every partner of this
        /// person who is infected (so diagnosis event s possible) needs to be marked as affected.
        void markOtherAffectedPeople(const PopulationStateInterface& population) override;

        ///
        static void processConfig(ConfigSettings& config, GslRandomNumberGenerator* pRndGen);

        ///
        static void obtainConfig(ConfigWriter& config);

private:
        ///
        double calculateInternalTimeInterval(const State* pState, double t0, double dt) override;

        ///
        double solveForRealTimeInterval(const State* pState, double Tdiff, double t0) override;

private:
        ///
        static double getTMax(const Person* pPerson);

private:
        static double s_baseline;
        static double s_ageFactor;
        static double s_genderFactor;
        static double s_diagPartnersFactor;
        static double s_isDiagnosedFactor;
        static double s_beta;
        static double s_tMax;
        static double s_HSV2factor;
};

