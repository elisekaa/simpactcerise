#pragma once
/*
 *  This is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *  The software is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with the software. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2018, Kuylen E et. al.
 */

/**
 * @file
 * Header file for AidsTimeOfDeathUtility.
 */

#include <cassert>

// This will do a hazard-like calculation. It would be easier if we could
// just use a similar hazard in the AIDS based mortality event, but this
// is not possible since we also need to schedule the AIDS stage and final
// AIDS stage a specific amount of time before death

class Person;

class AidsTimeOfDeathUtility
{
public:
        ///
        AidsTimeOfDeathUtility();

        ///
        ~AidsTimeOfDeathUtility() = default;

        ///
        void changeTimeOfDeath(double currentTime, const Person* pPerson);

        ///
        double getTimeOfDeath() const
        {
                assert(m_timeOfDeath >= 0);
                return m_timeOfDeath;
        }

        ///
        double getInfectionTime() const
        {
                assert(m_infectionTime >= 0);
                return m_infectionTime;
        }

private:
        double m_internalTimeRemaining;
        double m_infectionTime;
        double m_timeOfDeath;
        double m_prevHazard;
        double m_prevTime;
};

