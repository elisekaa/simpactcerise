#include "configwriter.h"
#include "util.h"

#include <cstdio>

#define __STDC_FORMAT_MACROS // Need this for PRId64
#include <cinttypes>

using namespace std;

ExitStatus ConfigWriter::addKey(const std::string& key, double value) { return addKey(key, doubleToString(value)); }

ExitStatus ConfigWriter::addKey(const std::string& key, int value) { return addKey(key, strprintf("%d", value)); }

ExitStatus ConfigWriter::addKey(const std::string& key, int64_t value)
{
        return addKey(key, strprintf("%" PRId64, value));
}

ExitStatus ConfigWriter::addKey(const std::string& key, bool value)
{
        if (value)
                return addKey(key, "yes");
        return addKey(key, "no");
}

ExitStatus ConfigWriter::addKey(const std::string& key, const char* pStr) { return addKey(key, string(pStr)); }

ExitStatus ConfigWriter::addKey(const std::string& key, const std::string& value)
{
        map<string, string>::const_iterator it = m_keyValues.find(key);

        if (it != m_keyValues.end())
                return ExitStatus("ConfigWriter::addKey: Key '" + key + "' already exists");

        m_keyValues[key] = value;
        return ExitStatus(true);
}

void ConfigWriter::getKeys(std::vector<std::string>& keys) const
{
        auto it = m_keyValues.cbegin();
        keys.clear();
        while (it != m_keyValues.cend()) {
                keys.push_back(it->first);
                it++;
        }
}

ExitStatus ConfigWriter::getKeyValue(const std::string& key, std::string& value) const
{
        map<string, string>::const_iterator it;
        it = m_keyValues.find(key);
        if (it == m_keyValues.end())
                return ExitStatus("Key '" + key + "' not found");
        value = it->second;

        return ExitStatus(true);
}

ExitStatus ConfigWriter::addKey(const std::string& key, const std::vector<double>& values)
{
        string str;
        if (!values.empty()) {
                str = doubleToString(values[0]);
                for (size_t i = 1; i < values.size(); i++)
                        str += "," + doubleToString(values[i]);
        }
        return addKey(key, str);
}
