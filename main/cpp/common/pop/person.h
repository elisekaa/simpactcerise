#pragma once

#include "PersonFamily.h"
#include "PersonHiv.h"
#include "PersonHsv2.h"
#include "PersonRelations.h"
#include "distribution/probabilitydistribution2d.h"
#include "personbase.h"
#include "util.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

class PersonImpl;
class Person;
class Man;
class Woman;
class GslRandomNumberGenerator;
class ConfigSettings;
class ConfigWriter;
class DiscreteDistribution2D;
class ProbabilityDistribution;
class VspModel;

class Person : public PersonBase
{
public:
        ///
        Person(double dateOfBirth, Gender g);

        ///
        ~Person() override;

        PersonImpl* getImplementationSpecificPart() { return m_pPersonImpl; }

        bool isMan() const { return getGender() == Male; }
        bool isWoman() const { return getGender() == Female; }

        // Family stuff
        void setFather(Man* pFather) { m_family.setFather(pFather); }
        void setMother(Woman* pMother) { m_family.setMother(pMother); }

        Man*   getFather() const { return m_family.getFather(); }
        Woman* getMother() const { return m_family.getMother(); }

        void    addChild(Person* pPerson) { m_family.addChild(pPerson); }
        bool    hasChild(Person* pPerson) const { return m_family.hasChild(pPerson); }
        int     getNumberOfChildren() const { return m_family.getNumberOfChildren(); }
        Person* getChild(int idx);

        // Relationship stuff
        int     getNumberOfRelationships() const { return m_relations.getNumberOfRelationships(); }
        void    startRelationshipIteration() { m_relations.startRelationshipIteration(); }
        Person* getNextRelationshipPartner(double& formationTime)
        {
                return m_relations.getNextRelationshipPartner(formationTime);
        }
        int getNumberOfDiagnosedPartners() { return m_relations.getNumberOfDiagnosedPartners(); }

        bool hasRelationshipWith(Person* pPerson) const { return m_relations.hasRelationshipWith(pPerson); }

        // WARNING: do not use these during relationship iteration
        void addRelationship(Person* pPerson, double t) { m_relations.addRelationship(pPerson, t); }
        void removeRelationship(Person* pPerson, double t, bool deathBased)
        {
                m_relations.removeRelationship(pPerson, t, deathBased);
        }

        // result is negative if no relations formed yet
        double getLastRelationshipChangeTime() const { return m_relations.getLastRelationshipChangeTime(); }

        void   setSexuallyActive(double t) { m_relations.setSexuallyActive(t); }
        bool   isSexuallyActive() const { return m_relations.isSexuallyActive(); }
        double getDebutTime() const { return m_relations.getDebutTime(); }

        double getFormationEagernessParameter() const { return m_relations.getFormationEagernessParameter(); }
        double getPreferredAgeDifference() const { return m_relations.getPreferredAgeDifference(); }
        double getFormationEagernessParameterMSM() const
        {
                assert(isMan());
                return m_relations.getFormationEagernessParameterMSM();
        }
        double getPreferredAgeDifferenceMSM() const
        {
                assert(isMan());
                return m_relations.getPreferredAgeDifferenceMSM();
        }

        // NOTE: this ignores the call if already in the list
        void    addPersonOfInterest(Person* pPerson) { m_relations.addPersonOfInterest(pPerson); }
        void    removePersonOfInterest(Person* pPerson) { m_relations.removePersonOfInterest(pPerson); }
        void    clearPersonsOfInterest() { m_relations.clearPersonsOfInterest(); }
        int     getNumberOfPersonsOfInterest() const { return m_relations.getNumberOfPersonsOfInterest(); }
        Person* getPersonOfInterest(int idx) const { return m_relations.getPersonOfInterest(idx); }

        // HIV stuff
        PersonHIV&       hiv() { return m_hiv; }
        const PersonHIV& hiv() const { return m_hiv; }

        // HSV2 stuff
        PersonHSV2&       hsv2() { return m_hsv2; }
        const PersonHSV2& hsv2() const { return m_hsv2; }

        // This is a per person value
        double getSurvivalTimeLog10Offset() const { return m_hiv.getSurvivalTimeLog10Offset(); }

        static void processConfig(ConfigSettings& config, GslRandomNumberGenerator* pRndGen);
        static void obtainConfig(ConfigWriter& config);

        void writeToPersonLog();
        void writeToTreatmentLog(double dropoutTime, bool justDied);
        void writeToLocationLog(double tNow);

        Point2D getLocation() const { return m_location; }
        void    setLocation(Point2D loc, double tNow)
        {
                m_location     = loc;
                m_locationTime = tNow;
        }
        double getLocationTime() const { return m_locationTime; }

        double                            getDistanceTo(Person* pPerson);
        static ProbabilityDistribution2D* getPopulationDistribution() { return m_pPopDist; }

private:
        PersonFamily    m_family;
        PersonRelations m_relations;
        PersonHIV       m_hiv;
        PersonHSV2      m_hsv2;

        Point2D     m_location;
        double      m_locationTime;
        PersonImpl* m_pPersonImpl;

        static ProbabilityDistribution2D* m_pPopDist;
};

class Man : public Person
{
public:
        explicit Man(double dateOfBirth) : Person(dateOfBirth, Male) {}
        ~Man() override = default;
};

class Woman : public Person
{
public:
        explicit Woman(double dateOfBirth) : Person(dateOfBirth, Female), m_pregnant(false) {}
        ~Woman() override = default;
        void setPregnant(bool f) { m_pregnant = f; }
        bool isPregnant() const { return m_pregnant; }

private:
        bool m_pregnant;
};

inline Man* MAN(Person* pPerson)
{
        assert(pPerson != 0);
        assert(pPerson->getGender() == PersonBase::Male);
        return dynamic_cast<Man*>(pPerson);
}

inline Woman* WOMAN(Person* pPerson)
{
        assert(pPerson != 0);
        assert(pPerson->getGender() == PersonBase::Female);
        return dynamic_cast<Woman*>(pPerson);
}

inline Person* Person::getChild(int idx)
{
        Person* pChild = m_family.getChild(idx);
        assert((isMan() && pChild->getFather() == this) || (isWoman() && pChild->getMother() == this));
        return pChild;
}

inline double Person::getDistanceTo(Person* pPerson)
{
        assert(this != pPerson);
        Point2D p  = pPerson->m_location;
        double  dx = p.x - m_location.x;
        double  dy = p.y - m_location.y;

        return std::sqrt(dx * dx + dy * dy);
}
