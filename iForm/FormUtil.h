#pragma once
#include "Attribute.h"
#include <string>

namespace fu
{
    inline const std::wstring ToWstring(std::string str)
    {
        std::wstring temp;
        temp.assign(str.begin(), str.end());
        return temp;
    }

    inline const std::string ToString(std::wstring wstr)
    {
        std::string temp;
        temp.assign(wstr.begin(), wstr.end());
        return temp;
    }

    inline const std::string LTrim(std::string str)
    {
        return str.erase(0, str.find_first_not_of(" \t\n\v"));
    }

    inline const std::string RTrim(std::string str)
    {
        return str.erase(str.find_last_not_of(" \t\n\v") + 1);
    }

    inline const std::string Trim(std::string str)
    {
        return RTrim(LTrim(str));
    }

    inline const std::wstring LTrim(std::wstring wstr)
    {
        return wstr.erase(0, wstr.find_first_not_of(L" \t\n\v"));
    }

    inline const std::wstring RTrim(std::wstring wstr)
    {
        return wstr.erase(wstr.find_last_not_of(L" \t\n\v") + 1);
    }

    inline const std::wstring Trim(std::wstring wstr)
    {
        return RTrim(LTrim(wstr));
    }

    inline const bool IsHangle(wchar_t wch)
    {
        bool is_hangle = false;
        const wchar_t start_hangle = L'가';
        const wchar_t end_hangle = L'힣';
        const wchar_t start_jamo = L'ㄱ';
        const wchar_t end_jamo = L'ㆎ';
        is_hangle |= (start_hangle <= wch && wch <= end_hangle);
        is_hangle |= (start_jamo <= wch && wch <= end_jamo);
        return is_hangle;
    }

    inline const int GetTextSize(std::wstring wstr)
    {
        int size = 0;
        for (size_t index = 0; index < wstr.size(); ++index)
        {
            wchar_t wch = wstr[index];
            size += (IsHangle(wch) ? 2 : 1);
        }
        return size;
    }
};