#pragma once
#include "ExitStatus.h"
#include "gridvalues.h"
#include <assert.h>
#include <vector>

class TIFFDensityFile : public GridValues
{
public:
        ///
        TIFFDensityFile();

        ///
        virtual ~TIFFDensityFile() override = default;

        // Note: everything will be converted to doubles!
        ExitStatus init(const std::string& fileName, bool noNegativeValues = true, bool flipY = false);

        ///
        int getWidth() const override { return m_width; }

        ///
        int getHeight() const override { return m_height; }

        ///
        double getValue(int x, int y) const override;

        ///
        void setValue(int x, int y, double v) override;

        ///
        bool isYFlipped() const override { return m_yFlipped; }

private:
        ExitStatus readTiffFile(const std::string& fileName, bool noNeg, bool flipY);

        template <class T>
        ExitStatus readTilesFromTIFF(void* pTiffVoid, int tileWidth, int tileHeight, int width, int height, bool noNeg,
                                     const std::string& fileName);

        template <class T>
        class Tile
        {
        public:
                Tile() = default;
                Tile(size_t s) { m_buffer.resize(s); }
                Tile(const Tile& src) { m_buffer = src.m_buffer; }
                T* getData()
                {
                        assert(m_buffer.size() > 0);
                        return &(m_buffer[0]);
                }

        private:
                std::vector<T> m_buffer;
        };

private:
        int                 m_height;
        int                 m_width;
        std::vector<double> m_values;
        bool                m_yFlipped;
};

inline double TIFFDensityFile::getValue(int x, int y) const
{
        assert(x >= 0 && x < m_width);
        assert(y >= 0 && y < m_height);
        int idx = x + y * m_width;
        assert(idx >= 0 && idx < (int)m_values.size());
        return m_values[idx];
}

inline void TIFFDensityFile::setValue(int x, int y, double v)
{
        assert(x >= 0 && x < m_width);
        assert(y >= 0 && y < m_height);
        int idx = x + y * m_width;
        assert(idx >= 0 && idx < (int)m_values.size());
        m_values[idx] = v;
}
