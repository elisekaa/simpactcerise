#pragma once

#include "ExitStatus.h"
#include "point2d.h"

#include <algorithm>
#include <utility>
#include <vector>

/** This class can be used to represent a polygon. */
class Polygon2D
{
public:
        Polygon2D() { m_numCoords = 0; }
        virtual ~Polygon2D() {}

        ExitStatus init(const std::vector<double>& xCoords, const std::vector<double>& yCoords);
        ExitStatus init(const std::vector<std::pair<double, double>>& points);
        ExitStatus init(const std::vector<Point2D>& points);
        bool   isInside(double x, double y) const;
        int    getNumberOfPoints() const { return m_numCoords; }

private:
        std::vector<std::pair<double, double>> m_xyCoords;
        int                                    m_numCoords;
};

inline ExitStatus Polygon2D::init(const std::vector<double>& xCoords, const std::vector<double>& yCoords)
{
        if (xCoords.size() != yCoords.size()) {
                return ExitStatus("Number of X and Y coordinates is not the same");
        }
        std::vector<std::pair<double, double>> points(xCoords.size());
        for (size_t i = 0; i < xCoords.size(); i++) {
                points[i] = std::make_pair(xCoords[i], yCoords[i]);
        }
        return init(points);
}

inline ExitStatus Polygon2D::init(const std::vector<std::pair<double, double>>& points)
{
        if (points.size() < 3) {
                return ExitStatus("Too few points to be a polygon");
        }
        m_numCoords = (int)points.size();
        m_xyCoords.resize(m_numCoords + 1);

        for (int i = 0; i < m_numCoords; i++)
                m_xyCoords[i] = points[i];

        m_xyCoords[m_numCoords] = points[0];

        return ExitStatus(true);
}

inline ExitStatus Polygon2D::init(const std::vector<Point2D>& points)
{
        if (points.size() < 3) {
                return ExitStatus("Too few points to be a polygon");
        }
        m_numCoords = points.size();
        m_xyCoords.resize(m_numCoords + 1);
        for (int i = 0; i < m_numCoords; i++)
                m_xyCoords[i] = std::make_pair(points[i].x, points[i].y);

        m_xyCoords[m_numCoords] = std::make_pair(points[0].x, points[0].y);
        return ExitStatus(true);
}

inline bool Polygon2D::isInside(double x, double y) const
{
        int intersections = 0;

        for (int i = 0; i < m_numCoords; i++) {
                double y1 = m_xyCoords[i].second;
                double y2 = m_xyCoords[i + 1].second;
                double Y1 = y1;
                double Y2 = y2;

                if (Y2 < Y1) {
                        double tmp = Y1;
                        Y1         = Y2;
                        Y2         = tmp;
                }

                if (Y1 < y && y <= Y2) {
                        double x1 = m_xyCoords[i].first;
                        double x2 = m_xyCoords[i + 1].first;

                        if (x <= std::max(x1, x2)) {
                                if (x1 == x2)
                                        intersections++;
                                else {
                                        double x0 = ((y - y1) * (x2 - x1)) / (y2 - y1) + x1;

                                        if (x <= x0)
                                                intersections++;
                                }
                        }
                }
        }
        return (intersections & 1) ? true : false;
}

