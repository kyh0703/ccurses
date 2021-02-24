#pragma once
#include <ncursesw/curses.h>

struct Color
{
    Color();
    Color(int bg, int fg);
    int bg, fg;
};

struct Style
{
    Style();
    Style(int bg, int fg);
    Style(int bg, int fg, int opt);
    int bg, fg, opt;
};

struct Pos
{
    Pos();
    Pos(int y, int x);
    bool operator<(const Pos &rhs) const;
    int y, x;
};

struct Rect
{
    Rect();
    Rect(int h, int w, int y, int x);
    bool IsInclude(int y, int x);
    Pos min;
    Pos max;
    int h, w;
};

struct Rune
{
    Rune();
    Rune(wchar_t wch);
    Rune(int bg, int fg, wchar_t wch);
    Rune(int bg, int fg, int opt, wchar_t wch);
    Rune(Style s, wchar_t wch);
    Style s;
    wchar_t wch;
};