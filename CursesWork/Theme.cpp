#include "Theme.h"

Theme &Theme::Get()
{
    // c++ 11 thread Safe
    static Theme instance;
    return instance;
}

Theme::Theme()
{
    _base.color.bg = COLOR_BLACK;
    _base.color.fg = COLOR_WHITE;
    _base.tilte = COLOR_WHITE;

    _basic.textColor = COLOR_WHITE;

    _btn.active.bg = COLOR_WHITE;
    _btn.active.fg = COLOR_BLACK;
    _btn.active.opt = A_BLINK;
    _btn.inactive.bg = COLOR_BLACK;
    _btn.inactive.fg = COLOR_WHITE;
    _btn.inactive.opt = A_NORMAL;

    _input.active.bg = COLOR_BLACK;
    _input.active.fg = COLOR_WHITE;
    _input.active.opt = A_UNDERLINE | A_BLINK;
    _input.inactive.bg = COLOR_BLACK;
    _input.inactive.fg = COLOR_WHITE;
    _input.inactive.opt = A_UNDERLINE;

    _tab.active.bg = COLOR_WHITE;
    _tab.active.fg = COLOR_BLACK;
    _tab.active.opt = A_BLINK;
    _tab.inactive.bg = COLOR_BLACK;
    _tab.inactive.fg = COLOR_WHITE;
    _tab.inactive.opt = A_NORMAL;

    _list.active.bg = COLOR_WHITE;
    _list.active.fg = COLOR_BLACK;
    _list.active.opt = A_BLINK;
    _list.inactive.bg = COLOR_BLACK;
    _list.inactive.fg = COLOR_WHITE;
    _list.inactive.opt = A_NORMAL;

    _progress.bar = COLOR_WHITE;
    _progress.label.bg = COLOR_BLACK;
    _progress.label.fg = COLOR_WHITE;
    _progress.label.opt = A_NORMAL;

    _bar.bar = COLOR_WHITE;
    _bar.label.bg = COLOR_BLACK;
    _bar.label.bg = COLOR_WHITE;
}