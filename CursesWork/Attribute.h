#pragma once
#include "ncurses.h"

struct Border
{
    Border()
    {
        this->ls = ACS_VLINE;
        this->rs = ACS_VLINE;
        this->ts = ACS_HLINE;
        this->bs = ACS_HLINE;
        this->tl = ACS_ULCORNER;
        this->tr = ACS_URCORNER;
        this->bl = ACS_LLCORNER;
        this->br = ACS_LRCORNER;
    }

    chtype ls, rs, ts, bs;
    chtype tl, tr, bl, br;
};

struct Color
{
    Color()
    {
        this->bg = COLOR_BLACK;
        this->fg = COLOR_WHITE;
    }

    Color(int bg, int fg)
    {
        this->bg = bg;
        this->fg = fg;
    }

    int bg, fg;
};

struct Style
{
    Style()
    {
        this->bg = COLOR_BLACK;
        this->fg = COLOR_WHITE;
        this->opt = A_NORMAL;
    }

    Style(int bg, int fg)
    {
        this->bg = bg;
        this->fg = fg;
        this->opt = A_NORMAL;
    }

    Style(int bg, int fg, int opt)
    {
        this->bg = bg;
        this->fg = fg;
        this->opt = opt;
    }

    int bg, fg, opt;
};

struct Rect
{
    Rect()
    {
        this->h = 0;
        this->w = 0;
        this->x = 0;
        this->y = 0;
    }

    Rect(int h, int w, int x, int y)
    {
        this->h = h;
        this->w = w;
        this->x = x;
        this->y = y;
    }

    int h, w, x, y;
};

struct Pos
{
    Pos(int y, int x)
    {
        this->y = y;
        this->x = x;
    }

    bool operator<(const Pos &rhs) const
    {
        if (this->y != rhs.y)
            return this->y < rhs.y;
        return this->x < rhs.x;
    }

    int y, x;
};

struct Rune
{
    Rune()
    {
        this->c = ' ';
    }

    Rune(chtype c)
    {
        this->s.bg = COLOR_BLACK;
        this->s.fg = COLOR_WHITE;
        this->s.opt = A_NORMAL;
        this->c = c;
    }

    Rune(int bg, int fg, chtype c)
    {
        this->s.bg = bg;
        this->s.fg = fg;
        this->s.opt = A_NORMAL;
        this->c = c;
    }

    Rune(Style s, chtype c)
    {
        this->s = s;
        this->c = c;
    }

    Style s;
    chtype c;
};