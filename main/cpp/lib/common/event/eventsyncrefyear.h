#ifndef EVENTSYNCREFYEAR_H

#define EVENTSYNCREFYEAR_H

#include "simpactevent.h"

class EventSyncReferenceYear : public SimpactEvent
{
public:
        EventSyncReferenceYear();
        ~EventSyncReferenceYear();

        std::string getDescription(double tNow) const override;
        void        writeLogs(const SimpactPopulation& pop, double tNow) const override;

        void fire(Algorithm* pAlgorithm, State* pState, double t) override;

        // Everything needs to be recalculated after this
        bool isEveryoneAffected() const override { return true; }

        static void processConfig(ConfigSettings& config, GslRandomNumberGenerator* pRndGen);
        static void obtainConfig(ConfigWriter& config);

        static bool   isEnabled() { return s_interval > 0; }
        static double getInterval() { return s_interval; }

private:
        double getNewInternalTimeDifference(GslRandomNumberGenerator* pRndGen, const State* pState) override;

        static double s_interval;
};

#endif // EVENTSYNCREFERENCEYEAR_H
