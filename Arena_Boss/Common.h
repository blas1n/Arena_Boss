#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#include <string>

#ifdef _UNICODE
using tstring = std::wstring;
#else
using tstring = std::string;
#endif

using byte = unsigned char;