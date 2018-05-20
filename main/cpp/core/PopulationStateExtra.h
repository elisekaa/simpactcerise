#pragma once
/**
 * \file PopulationStateExtra.h
 */

/**
 * Base class to allow some extra information to be stored in each
 * state that implements PopulationStateInterface (see PopulationStateInterface::setExtraStateInfo).
 */
class PopulationStateExtra
{
public:
        PopulationStateExtra() = default;

        virtual ~PopulationStateExtra() = default;
};
