#pragma once

#include <cassert>

class GslRandomNumberGenerator;

class VspModel
{
public:
        ///
        explicit VspModel(GslRandomNumberGenerator* pRndGen) : m_pRndGen(pRndGen) { assert(pRndGen != 0); }

        ///
        virtual ~VspModel() = default;

        ///
        virtual double pickSetPointViralLoad() = 0;

        ///
        virtual double inheritSetPointViralLoad(double VspInfector) = 0;

        ///
        GslRandomNumberGenerator* getRandomNumberGenerator() const
        {
                assert(m_pRndGen != 0);
                return m_pRndGen;
        }

private:
        mutable GslRandomNumberGenerator* m_pRndGen;
};
