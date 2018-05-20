#pragma once
/**
 * \file PopulationAlgorithmAboutToFireInterface.h
 */

class PopulationEvent;

/**
 * An interface to allow a member function PopulationAlgorithmAboutToFireInterface::onAboutToFire
 * to be called (see PopulationAlgorithmInterface::setAboutToFireAction).
 */
class PopulationAlgorithmAboutToFireInterface
{
public:
        ///
        PopulationAlgorithmAboutToFireInterface() = default;

        ///
        virtual ~PopulationAlgorithmAboutToFireInterface() = default;

        /// If set using PopulationAlgorithmInterface::setAboutToFireAction, this
        /// function will be called right before firing the specified event.
        virtual void onAboutToFire(PopulationEvent* pEvt) = 0;
};
