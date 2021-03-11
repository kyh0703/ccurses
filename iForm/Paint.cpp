#include "Paint.h"

Paint &Paint::Get()
{
    // c++ 11 thread Safe
    static Paint instance;
    return instance;
}

short Paint::GetIndex(short bg, short fg)
{
    short idx = FindColorSet(bg, fg);
    if (idx <= 0)
    {
        idx = AddColorSet(bg, fg);
        if (idx <= 0)
            return 0;
    }

    return idx;
}

Paint::Paint()
{
    _color_count = 0;
    memset(_color_table, 0x00, sizeof(_color_table));
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

short Paint::AddColorSet(short bg, short fg)
{
    short ret = FindColorSet(bg, fg);
    if (ret > 0)
        return ret;

    if (_color_count >= 64)
        return -1;

    _color_table[_color_count].no = _color_count + 1;
    _color_table[_color_count].bg = bg;
    _color_table[_color_count].fg = fg;

    if (_color_count <= 0)
        start_color();

    init_pair(_color_table[_color_count].no,
              _color_table[_color_count].fg,
              _color_table[_color_count].bg);

    ret = _color_table[_color_count].no;
    _color_count++;
    return ret;
}

short Paint::FindColorSet(short bg, short fg)
{
    for (int idx = 0; idx < _color_count; idx++)
    {
        if (_color_table[idx].bg == bg &&
            _color_table[idx].fg == fg)
            return _color_table[idx].no;
    }

    return -1;
}
