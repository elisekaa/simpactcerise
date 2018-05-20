#pragma once

#include "ExitStatus.h"

#include <cassert>
#include <vector>

class GridValues
{
public:
        ///
        GridValues() = default;

        ///
        virtual ~GridValues() = default;

        ///
        virtual ExitStatus init(const std::string& fileName, bool noNegativeValues = true, bool flipY = false) = 0;

        ///
        virtual int getWidth() const = 0;

        ///
        virtual int getHeight() const = 0;

        ///
        virtual double getValue(int x, int y) const = 0;

        ///
        virtual void setValue(int x, int y, double v) = 0;

        ///
        virtual bool isYFlipped() const = 0;
};
