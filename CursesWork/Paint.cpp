#include "Paint.h"

Paint &Paint::Get()
{
    // c++ 11 thread Safe
    static Paint instance;
    return instance;
}

Paint::Paint()
{
    _colorCnt = 0;
    memset(_colorTable, 0x00, sizeof(_colorTable));
}

short Paint::FindIndex(short fg, short bg)
{
    short idx = FindColorSet(fg, bg);
    if (idx <= 0)
    {
        idx = AddColorSet(fg, bg);
        if (idx <= 0)
            return 0;
    }

    return idx;
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

short Paint::AddColorSet(short fg, short bg)
{
    short ret = FindColorSet(fg, bg);
    if (ret > 0)
        return ret;

    if (_colorCnt >= 64)
        return -1;

    _colorTable[_colorCnt].no = _colorCnt + 1;
    _colorTable[_colorCnt].fg = fg;
    _colorTable[_colorCnt].bg = bg;

    if (_colorCnt <= 0)
    {
        start_color();
        init_color(COLOR_RED, 500, 0, 0);
        init_color(COLOR_GREEN, 500, 0, 0);
        init_color(COLOR_YELLOW, 500, 0, 0);
        init_color(COLOR_BLUE, 500, 0, 0);
        init_color(COLOR_MAGENTA, 500, 0, 0);
        init_color(COLOR_CYAN, 500, 0, 0);
    }

    init_pair(_colorTable[_colorCnt].no,
              _colorTable[_colorCnt].fg,
              _colorTable[_colorCnt].bg);

    ret = _colorTable[_colorCnt].no;
    _colorCnt++;
    return ret;
}

short Paint::FindColorSet(short fg, short bg)
{
    for (int colorIdx = 0; colorIdx < _colorCnt; colorIdx++)
    {
        if (_colorTable[colorIdx].fg == fg &&
            _colorTable[colorIdx].bg == bg)
            return _colorTable[colorIdx].no;
    }

    return -1;
}
