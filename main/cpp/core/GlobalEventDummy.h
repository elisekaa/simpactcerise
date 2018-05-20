#pragma once

/**
 * \file personbase.h
 */

#include "personbase.h"

class GlobalEventDummy : public PersonBase
{
public:
        GlobalEventDummy() : PersonBase(GlobalEventPerson, -11111) {}
        ~GlobalEventDummy() override = default;
};
