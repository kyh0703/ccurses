#include "Theme.h"

Theme &Theme::Get()
{
    // c++ 11 thread Safe
    static Theme instance;
    return instance;
}

Theme::Theme()
{
    DarkWhite();
}

void Theme::SetTheme(unsigned theme)
{
    if (theme == DARK_WHITE)
        DarkWhite();
    else if (theme == WHITE_DARK)
        WhiteDark();
    else if (theme == GITHUB_LIGHT)
        GitHubLight();
    else if (theme == GITHUB_DARK)
        GitHubDark();
    else if (theme ==  WINTER_IS_COMMING)
        WinterIsComming();
    else if (theme == VSCODE_DARK)
        VSCodeDark();
}

void Theme::DarkWhite()
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

    _list.active.bg = COLOR_BLACK;
    _list.active.fg = COLOR_WHITE;
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

    _radio.style.bg = COLOR_WHITE;
    _radio.style.fg = COLOR_BLACK;
    _radio.style.opt = WA_REVERSE;
}

void Theme::WhiteDark()
{
    _base.color.bg = COLOR_WHITE;
    _base.color.fg = COLOR_BLACK;
    _base.tilte = COLOR_BLACK;

    _textbox.style.bg = COLOR_WHITE;
    _textbox.style.fg = COLOR_BLACK;

    _button.active.bg = COLOR_BLACK;
    _button.active.fg = COLOR_WHITE;
    _button.inactive.bg = COLOR_WHITE;
    _button.inactive.fg = COLOR_BLACK;

    _input.active.bg = COLOR_WHITE;
    _input.active.fg = COLOR_BLACK;
    _input.active.opt = WA_UNDERLINE;
    _input.inactive.bg = COLOR_WHITE;
    _input.inactive.fg = COLOR_BLACK;
    _input.inactive.opt = WA_UNDERLINE;

    _tab.active.bg = COLOR_WHITE;
    _tab.active.fg = COLOR_BLACK;
    _tab.active.opt = WA_STANDOUT;
    _tab.inactive.bg = COLOR_WHITE;
    _tab.inactive.fg = COLOR_BLACK;
    _tab.inactive.opt = WA_NORMAL;

    _list.active.bg = COLOR_WHITE;
    _list.active.fg = COLOR_BLACK;
    _list.active.opt = WA_STANDOUT;
    _list.inactive.bg = COLOR_WHITE;
    _list.inactive.fg = COLOR_BLACK;
    _list.inactive.opt = WA_NORMAL;

    _progress.bar = COLOR_BLACK;
    _progress.label.bg = COLOR_WHITE;
    _progress.label.fg = COLOR_BLACK;
    _progress.label.opt = WA_NORMAL;

    _bar.bar = COLOR_BLACK;
    _bar.number = COLOR_WHITE;
    _bar.label.bg = COLOR_WHITE;
    _bar.label.bg = COLOR_BLACK;

    _checkbox.style.bg = COLOR_BLACK;
    _checkbox.style.fg = COLOR_WHITE;
    _checkbox.style.opt = WA_REVERSE;

    _radio.style.bg = COLOR_BLACK;
    _radio.style.fg = COLOR_WHITE;
    _radio.style.opt = WA_REVERSE;
}

