#pragma once
#include "Attribute.h"
#include "FormUtil.h"
#include <ncursesw/curses.h>
#include <string>
#include <vector>
using namespace std;

enum MB_RESULT
{
    MB_RESULT_CANCLE,
    MB_RESULT_OK,
    MB_RESULT_YES,
    MB_RESULT_NO,
};

enum MB_TYPE
{
    MB_TYPE_OK,
    MB_TYPE_YESNO,
};

const int MessageBox(wstring title, wstring text, int type);