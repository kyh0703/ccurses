#include "Attribute.h"

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
    this->opt = A_BOLD;
}

Style::Style(int bg, int fg)
{
    this->bg = bg;
    this->fg = fg;
    this->opt = A_BOLD;
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

bool Rect::IsInclude(int y, int x)
{
    return (this->min.y <= y && y <= this->max.y &&
            this->min.x <= x && x <= this->max.x);
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