void Theme::GitHubLight()
{
    _base.color.bg = COLOR_WHITE;
    _base.color.fg = COLOR_MAGENTA;
    _base.tilte = COLOR_RED;

    _textbox.style.bg = COLOR_WHITE;
    _textbox.style.fg = COLOR_BLACK;

    _button.active.bg = COLOR_WHITE;
    _button.active.fg = COLOR_CYAN;
    _button.inactive.bg = COLOR_WHITE;
    _button.inactive.fg = COLOR_BLACK;

    _input.active.bg = COLOR_WHITE;
    _input.active.fg = COLOR_BLACK;
    _input.active.opt = WA_UNDERLINE;
    _input.inactive.bg = COLOR_WHITE;
    _input.inactive.fg = COLOR_BLACK;
    _input.inactive.opt = WA_UNDERLINE;

    _tab.active.bg = COLOR_WHITE;
    _tab.active.fg = COLOR_BLUE;
    _tab.active.opt = WA_STANDOUT;
    _tab.inactive.bg = COLOR_WHITE;
    _tab.inactive.fg = COLOR_BLACK;
    _tab.inactive.opt = WA_NORMAL;

    _list.active.bg = COLOR_WHITE;
    _list.active.fg = COLOR_CYAN;
    _list.active.opt = WA_STANDOUT;
    _list.inactive.bg = COLOR_WHITE;
    _list.inactive.fg = COLOR_BLACK;
    _list.inactive.opt = WA_NORMAL;

    _progress.bar = COLOR_RED;
    _progress.label.bg = COLOR_BLUE;
    _progress.label.fg = COLOR_WHITE;
    _progress.label.opt = WA_REVERSE;

    _bar.bar = COLOR_BLUE;
    _bar.number = COLOR_WHITE;
    _bar.label.bg = COLOR_WHITE;
    _bar.label.fg = COLOR_RED;

    _checkbox.style.bg = COLOR_WHITE;
    _checkbox.style.fg = COLOR_MAGENTA;
    _checkbox.style.opt = WA_NORMAL;

    _radio.style.bg = COLOR_WHITE;
    _radio.style.fg = COLOR_MAGENTA;
    _radio.style.opt = WA_NORMAL;
}

void Theme::GitHubDark()
{
    _base.color.bg = COLOR_BLACK;
    _base.color.fg = COLOR_MAGENTA;
    _base.tilte = COLOR_RED;

    _textbox.style.bg = COLOR_BLACK;
    _textbox.style.fg = COLOR_WHITE;

    _button.active.bg = COLOR_BLACK;
    _button.active.fg = COLOR_CYAN;
    _button.inactive.bg = COLOR_BLACK;
    _button.inactive.fg = COLOR_WHITE;

    _input.active.bg = COLOR_BLACK;
    _input.active.fg = COLOR_MAGENTA;
    _input.active.opt = WA_UNDERLINE;
    _input.inactive.bg = COLOR_BLACK;
    _input.inactive.fg = COLOR_MAGENTA;
    _input.inactive.opt = WA_UNDERLINE;

    _tab.active.bg = COLOR_BLACK;
    _tab.active.fg = COLOR_BLUE;
    _tab.active.opt = WA_STANDOUT;
    _tab.inactive.bg = COLOR_BLACK;
    _tab.inactive.fg = COLOR_RED;
    _tab.inactive.opt = WA_NORMAL;

    _list.active.bg = COLOR_BLACK;
    _list.active.fg = COLOR_CYAN;
    _list.active.opt = WA_STANDOUT;
    _list.inactive.bg = COLOR_BLACK;
    _list.inactive.fg = COLOR_WHITE;
    _list.inactive.opt = WA_NORMAL;

    _progress.bar = COLOR_CYAN;
    _progress.label.bg = COLOR_RED;
    _progress.label.fg = COLOR_BLACK;
    _progress.label.opt = WA_REVERSE;

    _bar.bar = COLOR_BLUE;
    _bar.number = COLOR_WHITE;
    _bar.label.bg = COLOR_BLACK;
    _bar.label.fg = COLOR_CYAN;

    _checkbox.style.bg = COLOR_BLACK;
    _checkbox.style.fg = COLOR_WHITE;
    _checkbox.style.opt = WA_NORMAL;

    _radio.style.bg = COLOR_BLACK;
    _radio.style.fg = COLOR_WHITE;
    _radio.style.opt = WA_NORMAL;
}

