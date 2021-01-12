#include "Paint.h"

Paint &Paint::Get()
{
    // c++ 11 thread Safe
    static Paint instance;
    return instance;
}

Paint::Paint()
{
    mColorCnt = 0;
    memset(mColorTable, 0x00, sizeof(mColorTable));
}

bool Paint::IsColorSet(short color)
{
    switch (color)
    {
    case COLOR_BLACK:
    case COLOR_RED:
    case COLOR_GREEN:
    case COLOR_YELLOW:
    case COLOR_BLUE:
    case COLOR_MAGENTA:
    case COLOR_CYAN:
    case COLOR_WHITE:
        return true;
    default:
        return false;
    }
}

short Paint::FindIndex(short fg, short bg)
{
    short nIndex = FindColorSet(fg, bg);
    if (nIndex <= 0)
    {
        nIndex = AppendColorSet(fg, bg);
        if (nIndex <= 0)
            return 0;
    }

    return nIndex;
}

short Paint::AppendColorSet(short fg, short bg)
{
    short nResult = FindColorSet(fg, bg);
    if (nResult > 0)
        return nResult;

    if (mColorCnt >= 64)
        return -1;

    mColorTable[mColorCnt].no = mColorCnt + 1;
    mColorTable[mColorCnt].fg = fg;
    mColorTable[mColorCnt].bg = bg;

    if (mColorCnt <= 0)
    {
        start_color();
        init_color(COLOR_RED, 500, 0, 0);
        init_color(COLOR_GREEN, 500, 0, 0);
        init_color(COLOR_YELLOW, 500, 0, 0);
        init_color(COLOR_BLUE, 500, 0, 0);
        init_color(COLOR_MAGENTA, 500, 0, 0);
        init_color(COLOR_CYAN, 500, 0, 0);
    }

    init_pair(mColorTable[mColorCnt].no,
              mColorTable[mColorCnt].fg,
              mColorTable[mColorCnt].bg);

    nResult = mColorTable[mColorCnt].no;
    mColorCnt++;
    return nResult;
}

short Paint::FindColorSet(short fg, short bg)
{
    for (int nColor = 0; nColor < mColorCnt; nColor++)
    {
        if (mColorTable[nColor].fg == fg &&
            mColorTable[nColor].bg == bg)
            return mColorTable[nColor].no;
    }

    return -1;
}
