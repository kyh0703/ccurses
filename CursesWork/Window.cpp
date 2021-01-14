#include "Window.h"
#include "Paint.h"
#include "Theme.h"

Window::Window()
{
    _color.bg = th::Get()._default.bg;
    _color.fg = th::Get()._default.fg;
}

Window::~Window()
{
}

void Window::Log(const char *format, ...)
{
    char line[1024], *pPos;
    memset(line, 0x00, sizeof(line));
    pPos = line;
    int size = sprintf(pPos, "DEBUG > ");

    va_list Marker;
    va_start(Marker, format);
    vsnprintf(line, sizeof(line) - size, format, Marker);
    va_end(Marker);
    mvaddstr(LINES - 1, 0, line);
}

Rect Window::GetRect()
{
    return _rect;
}

void Window::SetRect(int h, int w, int y, int x)
{
    _rect.h = h;
    _rect.w = w;
    _rect.y = y;
    _rect.x = x;
}

void Window::SetColor(int bg, int fg)
{
    _color.bg = bg;
    _color.fg = fg;
}

void Window::SetTitle(string title)
{
    _title = title;
}

const map<Pos, Rune> &Window::GetCells(void)
{
    return _cells;
}

void Window::AttachCells(map<Pos, Rune> cells)
{
    map<Pos, Rune>::iterator it;
    for (it = cells.begin(); it != cells.end(); ++it)
    {
        Pos pos((*it).first);
        Rune r((*it).second);
        if (_cells.find(pos) != _cells.end())
            _cells[pos] = r;
    }
}

void Window::DrawBase()
{
    InitCell();
    MakeBorder();
    MakeTitle();
}

void Window::Erase()
{
    for (int i = _rect.y; i <= _rect.h + _rect.y; ++i)
        for (int j = _rect.x; j <= _rect.x + _rect.w; ++j)
            mvdelch(i, j);
    refresh();
}

void Window::Print()
{
    for (int line = _rect.y; line <= _rect.h + _rect.y; ++line)
    {
        for (int col = _rect.x; col <= _rect.x + _rect.w; ++col)
        {
            Rune rune = _cells[{line, col}];
            int idx = Paint::Get().GetIndex(rune.s.bg, rune.s.fg);
            attron(COLOR_PAIR(idx) | rune.s.opt);
            mvaddch(line, col, rune.c);
            attroff(COLOR_PAIR(idx) | rune.s.opt);
        }
    }
}

void Window::HLine(int y, int x, int n, Rune c)
{
    for (int cols = x; cols < n + x; ++cols)
        _cells[{y, cols}] = c;
}

void Window::VLine(int y, int x, int n, Rune c)
{
    for (int line = y; line < n + y; ++line)
        _cells[{line, x}] = c;
}

void Window::AddCh(int y, int x, Rune c)
{
    _cells[{y, x}] = c;
}

void Window::AddStr(int y, int x, string s)
{
    for (size_t idx = 0; idx < s.size(); idx++)
        _cells[{y, x++}] = {_color.bg, COLOR_WHITE, (chtype)s[idx]};
}

void Window::GetCh(int y, int x, Rune c)
{

}

const string Window::GetStr(int y, int x, int n)
{
    vector<chtype> runes;
    for (int col = x; col < x + n; ++col)
        runes.push_back(mvgetch(y, col));
    string str(runes.begin(), runes.end());
    return str;
}

void Window::InitCell()
{
    for (int line = _rect.y; line <= _rect.h + _rect.y; ++line)
        for (int col = _rect.x; col <= _rect.x + _rect.w; ++col)
            _cells[{line, col}] = {_color.bg, _color.bg, ' '};
}

void Window::MakeBorder()
{
    _cells[{_rect.y, _rect.x}] = {_color.bg, _color.fg, _border.tl};
    _cells[{_rect.y, _rect.x + _rect.w}] = {_color.bg, _color.fg, _border.tr};
    _cells[{_rect.y + _rect.h, _rect.x}] = {_color.bg, _color.fg, _border.bl};
    _cells[{_rect.y + _rect.h, _rect.x + _rect.w}] = {_color.bg, _color.fg, _border.br};
    HLine(_rect.y + _rect.h, _rect.x + 1, _rect.w - 1, {_color.bg, _color.fg, _border.bs});
    HLine(_rect.y, _rect.x + 1, _rect.w - 1, {_color.bg, _color.fg, _border.ts});
    VLine(_rect.y + 1, _rect.x, _rect.h - 1, {_color.bg, _color.fg, _border.ls});
    VLine(_rect.y + 1, _rect.x + _rect.w, _rect.h - 1, {_color.bg, _color.fg, _border.rs});
}

void Window::MakeTitle()
{
    AddStr(_rect.y, _rect.x + 2, _title);
}