#include "Util.h"

bool Util::IsHangle(const wchar_t wch)
{
    const wchar_t start_ch = L'가';
    const wchar_t end_ch = L'힣';
    return (start_ch <= wch && wch <= end_ch);
}