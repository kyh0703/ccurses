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

    _textbox.style.bg = COLOR_BLACK;
    _textbox.style.fg = COLOR_WHITE;

    _button.active.bg = COLOR_WHITE;
    _button.active.fg = COLOR_BLACK;
    _button.inactive.bg = COLOR_BLACK;
    _button.inactive.fg = COLOR_WHITE;

    _input.active.bg = COLOR_BLACK;
    _input.active.fg = COLOR_WHITE;
    _input.active.opt = WA_UNDERLINE;
    _input.inactive.bg = COLOR_BLACK;
    _input.inactive.fg = COLOR_WHITE;
    _input.inactive.opt = WA_UNDERLINE;

    _tab.active.bg = COLOR_BLACK;
    _tab.active.fg = COLOR_WHITE;
    _tab.active.opt = WA_STANDOUT;
    _tab.inactive.bg = COLOR_BLACK;
    _tab.inactive.fg = COLOR_WHITE;
    _tab.inactive.opt = WA_NORMAL;

    _list.active.bg = COLOR_WHITE;
    _list.active.fg = COLOR_BLACK;
    _list.active.opt = WA_STANDOUT;
    _list.inactive.bg = COLOR_BLACK;
    _list.inactive.fg = COLOR_WHITE;
    _list.inactive.opt = WA_NORMAL;

    _progress.bar = COLOR_WHITE;
    _progress.label.bg = COLOR_BLACK;
    _progress.label.fg = COLOR_WHITE;
    _progress.label.opt = WA_NORMAL;

    _bar.bar = COLOR_WHITE;
    _bar.number = COLOR_BLACK;
    _bar.label.bg = COLOR_BLACK;
    _bar.label.bg = COLOR_WHITE;

    _checkbox.style.bg = COLOR_WHITE;
    _checkbox.style.fg = COLOR_BLACK;
    _checkbox.style.opt = WA_REVERSE;

    _radio.active.bg = COLOR_WHITE;
    _radio.active.fg = COLOR_BLUE;
    _radio.active.opt = WA_REVERSE;
    _radio.inactive.bg = COLOR_WHITE;
    _radio.inactive.bg = COLOR_WHITE;
}