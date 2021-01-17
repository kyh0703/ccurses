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

    _btn.active.bg = COLOR_WHITE;
    _btn.active.fg = COLOR_BLACK;
    _btn.active.opt = A_BLINK;
    _btn.inactive.bg = COLOR_BLACK;
    _btn.inactive.fg = COLOR_WHITE;
    _btn.inactive.opt = A_NORMAL;

    _tab.active.bg = COLOR_WHITE;
    _tab.active.fg = COLOR_BLUE;
    _tab.active.opt = A_BLINK;
    _tab.inactive.bg = COLOR_BLACK;
    _tab.inactive.fg = COLOR_WHITE;
    _tab.inactive.opt = A_NORMAL;

    _list.active.bg = COLOR_WHITE;
    _list.active.fg = COLOR_BLUE;
    _list.active.opt = A_BLINK;
    _list.inactive.bg = COLOR_BLACK;
    _list.inactive.fg = COLOR_WHITE;
    _list.inactive.opt = A_NORMAL;

    _progress.bar = COLOR_RED;
    _progress.label.bg = COLOR_BLACK;
    _progress.label.fg = COLOR_RED;
}