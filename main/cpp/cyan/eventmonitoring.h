#pragma once

#include "event/simpactevent.h"

class ConfigSettings;
class ConfigWriter;
class PieceWiseLinearFunction;

class EventMonitoring : public SimpactEvent
{
public:
        ///
        explicit EventMonitoring(Person* pPerson, bool scheduleImmediately = false);

        ///
        ~EventMonitoring() override = default;

        ///
        std::string getDescription(double tNow) const override;

        ///
        void writeLogs(const SimpactPopulation& pop, double tNow) const override;

        ///
        void fire(Algorithm* pAlgorithm, State* pState, double t) override;

        ///
        static void processConfig(ConfigSettings& config, GslRandomNumberGenerator* pRndGen);

        ///
        static void obtainConfig(ConfigWriter& config);

private:
        ///
        bool isEligibleForTreatment(double t);

        ///
        bool isWillingToStartTreatment(double t, GslRandomNumberGenerator* pRndGen);

        ///
        double getNewInternalTimeDifference(GslRandomNumberGenerator* pRndGen, const State* pState) override;

private:
        bool m_scheduleImmediately;

private:
        static double                   s_treatmentVLLogFrac;
        static double                   s_cd4Threshold;
        static PieceWiseLinearFunction* s_pRecheckInterval;
};