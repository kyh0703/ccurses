#include "Theme.h"

Theme &Theme::Get()
{
    // c++ 11 thread Safe
    static Theme instance;
    return instance;
}

Theme::Theme()
{
    _default.bg = COLOR_BLACK;
    _default.fg = COLOR_WHITE;

    _basic = COLOR_WHITE;

    _btn._active.bg = COLOR_WHITE;
    _btn._active.fg = COLOR_BLACK;
    _btn._active.opt = A_BLINK;
    _btn._inactive.bg = COLOR_BLACK;
    _btn._inactive.fg = COLOR_WHITE;
    _btn._inactive.opt = A_NORMAL;

    _tab._active.bg = COLOR_WHITE;
    _tab._active.fg = COLOR_BLUE;
    _tab._active.opt = A_BLINK;
    _tab._inactive.bg = COLOR_BLACK;
    _tab._inactive.fg = COLOR_WHITE;
    _tab._inactive.opt = A_NORMAL;

    _list._active.bg = COLOR_WHITE;
    _list._active.fg = COLOR_BLUE;
    _list._active.opt = A_BLINK;
    _list._inactive.bg = COLOR_BLACK;
    _list._inactive.fg = COLOR_WHITE;
    _list._inactive.opt = A_NORMAL;
}