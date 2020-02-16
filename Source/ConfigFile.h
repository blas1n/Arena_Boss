#pragma once

#include <map>
#include <string>

namespace ArenaBoss
{
    class ConfigSection
    {
    public:
        ConfigSection(const ConfigSection&) = default;
        ConfigSection(ConfigSection&&) noexcept = default;

        ConfigSection& operator=(const ConfigSection&) = default;
        ConfigSection& operator=(ConfigSection&&) noexcept = default;

        const std::string* operator[](const std::string& key) const;

        const std::map<std::string, std::string>& GetData() const { return data; }

    private:
        friend class ConfigFile;

        ConfigSection(const std::map<std::string, std::string>& inData)
            : data(inData) {}

        std::map<std::string, std::string> data;
    };

    class ConfigFile
    {
    public:
        ConfigFile() = default;
        ConfigFile(const std::string& fileName)
            : ConfigFile() { LoadFromFile(fileName); }

        ConfigFile(const ConfigFile&) = default;
        ConfigFile(ConfigFile&&) = default;
        
        ~ConfigFile() = default;

        ConfigFile& operator=(const ConfigFile&) = default;
        ConfigFile& operator=(ConfigFile&&) noexcept = default;

        void LoadFromFile(const std::string& fileName);
        void Clear();

        inline bool IsAvailable() const { return state == State::Available; }

        inline operator bool() const { return IsAvailable(); }

        inline bool IsExistSection(const std::string& section) const
        {
            return map.find(section) != map.cend();
        }

        const std::string* operator()(const std::string& sectionName, const std::string& keyName) const;
        const ConfigSection* GetSection(const std::string& section) const;

    private:
        enum class State
        {
            Uninitialized,
            Available,
            Error
        } state = State::Uninitialized;

        std::map<std::string, ConfigSection> map;
    };
}