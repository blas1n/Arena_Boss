#include "FileSystem.h"
#include <filesystem>
#include <fstream>
#include <iterator>

#if _UNICODE    
using tifstream = std::wifstream;
#else
using tifstream = std::ifstream;
#endif

namespace fs = std::filesystem;

namespace FileSystem
{
    tstring ReadFile(const tstring& path)
    {
        tifstream in{ path };
        if (!in)
            throw "Cannot open file.";

        return tstring{ std::istreambuf_iterator<TCHAR>{ in },
            std::istreambuf_iterator<TCHAR>{} };
    }

    std::vector<char> ReadBinary(const tstring& path)
    {
        std::ifstream in{ path, std::ios::binary };
        if (!in)
            throw "Cannot open file.";

        auto buf = in.rdbuf();
        auto fileSize = buf->pubseekoff(0, std::ios::end, std::ios::in);
        buf->pubseekpos(0, std::ios::in);

        std::vector<char> ret(static_cast<size_t>(fileSize));
        buf->sgetn(ret.data(), fileSize);
        return ret;
    }

    tstring GetCurrentPath()
    {
    #if _UNICODE
        return fs::current_path().wstring();
    #else
        return fs::current_path().string();
    #endif
    }

    tstring GetFileName(const tstring& path)
    {
    #if _UNICODE
        return fs::path{ path }.filename().wstring();
    #else
        return fs::path{ path }.filename().string();
    #endif
    }

    std::vector<tstring> GetFileNames(const tstring& dir)
    {
        std::vector<tstring> ret;

        for (auto&& entry : fs::directory_iterator{ dir })
        {
            auto& path = entry.path();
            if (fs::is_regular_file(path))
            {
            #if _UNICODE
                ret.push_back(path.wstring());
            #else
                ret.push_back(path.string());
            #endif
            }
        }

        return ret;
    }

    std::vector<tstring> GetFileNames(const tstring& dir, const tstring& ext)
    {
        std::vector<tstring> ret;

        for (auto&& entry : fs::directory_iterator{ dir })
        {
            auto& path = entry.path();

        #if _UNICODE
            auto pathExt = path.extension().wstring();
        #else
            auto pathExt = path.extension().string();
        #endif

            if (fs::is_regular_file(path) && pathExt == ext)
            {
#if _UNICODE
                ret.push_back(path.wstring());
#else
                ret.push_back(path.string());
#endif
            }
        }

        return ret;
    }
}

bool ReadFileBinary(const std::wstring& filename, std::vector<char>& buf)
{
    buf.clear();

    std::ifstream fin(filename, std::ios::binary);
    if (!fin)
        return false;

    std::filebuf* fb = fin.rdbuf();
    std::streampos fileSize = fb->pubseekoff(0, std::ios::end, std::ios::in);
    fb->pubseekpos(0, std::ios::in);

    buf.resize(static_cast<size_t>(fileSize));
    fb->sgetn(buf.data(), fileSize);

    return true;
}