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
    _textbox.style.fg = COLOR_BLACK;

    _button.active.bg = COLOR_WHITE;
    _button.active.fg = COLOR_BLACK;
    _button.inactive.bg = COLOR_BLACK;
    _button.inactive.fg = COLOR_WHITE;

    _popup.text_color = COLOR_WHITE;
    _popup.button.bg = COLOR_WHITE;
    _popup.button.fg = COLOR_BLACK;

    _yesno.text_color = COLOR_WHITE;
    _yesno.active.bg = COLOR_WHITE;
    _yesno.active.fg = COLOR_BLACK;
    _yesno.inactive.bg = COLOR_BLACK;
    _yesno.inactive.fg = COLOR_WHITE;

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
    _bar.number = COLOR_BLACK;
    _bar.label.bg = COLOR_BLACK;
    _bar.label.bg = COLOR_WHITE;

    _checkbox.active.bg = COLOR_WHITE;
    _checkbox.active.fg = COLOR_BLUE;
    _checkbox.active.opt = A_REVERSE;
    _checkbox.inactive.bg = COLOR_WHITE;
    _checkbox.inactive.bg = COLOR_WHITE;

    _radio.active.bg = COLOR_WHITE;
    _radio.active.fg = COLOR_BLUE;
    _radio.active.opt = A_REVERSE;
    _radio.inactive.bg = COLOR_WHITE;
    _radio.inactive.bg = COLOR_WHITE;
}