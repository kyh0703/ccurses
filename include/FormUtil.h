#pragma once
#include "Attribute.h"
#include <string>
#include <vector>

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

    inline std::string &LTrim(std::string &str)
    {
        return str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    }

    inline std::string &RTrim(std::string &str)
    {
        return str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
    }

    inline std::string &Trim(std::string str)
    {
        return RTrim(LTrim(str));
    }

    inline std::wstring &LTrim(std::wstring &wstr)
    {
        wstr.erase(0, wstr.find_first_not_of(L" \t\n\r\f\v"));
        return wstr;
    }

    inline std::wstring &RTrim(std::wstring &wstr)
    {
        wstr.erase(wstr.find_last_not_of(L" \t\n\r\f\v") + 1);
        return wstr;
    }

    inline std::wstring &Trim(std::wstring wstr)
    {
        return LTrim(RTrim(wstr));
    }

    inline std::vector<std::wstring> ToWVector(std::vector<std::string> strs)
    {
        std::vector<std::wstring> wstrs;
        for (auto it : strs)
            wstrs.push_back(ToWstring(it));
        return wstrs;
    }

    inline std::vector<std::string> ToVector(std::vector<std::wstring> wstrs)
    {
        std::vector<std::string> strs;
        for (auto it : wstrs)
            strs.push_back(ToString(it));
        return strs;
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