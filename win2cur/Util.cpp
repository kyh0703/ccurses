#include "Util.h"

bool Util::IsHangle(const wchar_t wch)
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

int Util::GetTextSize(wstring wstr)
{
    int size = 0;
    for (size_t index = 0; index < wstr.size(); ++index)
    {
        wchar_t wch = wstr[index];
        size += (IsHangle(wch) ? 2 : 1);
    }
    return size;
}