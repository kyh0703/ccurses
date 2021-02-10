#pragma once
#include <ncurses.h>
#include <string>
#include "Attribute.h"
using namespace std;

enum MB_RESULT
{
    MB_RESULT_OK,
    MB_RESULT_YES,
    MB_RESULT_NO,
};

enum MB_TYPE
{
    MB_OK,
    MB_YESNO,
};

int MessageBox(string title, string text, int type);