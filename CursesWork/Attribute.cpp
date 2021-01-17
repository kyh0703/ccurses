#include "Attribute.h"

Border::Border()
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

Color::Color()
{
    this->bg = COLOR_BLACK;
    this->fg = COLOR_WHITE;
}

Color::Color(int bg, int fg)
{
    this->bg = bg;
    this->fg = fg;
}

Style::Style()
{
    this->bg = COLOR_BLACK;
    this->fg = COLOR_WHITE;
    this->opt = A_NORMAL;
}

Style::Style(int bg, int fg)
{
    this->bg = bg;
    this->fg = fg;
    this->opt = A_NORMAL;
}

Style::Style(int bg, int fg, int opt)
{
    this->bg = bg;
    this->fg = fg;
    this->opt = opt;
}

Pos::Pos()
{
    this->y = 0;
    this->x = 0;
}

Pos::Pos(int y, int x)
{
    this->y = y;
    this->x = x;
}

bool Pos::operator<(const Pos &rhs) const
{
    if (this->y != rhs.y)
        return this->y < rhs.y;
    return this->x < rhs.x;
}

Rect::Rect()
{
    min = {0, 0};
    max = {0, 0};
    h = 0;
    w = 0;
};

Rect::Rect(int h, int w, int y, int x)
{
    min.y = y;
    min.x = x;
    max.y = y + h - 1;
    max.x = x + w - 1;
    this->h = h;
    this->w = w;
}

Rune::Rune()
{
    this->c = ' ';
}

Rune::Rune(chtype c)
{
    this->s.bg = COLOR_BLACK;
    this->s.fg = COLOR_WHITE;
    this->s.opt = A_NORMAL;
    this->c = c;
}

Rune::Rune(int bg, int fg, chtype c)
{
    this->s.bg = bg;
    this->s.fg = fg;
    this->s.opt = A_NORMAL;
    this->c = c;
}

Rune::Rune(int bg, int fg, int opt, chtype c)
{
    this->s.bg = bg;
    this->s.fg = fg;
    this->s.opt = opt;
    this->c = c;
}

Rune::Rune(Style s, chtype c)
{
    this->s = s;
    this->c = c;
}