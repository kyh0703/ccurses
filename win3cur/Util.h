#pragma once
#include <string>
#include "Attribute.h"
using namespace std;

class Util
{
public:
    static bool IsHangle(wchar_t wch);
    static int GetTextSize(wstring wstr);
};