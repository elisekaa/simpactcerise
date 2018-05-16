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
 * Implementation for AidsTimeOfDeathUtility.
 */

#include "AidsTimeOfDeathUtility.h"
#include "event/eventaidsmortality.h"
#include "pop/person.h"

AidsTimeOfDeathUtility::AidsTimeOfDeathUtility()
        : m_internalTimeRemaining(-1.0), m_infectionTime(-1.0), m_timeOfDeath(-1.0), m_prevHazard(-1.0),
          m_prevTime(-1.0)
{

}

void AidsTimeOfDeathUtility::changeTimeOfDeath(double currentTime, const Person* pPerson)
{
        assert(pPerson && pPerson->hiv().isInfected());
        double survivalTime = EventAIDSMortality::getExpectedSurvivalTime(pPerson);
        double newHazard    = 1.0 / survivalTime;

        if (m_internalTimeRemaining < 0) {
                m_internalTimeRemaining = 1.0;
                m_infectionTime         = currentTime;
        } else {
                assert(m_internalTimeRemaining <= 1.0);
                double dt = currentTime - m_prevTime;
                m_internalTimeRemaining -= dt * m_prevHazard;
                assert(m_internalTimeRemaining > -1e-10);
        }

        m_prevHazard  = newHazard;
        m_prevTime    = currentTime;
        m_timeOfDeath = currentTime + m_internalTimeRemaining / newHazard;
}
