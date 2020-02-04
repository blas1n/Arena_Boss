#pragma once

#include "Common.h"
#include <map>

namespace ArenaBoss
{
    namespace
    {
#       if _UNICODE    
        using tifstream = std::wifstream;
#       else
        using tifstream = std::ifstream;
#       endif
    }

    class ConfigSection
    {
    public:
        ConfigSection(const ConfigSection&) = default;
        ConfigSection(ConfigSection&&) noexcept = default;

        ConfigSection& operator=(const ConfigSection&) = default;
        ConfigSection& operator=(ConfigSection&&) noexcept = default;

        const tstring* operator[](const tstring& key) const;

        const std::map<tstring, tstring>& GetData() const { return data; }

    private:
        friend class ConfigFile;

        ConfigSection(const std::map<tstring, tstring>& inData)
            : data(inData) {}

        std::map<tstring, tstring> data;
    };

    class ConfigFile
    {
    public:
        ConfigFile() = default;
        ConfigFile(const tstring& fileName)
            : ConfigFile() { LoadFromFile(fileName); }

        ConfigFile(const ConfigFile&) = default;
        ConfigFile(ConfigFile&&) = default;
        
        ~ConfigFile() = default;

        ConfigFile& operator=(const ConfigFile&) = default;
        ConfigFile& operator=(ConfigFile&&) noexcept = default;

        bool LoadFromFile(const tstring& filename);
        void Clear();

        inline bool IsAvailable() const { return state == State::Available; }

        inline operator bool() const { return IsAvailable(); }

        inline bool IsExistSection(const tstring& section) const
        {
            return map.find(section) != map.cend();
        }

        const tstring* operator()(const tstring& sectionName, const tstring& keyName) const;
        const ConfigSection* GetSection(const tstring& section) const;

    private:
        enum class State
        {
            Uninitialized,
            Available,
            Error
        } state = State::Uninitialized;

        std::map<tstring, ConfigSection> map;
    };
}