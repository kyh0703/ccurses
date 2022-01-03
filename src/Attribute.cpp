#include "Attribute.h"
#include "Theme.h"

Border::Border()
{
    // NOTE WACS는 포인터임. attr 수정시 참조하는 Drawing 전체가 변경됨으로 주의
    this->ls = WACS_VLINE;
    this->rs = WACS_VLINE;
    this->ts = WACS_HLINE;
    this->bs = WACS_HLINE;
    this->tl = WACS_ULCORNER;
    this->tr = WACS_URCORNER;
    this->bl = WACS_LLCORNER;
    this->br = WACS_LRCORNER;
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
    this->opt = WA_NORMAL;
}

Style::Style(int bg, int fg)
{
    this->bg = bg;
    this->fg = fg;
    this->opt = WA_NORMAL;
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
    this->wch = ' ';
}

Rune::Rune(wchar_t wch)
{
    this->s.bg = COLOR_BLACK;
    this->s.fg = COLOR_WHITE;
    this->s.opt = WA_NORMAL;
    this->wch = wch;
}

Rune::Rune(int bg, int fg, wchar_t wch)
{
    this->s.bg = bg;
    this->s.fg = fg;
    this->s.opt = WA_NORMAL;
    this->wch = wch;
}

Rune::Rune(int bg, int fg, int opt, wchar_t wch)
{
    this->s.bg = bg;
    this->s.fg = fg;
    this->s.opt = opt;
    this->wch = wch;
}

Rune::Rune(Style s, wchar_t wch)
{
    this->s = s;
    this->wch = wch;
}