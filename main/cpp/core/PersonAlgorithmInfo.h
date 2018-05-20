#pragma once
/**
 * \file PersonAlgorithmInfo.h
 */

/**
 * Base class to be able to store algorithm-specific information in the
 * PersonBase object for a person in the simulation (see PersonBase::setAlgorithmInfo).
 */
class PersonAlgorithmInfo
{
public:
        ///
        PersonAlgorithmInfo() = default;

        ///
        virtual ~PersonAlgorithmInfo() = default;
};
