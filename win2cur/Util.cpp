#include "Util.h"

bool Util::IsHangle(const wchar_t wch)
{
    const wchar_t start_ch = L'가';
    const wchar_t end_ch = L'힣';
    return (start_ch <= wch && wch <= end_ch);
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