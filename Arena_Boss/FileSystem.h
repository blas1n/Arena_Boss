#pragma once

#include "Common.h"
#include <map>
#include <vector>

namespace FileSystem
{
    tstring ReadFile(const tstring& path);
    std::vector<char> ReadBinary(const tstring& path);

    tstring GetCurrentPath();

    tstring GetFileName(const tstring& path);
    std::vector<tstring> GetFileNames(const tstring& dir);
    std::vector<tstring> GetFileNames(const tstring& dir, const tstring& ext);
}