#pragma once

#include "ExitStatus.h"

#include <map>
#include <cstdint>
#include <vector>

class ConfigWriter
{
public:
        ///
        ConfigWriter() = default;

        ///
        virtual ~ConfigWriter() = default;

        ExitStatus addKey(const std::string& key, double value);
        ExitStatus addKey(const std::string& key, const std::vector<double>& values);
        ExitStatus addKey(const std::string& key, int value);
        ExitStatus addKey(const std::string& key, int64_t value);
        ExitStatus addKey(const std::string& key, bool value);
        ExitStatus addKey(const std::string& key, const char* pStr);
        ExitStatus addKey(const std::string& key, const std::string& value);

        void   getKeys(std::vector<std::string>& keys) const;
        ExitStatus getKeyValue(const std::string& key, std::string& value) const;

private:
        std::map<std::string, std::string> m_keyValues;
};

