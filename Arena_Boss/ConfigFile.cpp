#include "ConfigFile.h"
#include <algorithm>
#include <cassert>
#include <fstream>

namespace ArenaBoss
{
    const tstring* ConfigSection::operator[](const tstring& key) const
    {
        const auto it = data.find(key);
        if (it != data.cend())
            return &(it->second);
        return nullptr;
    }

    namespace
    {
        tstring TrimInline(const tstring& s)
        {
            auto begin = s.find_first_not_of(TEXT(" \t"));
            auto end = s.find_last_not_of(TEXT(" \t"));
            if (begin == tstring::npos || end == tstring::npos || begin > end)
                return TEXT("");
            return s.substr(begin, end - begin + 1);
        }
    }

    bool ConfigFile::LoadFromFile(const tstring& fileName)
    {
        assert(state == State::Uninitialized);

        try
        {
            tifstream fin{ fileName };
            if (!fin) throw;

            tstring section = TEXT("Global");
            std::map<tstring, tstring> sectionMap;
            tstring line;

            while (std::getline(fin, line))
            {
                if ((line = TrimInline(line)).empty() || line[0] == '#')
                    continue;

                if (line[0] == TEXT('['))
                {
                    const auto end = line.rfind(']');
                    if (end == tstring::npos || end == 1)
                        throw;

                    map.emplace(std::make_pair(section, ConfigSection{ sectionMap }));
                    section = TrimInline(line.substr(1, end - 1));
                }
                else
                {
                    const auto eq = line.find('=');
                    if (eq == tstring::npos || eq == 0 || eq == line.length() - 1)
                        throw;

                    const auto left = TrimInline(line.substr(0, eq));
                    const auto right = TrimInline(line.substr(eq + 1));

                    if (left.empty() || right.empty())
                        throw;

                    sectionMap.emplace(std::make_pair(left, right));
                }
            }

            state = State::Available;
            return true;
        }
        catch (...)
        {
            map.clear();
            state = State::Error;
            return false;
        }
    }

    void ConfigFile::Clear()
    {
        map.clear();
        state = State::Uninitialized;
    }

    const tstring* ConfigFile::operator()(const tstring& sectionName, const tstring& keyName) const
    {
        const auto section = GetSection(sectionName);
        if (!section) return nullptr;
        return (*section)[keyName];
    }

    const ConfigSection* ConfigFile::GetSection(const tstring& section) const
    {
        const auto it = map.find(section);
        if (it != map.cend())
            return &(it->second);
        return nullptr;
    }
}