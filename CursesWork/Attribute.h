#pragma once
#include "ncurses.h"

struct Border
{
    Border();
    chtype ls, rs, ts, bs;
    chtype tl, tr, bl, br;
};

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
    Pos min;
    Pos max;
    int h, w;
};

struct Rune
{
    Rune();
    Rune(chtype c);
    Rune(int bg, int fg, chtype c);
    Rune(Style s, chtype c);
    Style s;
    chtype c;
};