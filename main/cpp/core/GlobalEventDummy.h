#pragma once

/**
 * \file personbase.h
 */

#include "PersonBase.h"

class GlobalEventDummy : public PersonBase
{
public:
        GlobalEventDummy() : PersonBase(GlobalEventPerson, -11111) {}
        ~GlobalEventDummy() override = default;
};
