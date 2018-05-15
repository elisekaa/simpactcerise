#ifndef EVENTDROPOUT_H

#define EVENTDROPOUT_H

#include "simpactevent.h"

class ConfigSettings;
class ConfigWriter;
class ProbabilityDistribution;

class EventDropout : public SimpactEvent
{
public:
	EventDropout(Person *pPerson, double treatmentStartTime);
	~EventDropout();

	std::string getDescription(double tNow) const override;
	void writeLogs(const SimpactPopulation &pop, double tNow) const override;
	void fire(Algorithm *pAlgorithm, State *pState, double t) override;

	static void processConfig(ConfigSettings &config, GslRandomNumberGenerator *pRndGen);
	static void obtainConfig(ConfigWriter &config);
private:
	double getNewInternalTimeDifference(GslRandomNumberGenerator *pRndGen, const State *pState) override;
	double calculateInternalTimeInterval(const State *pState, double t0, double dt) override;
	double solveForRealTimeInterval(const State *pState, double Tdiff, double t0) override;

	double m_treatmentStartTime;

	static ProbabilityDistribution *s_pDropoutDistribution;
};

#endif // EVENTDROPOUT_H