void Theme::WinterIsComming()
{
    _base.color.bg = COLOR_BLUE;
    _base.color.fg = COLOR_CYAN;
    _base.tilte = COLOR_GREEN;

    _textbox.style.bg = COLOR_BLUE;
    _textbox.style.fg = COLOR_GREEN;

    _button.active.bg = COLOR_BLUE;
    _button.active.fg = COLOR_MAGENTA;
    _button.inactive.bg = COLOR_BLUE;
    _button.inactive.fg = COLOR_CYAN;

    _input.active.bg = COLOR_BLUE;
    _input.active.fg = COLOR_CYAN;
    _input.active.opt = WA_UNDERLINE;
    _input.inactive.bg = COLOR_BLUE;
    _input.inactive.fg = COLOR_CYAN;
    _input.inactive.opt = WA_UNDERLINE;

    _tab.active.bg = COLOR_BLUE;
    _tab.active.fg = COLOR_GREEN;
    _tab.active.opt = WA_STANDOUT;
    _tab.inactive.bg = COLOR_BLUE;
    _tab.inactive.fg = COLOR_CYAN;
    _tab.inactive.opt = WA_NORMAL;

    _list.active.bg = COLOR_BLUE;
    _list.active.fg = COLOR_CYAN;
    _list.active.opt = WA_STANDOUT;
    _list.inactive.bg = COLOR_BLUE;
    _list.inactive.fg = COLOR_WHITE;
    _list.inactive.opt = WA_NORMAL;

    _progress.bar = COLOR_CYAN;
    _progress.label.bg = COLOR_YELLOW;
    _progress.label.fg = COLOR_BLUE;
    _progress.label.opt = WA_REVERSE;

    _bar.bar = COLOR_CYAN;
    _bar.number = COLOR_WHITE;
    _bar.label.bg = COLOR_BLUE;
    _bar.label.fg = COLOR_CYAN;

    _checkbox.style.bg = COLOR_BLUE;
    _checkbox.style.fg = COLOR_WHITE;
    _checkbox.style.opt = WA_NORMAL;

    _radio.style.bg = COLOR_BLUE;
    _radio.style.fg = COLOR_WHITE;
    _radio.style.opt = WA_NORMAL;
}

void Theme::VSCodeDark()
{
    _base.color.bg = COLOR_BLACK;
    _base.color.fg = COLOR_CYAN;
    _base.tilte = COLOR_YELLOW;

    _textbox.style.bg = COLOR_BLACK;
    _textbox.style.fg = COLOR_WHITE;

    _button.active.bg = COLOR_BLACK;
    _button.active.fg = COLOR_YELLOW;
    _button.inactive.bg = COLOR_BLACK;
    _button.inactive.fg = COLOR_WHITE;

    _input.active.bg = COLOR_BLACK;
    _input.active.fg = COLOR_CYAN;
    _input.active.opt = WA_UNDERLINE;
    _input.inactive.bg = COLOR_BLACK;
    _input.inactive.fg = COLOR_CYAN;
    _input.inactive.opt = WA_UNDERLINE;

    _tab.active.bg = COLOR_BLACK;
    _tab.active.fg = COLOR_WHITE;
    _tab.active.opt = WA_STANDOUT;
    _tab.inactive.bg = COLOR_BLACK;
    _tab.inactive.fg = COLOR_YELLOW;
    _tab.inactive.opt = WA_NORMAL;

    _list.active.bg = COLOR_BLACK;
    _list.active.fg = COLOR_CYAN;
    _list.active.opt = WA_STANDOUT;
    _list.inactive.bg = COLOR_BLACK;
    _list.inactive.fg = COLOR_WHITE;
    _list.inactive.opt = WA_NORMAL;

    _progress.bar = COLOR_YELLOW;
    _progress.label.bg = COLOR_GREEN;
    _progress.label.fg = COLOR_BLACK;
    _progress.label.opt = WA_REVERSE;

    _bar.bar = COLOR_YELLOW;
    _bar.number = COLOR_WHITE;
    _bar.label.bg = COLOR_BLACK;
    _bar.label.fg = COLOR_CYAN;

    _checkbox.style.bg = COLOR_BLACK;
    _checkbox.style.fg = COLOR_WHITE;
    _checkbox.style.opt = WA_NORMAL;

    _radio.style.bg = COLOR_BLACK;
    _radio.style.fg = COLOR_WHITE;
    _radio.style.opt = WA_NORMAL;
}