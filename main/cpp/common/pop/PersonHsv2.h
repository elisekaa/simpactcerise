#pragma once

#include "util.h"

#include <cassert>

class Person;
class ProbabilityDistribution;
class ConfigSettings;
class ConfigWriter;
class GslRandomNumberGenerator;

class PersonHSV2
{
public:
        enum InfectionType
        {
                None,
                Partner,
                Seed
        };

        explicit PersonHSV2(Person* pSelf);

        ~PersonHSV2() = default;

        InfectionType getInfectionType() const { return m_infectionType; }
        void          setInfected(double t, Person* pOrigin, InfectionType iType);

        bool isInfected() const
        {
                if (m_infectionType == None)
                        return false;
                return true;
        }
        double getInfectionTime() const
        {
                assert(isInfected());
                return m_infectionTime;
        }
        Person* getInfectionOrigin() const
        {
                assert(isInfected());
                return m_pInfectionOrigin;
        }

        double getHazardAParameter() const { return m_hazardAParam; }
        double getHazardB2Parameter() const { return m_hazardB2Param; }

        static void processConfig(ConfigSettings& config, GslRandomNumberGenerator* pRndGen);
        static void obtainConfig(ConfigWriter& config);

private:
        const Person* m_pSelf;

        double        m_infectionTime;
        Person*       m_pInfectionOrigin;
        InfectionType m_infectionType;
        double        m_hazardAParam;
        double        m_hazardB2Param;

        static ProbabilityDistribution* m_pADist;
        static ProbabilityDistribution* m_pB2Dist;
};
